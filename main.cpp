#include <stdio.h>
#include <stdint.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

/* VM components */
#include "runtime.h"
extern vector<REGTYPE> vm_stack;
extern uint8_t vm_mem[VM_MEM_SZ];
extern map<string,REGTYPE> vm_regs;
extern map<string,double> vm_regs_double;

/* arguments */


//-----------------------------------------------------------------------------
// type/value definition, helpers
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// functions from tests_il.o
//-----------------------------------------------------------------------------

#ifdef LEADING_UNDERSCORE
#define life_universe_everything _life_universe_everything
#define add _add
#define test_byte_e_10 _test_byte_e_10
#define test_byte_ne_10 _test_byte_ne_10
#define test_byte_slt_10 _test_byte_slt_10
#define test_byte_ult_10 _test_byte_ult_10
#define test_byte_sle_10 _test_byte_sle_10
#define test_byte_ule_10 _test_byte_ule_10
#define test_byte_sge_10 _test_byte_sge_10
#define test_byte_uge_10 _test_byte_uge_10
#define test_byte_sgt_10 _test_byte_sgt_10
#define test_byte_ugt_10 _test_byte_ugt_10
#define test_byte_neg _test_byte_neg
#define test_byte_pos _test_byte_pos
#define test_word_e_10 _test_word_e_10
#define test_word_ne_10 _test_word_ne_10
#define test_word_slt_10 _test_word_slt_10
#define test_word_ult_10 _test_word_ult_10
#define test_word_sle_10 _test_word_sle_10
#define test_word_ule_10 _test_word_ule_10
#define test_word_sge_10 _test_word_sge_10
#define test_word_uge_10 _test_word_uge_10
#define test_word_sgt_10 _test_word_sgt_10
#define test_word_ugt_10 _test_word_ugt_10
#define test_word_neg _test_word_neg
#define test_word_pos _test_word_pos
#define triangle_up _triangle_up
#define triangle_down _triangle_down
#define multiply_u8 _multiply_u8
#define multiply _multiply
#define multiply_loop _multiply_loop
#define div _div
#define mod _mod
#define exp_dummy _exp_dummy
#define expmod _expmod
#define gcd _gcd
#define gcd_recursive _gcd_recursive
#define switch_doubler _switch_doubler
#define factorial _factorial
#define fp_single_add _fp_single_add
#define fp_single_sub _fp_single_sub
#define fp_single_mul _fp_single_mul
#define fp_single_div _fp_single_div
#endif

/* functions from generated tests_il.o we'll be using */
void life_universe_everything();
void initialize_memory();
void add();
void test_byte_e_10();
void test_byte_ne_10();
void test_byte_slt_10();
void test_byte_ult_10();
void test_byte_sle_10();
void test_byte_ule_10();
void test_byte_sge_10();
void test_byte_uge_10();
void test_byte_sgt_10();
void test_byte_ugt_10();
void test_byte_neg();
void test_byte_pos();
void test_word_e_10();
void test_word_ne_10();
void test_word_slt_10();
void test_word_ult_10();
void test_word_sle_10();
void test_word_ule_10();
void test_word_sge_10();
void test_word_uge_10();
void test_word_sgt_10();
void test_word_ugt_10();
void test_word_neg();
void test_word_pos();
void triangle_up();
void triangle_down();
void multiply();
void multiply_u8();
void multiply_loop();
void div();
void mod();
void exp_dummy();
void expmod();
void gcd();
void gcd_recursive();
void switch_doubler();
void factorial();
void fp_single_add();
void fp_single_sub();
void fp_single_mul();
void fp_single_div();

//-----------------------------------------------------------------------------
// architecture-specific VM utilities to init stack, set args, return values
//-----------------------------------------------------------------------------

