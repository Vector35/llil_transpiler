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
#define VM_TYPE_NONE 0
#define VM_TYPE_UINT16 1
#define VM_TYPE_UINT32 2
#define VM_TYPE_UINT64 3
#define VM_TYPE_FLOAT32 4

//-----------------------------------------------------------------------------
// type/value definition, helpers
//-----------------------------------------------------------------------------

typedef struct type_val_
{
	int type; // VM_TYPE_
	uint16_t u16;
	union {
		uint32_t u32;
		float f32;
	};
	uint64_t u64;

} type_val;

void tv_to_str(type_val tv, char *str)
{
	if(tv.type == VM_TYPE_UINT32) sprintf(str, "0x%08X", tv.u32);
	else if(tv.type == VM_TYPE_FLOAT32) sprintf(str, "%f", tv.f32);
	else strcpy(str, "None");
}

int tv_cmp(type_val a, type_val b)
{
	if(a.type != b.type) return -1;
	if(a.type == VM_TYPE_UINT16 && a.u16 == b.u16) return 0;
	if(a.type == VM_TYPE_UINT32 && a.u32 == b.u32) return 0;
	if(a.type == VM_TYPE_UINT64 && a.u64 == b.u64) return 0;
	if(a.type == VM_TYPE_FLOAT32 && a.f32 == b.f32) return 0;
	return -1;
}

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

//-----------------------------------------------------------------------------
// architecture-specific VM utilities to init stack, set args, return values
//-----------------------------------------------------------------------------

#ifdef ARCH_X64
void vm_init_stack() { vm_regs["rsp"] = VM_MEM_SZ; }
void vm_set_arg0(int a) { vm_regs["rdi"] = a; }
void vm_set_arg1(int a) { vm_regs["rsi"] = a; }
void vm_set_arg2(int a) { vm_regs["rdx"] = a; }
void vm_precall() { vm_regs["rsp"] -= 8; *(uint64_t *)vm_mem = 0x00C4113200C41132; }
int vm_get_retval() { return vm_regs["rax"]; }
#endif

#ifdef ARCH_ARM
void vm_init_stack() { vm_regs["sp"] = VM_MEM_SZ; }
void vm_set_arg0(int a) { vm_regs["r0"] = a; }
void vm_set_arg1(int a) { vm_regs["r1"] = a; }
void vm_set_arg2(int a) { vm_regs["r2"] = a; }
void vm_precall() { vm_regs["sp"] -= 4; *(uint32_t *)vm_mem = 0x00C41132; }
int vm_get_retval() { return vm_regs["r0"]; }
#endif

#ifdef ARCH_A64
void vm_init_stack() { vm_regs["sp"] = VM_MEM_SZ; }
void vm_precall() { vm_regs["sp"] -= 8; *(uint64_t *)vm_mem = 0x00C4113200C41132; }
void vm_set_arg(int order, type_val tv)
{
	if(tv.type == VM_TYPE_UINT32) {
		if(order==0) reg_core_set_value("x0", tv.u32);
		else if(order==1) reg_core_set_value("x1", tv.u32);
		else if(order==2) reg_core_set_value("x2", tv.u32);
		else if(order==3) reg_core_set_value("x3", tv.u32);
	}
	else if(tv.type == VM_TYPE_UINT64) {
		if(order==0) reg_core_set_value("x0", tv.u64);
		else if(order==1) reg_core_set_value("x1", tv.u64);
		else if(order==2) reg_core_set_value("x2", tv.u64);
		else if(order==3) reg_core_set_value("x3", tv.u64);
	}
	else if(tv.type == VM_TYPE_FLOAT32) {
		if(order==0) reg_core_set_value("s0", tv.u32);
		else if(order==1) reg_core_set_value("s1", tv.u32);
		else if(order==2) reg_core_set_value("s2", tv.u32);
		else if(order==3) reg_core_set_value("s3", tv.u32);
	}
}
type_val vm_get_retval(int type)
{
	if(type == VM_TYPE_UINT32) return {.type=VM_TYPE_UINT32, .u32=(uint32_t)reg_core_get_value("w0")};
	if(type == VM_TYPE_UINT64) return {.type=VM_TYPE_UINT64, .u64=(uint64_t)reg_core_get_value("x0")};
	if(type == VM_TYPE_FLOAT32) return {.type=VM_TYPE_FLOAT32, .u32=(uint32_t)reg_core_get_value("s0")};
	return {.type=VM_TYPE_NONE, .u32=0};
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
type_val vm_call(VM_FUNC pfunc, type_val *args, int ret_type) {
	vm_reset();
	vm_precall();

	/* set function arguments */
	for(int i=0; args[i].type != VM_TYPE_NONE; i++)
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
	tv_to_str(actual, actual_str);
	tv_to_str(expected, expected_str);

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
	type_val args[1] = {{.type=VM_TYPE_NONE, .u32=0}};
	type_val result = vm_call(pfunc, args, VM_TYPE_UINT32);
	check(result, {.type=VM_TYPE_UINT32, .u32=expected});
}

// u32 foo(u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[2] = {{.type=VM_TYPE_UINT32, .u32=arg0}, {.type=VM_TYPE_NONE, .u32=0}};
	type_val result = vm_call(pfunc, args, VM_TYPE_UINT32);
	check(result, {.type=VM_TYPE_UINT32, .u32=expected});
}

// u32 foo(u32, u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t arg1, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[3] = {{.type=VM_TYPE_UINT32, .u32=arg0}, {.type=VM_TYPE_UINT32, .u32=arg1}, {.type=VM_TYPE_NONE, .u32=0}};
	type_val result = vm_call(pfunc, args, VM_TYPE_UINT32);
	check(result, {.type=VM_TYPE_UINT32, .u32=expected});
}

// u32 foo(u32, u32, u32)
void test(const char *func_name, VM_FUNC pfunc, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t expected)
{
	printf("%s()...\n", func_name);
	type_val args[4] = {
		{.type=VM_TYPE_UINT32, .u32=arg0}, {.type=VM_TYPE_UINT32, .u32=arg1},
		{.type=VM_TYPE_UINT32, .u32=arg2}, {.type=VM_TYPE_NONE, .u32=0}
	};
	type_val result = vm_call(pfunc, args, VM_TYPE_UINT32);
	check(result, {.type=VM_TYPE_UINT32, .u32=expected});
}

// u32 foo(u32, u32)
void test_f(const char *func_name, VM_FUNC pfunc, float arg0, float arg1, float expected)
{
	printf("%s()...\n", func_name);
	type_val args[3] = {{.type=VM_TYPE_FLOAT32, .f32=arg0}, {.type=VM_TYPE_FLOAT32, .f32=arg1}, {.type=VM_TYPE_NONE, .u32=0}};
	type_val result = vm_call(pfunc, args, VM_TYPE_FLOAT32);
	check(result, {.type=VM_TYPE_FLOAT32, .f32=expected});
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
	test_f("fadd", fp_single_add,1.0,2.0, 3.0);
	test_f("fadd", fp_single_add,1.5,2.5, 4.0);
	test_f("fadd", fp_single_add,2.5,3.5, 6.0);
	test_f("fadd", fp_single_add,2.5,-3.5, -1.0);

	/* switch statements */
	test("switch_doubler", switch_doubler,0, 0);
	test("switch_doubler", switch_doubler,2, 4);
	test("switch_doubler", switch_doubler,999, -1);
	test("switch_doubler", switch_doubler,9, 18);
}