#ifdef ARCH_X64
void vm_init_stack() { reg_set_uint64("rsp", VM_MEM_SZ); }
void vm_set_arg0(int a) { reg_set_uint64("rdi", a); }
void vm_set_arg1(int a) { reg_set_uint64("rsi", a); }
void vm_set_arg2(int a) { reg_set_uint64("rdx", a); }
void vm_precall()
{
	// synthesize a push of "CALLERCALLER"
	reg_set_uint64("rsp", reg_get_uint64("rsp")-8);
	*(uint64_t *)(vm_mem + reg_get_uint64("rsp")) = RETURN_ADDRESS_CANARY;
}

void vm_set_arg(int order, type_val tv)
{
	// System V AMD64 ABI
	// The first six integer or pointer arguments are passed in registers RDI, RSI, RDX, RCX, R8, R9
	if(tv.type == TV_TYPE_UINT64) {
		switch(order) {
			case 0: reg_set_uint64("rdi", tv_get_uint64(tv)); break;
			case 1: reg_set_uint64("rsi", tv_get_uint64(tv)); break;
			case 2: reg_set_uint64("rdx", tv_get_uint64(tv)); break;
			case 3: reg_set_uint64("rcx", tv_get_uint64(tv)); break;
			case 4: reg_set_uint64("r8", tv_get_uint64(tv)); break;
			case 5: reg_set_uint64("r9", tv_get_uint64(tv)); break;
			break;
		}
	}
	else if(tv.type == TV_TYPE_UINT32) {
		switch(order) {
			case 0: reg_set_uint64("rdi", tv_get_uint32(tv)); break;
			case 1: reg_set_uint64("rsi", tv_get_uint32(tv)); break;
			case 2: reg_set_uint64("rdx", tv_get_uint32(tv)); break;
			case 3: reg_set_uint64("rcx", tv_get_uint32(tv)); break;
			case 4: reg_set_uint64("r8", tv_get_uint32(tv)); break;
			case 5: reg_set_uint64("r9", tv_get_uint32(tv)); break;
			break;
		}
	}
	// ...while XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6 and XMM7 are used for the first floating point arguments
	else if(tv.type == TV_TYPE_FLOAT32) {
		switch(order) {
			case 0: reg_set_float32("xmm0", tv_get_float32(tv)); break;
			case 1: reg_set_float32("xmm1", tv_get_float32(tv)); break;
			case 2: reg_set_float32("xmm2", tv_get_float32(tv)); break;
			case 3: reg_set_float32("xmm3", tv_get_float32(tv)); break;
			case 4: reg_set_float32("xmm4", tv_get_float32(tv)); break;
			case 5: reg_set_float32("xmm5", tv_get_float32(tv)); break;
			case 6: reg_set_float32("xmm6", tv_get_float32(tv)); break;
			case 7: reg_set_float32("xmm7", tv_get_float32(tv)); break;
			case 8: reg_set_float32("xmm8", tv_get_float32(tv)); break;
			break;
		}
	}
}

type_val vm_get_retval(enum TV_TYPE ret_type)
{
	switch(ret_type)
	{
		case TV_TYPE_UINT8: return tv_new_uint8(reg_get_uint8("al"));
		case TV_TYPE_UINT16: return tv_new_uint16(reg_get_uint16("ax"));
		case TV_TYPE_UINT32: return tv_new_uint32(reg_get_uint32("eax"));
		case TV_TYPE_UINT64: return tv_new_uint64(reg_get_uint64("rax"));
		case TV_TYPE_FLOAT32:
		{
			__uint128_t tmp = reg_get_uint128("xmm0");
			type_val tv = tv_new_float32(*(float *)(&tmp));
			return tv;
		}
		default:
			return tv_new_none();
	}
}
#endif

#ifdef ARCH_ARM
void vm_init_stack() { vm_regs["sp"] = VM_MEM_SZ; }
void vm_set_arg(int order, type_val tv)
{
	if(tv.type == TV_TYPE_UINT32 || tv.type == TV_TYPE_FLOAT32) {
		switch(order) {
			case 0: reg_set_uint32("r0", tv_get_uint32(tv)); break;
			case 1: reg_set_uint32("r1", tv_get_uint32(tv)); break;
			case 2: reg_set_uint32("r2", tv_get_uint32(tv)); break;
			break;
		}
	}
}

void vm_precall()
{
	reg_set_uint32("lr", RETURN_ADDRESS_CANARY);
}

type_val vm_get_retval(enum TV_TYPE ret_type)
{
	switch(ret_type)
	{
		case TV_TYPE_UINT32:
			return tv_new_uint32(reg_get_uint32("r0"));
		case TV_TYPE_FLOAT32:
			return tv_new_float32(reg_get_float32("r0"));
		default:
			return tv_new_none();
	}
}
#endif

#ifdef ARCH_A64
void vm_init_stack() { vm_regs["sp"] = VM_MEM_SZ; }
void vm_precall() { vm_regs["sp"] -= 8; *(uint64_t *)vm_mem = RETURN_ADDRESS_CANARY; }
void vm_set_arg(int order, type_val tv)
{
	if(tv.type == TV_TYPE_UINT32) {
		if(order==0) reg_set_uint32("w0", tv_get_uint32(tv));
		else if(order==1) reg_set_uint32("w1", tv_get_uint32(tv));
		else if(order==2) reg_set_uint32("w2", tv_get_uint32(tv));
		else if(order==3) reg_set_uint32("w3", tv_get_uint32(tv));
	}
	else if(tv.type == TV_TYPE_UINT64) {
		if(order==0) reg_set_uint64("x0", tv_get_uint64(tv));
		else if(order==1) reg_set_uint64("x1", tv_get_uint64(tv));
		else if(order==2) reg_set_uint64("x2", tv_get_uint64(tv));
		else if(order==3) reg_set_uint64("x3", tv_get_uint64(tv));
	}
	else if(tv.type == TV_TYPE_FLOAT32) {
		if(order==0) reg_set_float32("s0", tv_get_float32(tv));
		else if(order==1) reg_set_float32("s1", tv_get_float32(tv));
		else if(order==2) reg_set_float32("s2", tv_get_float32(tv));
		else if(order==3) reg_set_float32("s3", tv_get_float32(tv));
	}
}
type_val vm_get_retval(enum TV_TYPE type)
{
	type_val result;

	switch(type)
	{
		case TV_TYPE_UINT32:
			result = reg_get_type_val("w0");
			break;
		case TV_TYPE_UINT64:
			result = reg_get_type_val("x0");
			break;
		case TV_TYPE_FLOAT32:
			result = reg_get_type_val("s0");
			break;
		default:
			__builtin_debugtrap();
	}

	result.type = type;
	return result;
}
#endif

#ifdef ARCH_Z80
void vm_init_stack() { vm_regs["SP"] = VM_MEM_SZ; }
void vm_set_arg0(int16_t a) { vm_regs["SP"] -= 2; *(int16_t *)(vm_mem + vm_regs["SP"]) = a; }
void vm_set_arg1(int16_t a) { vm_set_arg0(a); }
void vm_set_arg2(int16_t a) { vm_set_arg0(a); }
void vm_precall() { vm_regs["SP"] -= 2; *(uint16_t *)(vm_mem + vm_regs["SP"]) = 0xAAAA; }
int16_t vm_get_retval() { return (int16_t)vm_regs["HL"]; }
#endif

//-----------------------------------------------------------------------------
// architecture-independent VM utilities
//-----------------------------------------------------------------------------

void vm_reset()
{
	memset(vm_mem, 0, VM_MEM_SZ);
	vm_regs.clear();
	vm_init_stack();
	/* from tests_il.cpp, generated to include switch lookup tables */
	initialize_memory();
}

typedef void (*VM_FUNC)(void);
typedef void (*VM_FUNC_SET_ARG)(type_val tv);

/* call a function in the vm */
type_val vm_call(VM_FUNC pfunc, type_val *args, enum TV_TYPE ret_type)
{
	vm_reset();
	vm_precall();

	/* set function arguments */
	for(int i=0; args[i].type != TV_TYPE_NONE; i++)
		vm_set_arg(i, args[i]);

	/* call the function, return result */
	pfunc();
	return vm_get_retval(ret_type);
}

//-----------------------------------------------------------------------------
// testing convenience functions
//-----------------------------------------------------------------------------

void check(type_val actual, type_val expected)
{
	char actual_str[128], expected_str[128];
	tv_to_str(actual, actual_str, 128);
	tv_to_str(expected, expected_str, 128);

	printf("actual: ");
	for(int i=0; i<16; i++)
		printf("%02X ", actual.data[i]);
	printf("\n");

	printf("expect: ");
	for(int i=0; i<16; i++)
		printf("%02X ", expected.data[i]);
	printf("\n");

	if(tv_cmp(actual, expected)==0)
		printf("   \x1B[32mPASSED\x1B[0m (actual,expected) = (%s,%s)\n", actual_str, expected_str);
	else {
		printf("   \x1B[31mFAILED\x1B[0m (actual,expected) = (%s,%s)\n", actual_str, expected_str);
		exit(-1);
	}
}

// u32 foo(void)
void test(const char *func_name, VM_FUNC pfunc, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[1];
	args[0] = tv_new_none();
	type_val result = vm_call(pfunc, args, TV_TYPE_UINT32);
	type_val expected_tv = tv_new_uint32(expected);
	check(result, expected_tv);
}

// u32 foo(u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[2];
	args[0] = tv_new_uint32(arg0);
	args[1] = tv_new_none();
	type_val result = vm_call(pfunc, args, TV_TYPE_UINT32);
	type_val expected_tv = tv_new_uint32(expected);
	check(result, expected_tv);
}

// u32 foo(u32, u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t arg1, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[3];
	args[0] = tv_new_uint32(arg0);
	args[1] = tv_new_uint32(arg1);
	args[2] = tv_new_none();
	type_val result = vm_call(pfunc, args, TV_TYPE_UINT32);
	type_val expected_tv = tv_new_uint32(expected);
	check(result, expected_tv);
}

// u32 foo(u32, u32, u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[4];
	args[0] = tv_new_uint32(arg0);
	args[1] = tv_new_uint32(arg1);
	args[2] = tv_new_uint32(arg2);
	args[3] = tv_new_none();
	type_val result = vm_call(pfunc, args, TV_TYPE_UINT32);
	type_val expected_tv = tv_new_uint32(expected);
	check(result, expected_tv);
}

// u32 foo(float32, float32)
void test_f(const char *func_name, VM_FUNC pfunc, float arg0, float arg1, float expected)
{
	printf("%s()...\n", func_name);
	type_val args[3];
	args[0] = tv_new_float32(arg0);
	args[1] = tv_new_float32(arg1);
	args[2] = tv_new_none();
	type_val result = vm_call(pfunc, args, TV_TYPE_FLOAT32);
	type_val expected_tv = tv_new_float32(expected);
	check(result, expected_tv);
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main(int ac, char **av)
{
	int result;

	test("life_universe_everything", life_universe_everything, 42);

	/* add */
	test("add", add, 4,7, 11);
	test("add", add, -4,7, 3);
	test("add", add, -4,-7, -11);
	test("add", add, 123,456, 579);

	/* comparison, 1 byte */

	//void test_byte_e_10();
	test("test_byte_e_10", test_byte_e_10,3, 13);
	test("test_byte_e_10", test_byte_e_10,7, 13);
	test("test_byte_e_10", test_byte_e_10,10, 7);
	test("test_byte_e_10", test_byte_e_10,13, 13);

	//void test_byte_ne_10();
	test("test_byte_ne_10", test_byte_ne_10,3, 7);
	test("test_byte_ne_10", test_byte_ne_10,7, 7);
	test("test_byte_ne_10", test_byte_ne_10,10, 13);
	test("test_byte_ne_10", test_byte_ne_10,13, 7);

	//void test_byte_slt_10();
	test("test_byte_slt_10", test_byte_slt_10,3, 7);
	test("test_byte_slt_10", test_byte_slt_10,7, 7);
	test("test_byte_slt_10", test_byte_slt_10,10, 13);
	test("test_byte_slt_10", test_byte_slt_10,13, 13);

	//void test_byte_ult_10();
	test("test_byte_ult_10", test_byte_ult_10,3, 7);
	test("test_byte_ult_10", test_byte_ult_10,7, 7);
	test("test_byte_ult_10", test_byte_ult_10,10, 13);
	test("test_byte_ult_10", test_byte_ult_10,13, 13);

	//void test_byte_sle_10();
	test("test_byte_sle_10", test_byte_sle_10,3, 7);
	test("test_byte_sle_10", test_byte_sle_10,7, 7);
	test("test_byte_sle_10", test_byte_sle_10,10, 7);
	test("test_byte_sle_10", test_byte_sle_10,13, 13);

	//void test_byte_ule_10();
	test("test_byte_ule_10", test_byte_ule_10,3, 7);
	test("test_byte_ule_10", test_byte_ule_10,7, 7);
	test("test_byte_ule_10", test_byte_ule_10,10, 7);
	test("test_byte_ule_10", test_byte_ule_10,13, 13);

	//void test_byte_sge_10();
	test("test_byte_sge_10", test_byte_sge_10,3, 13);
	test("test_byte_sge_10", test_byte_sge_10,7, 13);
	test("test_byte_sge_10", test_byte_sge_10,10, 7);
	test("test_byte_sge_10", test_byte_sge_10,13, 7);

	//void test_byte_uge_10();
	test("test_byte_uge_10", test_byte_uge_10,3, 13);
	test("test_byte_uge_10", test_byte_uge_10,7, 13);
	test("test_byte_uge_10", test_byte_uge_10,10, 7);
	test("test_byte_uge_10", test_byte_uge_10,13, 7);

	//void test_byte_sgt_10();
	test("test_byte_sgt_10", test_byte_sgt_10,3, 13);
	test("test_byte_sgt_10", test_byte_sgt_10,7, 13);
	test("test_byte_sgt_10", test_byte_sgt_10,10, 13);
	test("test_byte_sgt_10", test_byte_sgt_10,13, 7);

	//void test_byte_ugt_10();
	test("test_byte_ugt_10", test_byte_ugt_10,3, 13);
	test("test_byte_ugt_10", test_byte_ugt_10,7, 13);
	test("test_byte_ugt_10", test_byte_ugt_10,10, 13);
	test("test_byte_ugt_10", test_byte_ugt_10,13, 7);

	//void test_byte_neg();
	test("test_byte_neg", test_byte_neg,-23, 7);
	test("test_byte_neg", test_byte_neg,-7, 7);
	test("test_byte_neg", test_byte_neg,0, 13);
	test("test_byte_neg", test_byte_neg,7, 13);
	test("test_byte_neg", test_byte_neg,23, 13);

	//void test_byte_pos();
	test("test_byte_pos", test_byte_pos,-23, 13);
	test("test_byte_pos", test_byte_pos,-7, 13);
	test("test_byte_pos", test_byte_pos,0, 7);
	test("test_byte_pos", test_byte_pos,7, 7);
	test("test_byte_pos", test_byte_pos,23, 7);

	/* comparison, more bytes */
	//void test_word_e_10();
	test("test_word_e_10", test_word_e_10,3, 13);
	test("test_word_e_10", test_word_e_10,7, 13);
	test("test_word_e_10", test_word_e_10,10, 7);
	test("test_word_e_10", test_word_e_10,13, 13);

	//void test_word_ne_10();
	test("test_word_ne_10", test_word_ne_10,3, 7);
	test("test_word_ne_10", test_word_ne_10,7, 7);
	test("test_word_ne_10", test_word_ne_10,10, 13);
	test("test_word_ne_10", test_word_ne_10,13, 7);

	//void test_word_slt_10();
	test("test_word_slt_10", test_word_slt_10,3, 7);
	test("test_word_slt_10", test_word_slt_10,7, 7);
	test("test_word_slt_10", test_word_slt_10,10, 13);
	test("test_word_slt_10", test_word_slt_10,13, 13);

	//void test_word_ult_10();
	test("test_word_ult_10", test_word_ult_10,3, 7);
	test("test_word_ult_10", test_word_ult_10,7, 7);
	test("test_word_ult_10", test_word_ult_10,10, 13);
	test("test_word_ult_10", test_word_ult_10,13, 13);

	//void test_word_sle_10();
	test("test_word_sle_10", test_word_sle_10,3, 7);
	test("test_word_sle_10", test_word_sle_10,7, 7);
	test("test_word_sle_10", test_word_sle_10,10, 7);
	test("test_word_sle_10", test_word_sle_10,13, 13);

	//void test_word_ule_10();
	test("test_word_ule_10", test_word_ule_10,3, 7);
	test("test_word_ule_10", test_word_ule_10,7, 7);
	test("test_word_ule_10", test_word_ule_10,10, 7);
	test("test_word_ule_10", test_word_ule_10,13, 13);

	//void test_word_sge_10();
	test("test_word_sge_10", test_word_sge_10,3, 13);
	test("test_word_sge_10", test_word_sge_10,7, 13);
	test("test_word_sge_10", test_word_sge_10,10, 7);
	test("test_word_sge_10", test_word_sge_10,13, 7);

	//void test_word_uge_10();
	test("test_word_uge_10", test_word_uge_10,3, 13);
	test("test_word_uge_10", test_word_uge_10,7, 13);
	test("test_word_uge_10", test_word_uge_10,10, 7);
	test("test_word_uge_10", test_word_uge_10,13, 7);

	//void test_word_sgt_10();
	test("test_word_sgt_10", test_word_sgt_10,3, 13);
	test("test_word_sgt_10", test_word_sgt_10,7, 13);
	test("test_word_sgt_10", test_word_sgt_10,10, 13);
	test("test_word_sgt_10", test_word_sgt_10,13, 7);

	//void test_word_ugt_10();
	test("test_word_ugt_10", test_word_ugt_10,3, 13);
	test("test_word_ugt_10", test_word_ugt_10,7, 13);
	test("test_word_ugt_10", test_word_ugt_10,10, 13);
	test("test_word_ugt_10", test_word_ugt_10,13, 7);

	//void test_word_neg();
	test("test_word_neg", test_word_neg,-23, 7);
	test("test_word_neg", test_word_neg,-7, 7);
	test("test_word_neg", test_word_neg,0, 13);
	test("test_word_neg", test_word_neg,7, 13);
	test("test_word_neg", test_word_neg,23, 13);

	//void test_word_pos();
	test("test_word_pos", test_word_pos,-23, 13);
	test("test_word_pos", test_word_pos,-7, 13);
	test("test_word_pos", test_word_pos,0, 7);
	test("test_word_pos", test_word_pos,7, 7);
	test("test_word_pos", test_word_pos,23, 7);

    /* triangle numbers */
	test("triangle_up", triangle_up,4, 10);
	test("triangle_up", triangle_up,7, 28);
	test("triangle_up", triangle_up,10, 55);
	test("triangle_up", triangle_up,100, 5050);
	test("triangle_down", triangle_down,4, 10);
	test("triangle_down", triangle_down,7, 28);
	test("triangle_down", triangle_down,10, 55);
	test("triangle_down", triangle_down,100, 5050);

	/* multiply: easy case with MUL instruction, else kinda tough */
	test("multiply", multiply,4,7, 28);
	test("multiply", multiply,-4,7, -28);
	test("multiply", multiply,-4,-7, 28);
	test("multiply", multiply,151,217, 32767);

	/* multiply: using loop */
	test("multiply_loop", multiply_loop,4,7, 28);
	test("multiply_loop", multiply_loop,-4,7, -28);
	test("multiply_loop", multiply_loop,-4,-7, 28);
	test("multiply_loop", multiply_loop,151,217, 32767);

	/* div */
	test("div", div,4,-2, -2);
	test("div", div,4,7, 0);
	test("div", div,7,4, 1);
	test("div", div,28,7, 4);
	test("div", div,151,-50, -3);

	/* mod */
	test("mod", mod,4,7, 4);
	test("mod", mod,7,4, 3);
	test("mod", mod,28,7, 0);
	test("mod", mod,151,50, 1);

	/* exponentiate */
	test("exp", exp_dummy,4,7, 16384);
	test("exp", exp_dummy,2,14, 16384);
	test("exp", exp_dummy,3,7, 2187);
	test("exp", exp_dummy,-2,7, -128);

	/* exponentiate with a modulus */
	test("expmod", expmod,4,7,5, 4);
	test("expmod", expmod,2,16,17, 1);
	test("expmod", expmod,3,17,19, 13);
	test("expmod", expmod,17,3,23, 14);

	/* greatest common divisor */
	test("gcd", gcd,5,15, 5);
	test("gcd", gcd,16,24, 8);
	test("gcd", gcd,51,77, 1);
	test("gcd", gcd,51,119, 17);

	/* recursion */
	test("factorial", factorial,0, 1);
	test("factorial", factorial,5, 120);
#if REGWIDTH == 16
	/* be nice and don't let tests set MSB -> negative */
	test("factorial", factorial,6, 720);
	test("factorial", factorial,7, 5040);
#else
	test("factorial", factorial,8, 40320);
	test("factorial", factorial,11, 39916800);
#endif

	/* recursive version: greatest common divisor */
	test("gcd_recursive", gcd_recursive,5,15, 5);
	test("gcd_recursive", gcd_recursive,16,24, 8);
	test("gcd_recursive", gcd_recursive,51,77, 1);
	test("gcd_recursive", gcd_recursive,51,119, 17);

	/* floating point */
	test_f("fp_single_add", fp_single_add,1.0,2.0, 3.0);
	test_f("fp_single_add", fp_single_add,1.5,2.5, 4.0);
	test_f("fp_single_add", fp_single_add,2.5,3.5, 6.0);
	test_f("fp_single_add", fp_single_add,2.5,-3.5, -1.0);

	test_f("fp_single_sub", fp_single_sub,1.0,2.0, -1.0);
	test_f("fp_single_sub", fp_single_sub,1.5,2.5, -1.0);
	test_f("fp_single_sub", fp_single_sub,2.5,3.5, -1.0);
	test_f("fp_single_sub", fp_single_sub,2.5,-3.5, 6.0);

	test_f("fp_single_mul", fp_single_mul,1.0,2.0, 2.0);
	test_f("fp_single_mul", fp_single_mul,1.5,2.5, 3.75);
	test_f("fp_single_mul", fp_single_mul,2.5,3.5, 8.75);
	test_f("fp_single_mul", fp_single_mul,2.5,-3.5, -8.75);

	test_f("fp_single_div", fp_single_div,1.0,2.0, 0.5);
	test_f("fp_single_div", fp_single_div,1.5,2.5, 0.6);
	test_f("fp_single_div", fp_single_div,2.5,4.0, 0.625);
	test_f("fp_single_div", fp_single_div,2.5,-4.0, -0.625);

	/* switch statements */
	test("switch_doubler", switch_doubler,0, 0);
	test("switch_doubler", switch_doubler,2, 4);
	test("switch_doubler", switch_doubler,999, -1);
	test("switch_doubler", switch_doubler,9, 18);
}
