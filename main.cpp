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

/* architecture-specific VM utilities to init stack, set args, return values */
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
void vm_set_arg0(int a) { vm_regs["x0"] = a; }
void vm_set_arg1(int a) { vm_regs["x1"] = a; }
void vm_set_arg2(int a) { vm_regs["x2"] = a; }
void vm_precall() { vm_regs["sp"] -= 8; *(uint64_t *)vm_mem = 0x00C4113200C41132; }
int vm_get_retval() { return vm_regs["x0"]; }
#endif

#ifdef ARCH_Z80
void vm_init_stack() { vm_regs["SP"] = VM_MEM_SZ; }
void vm_set_arg0(int16_t a) { vm_regs["SP"] -= 2; *(int16_t *)(vm_mem + vm_regs["SP"]) = a; }
void vm_set_arg1(int16_t a) { vm_set_arg0(a); }
void vm_set_arg2(int16_t a) { vm_set_arg0(a); }
void vm_precall() { vm_regs["SP"] -= 2; *(uint16_t *)(vm_mem + vm_regs["SP"]) = 0xAAAA; }
int16_t vm_get_retval() { return (int16_t)vm_regs["HL"]; }
#endif

/* architecture-independent VM utilities */
void vm_reset()
{
	memset(vm_mem, 0, VM_MEM_SZ);
	vm_regs.clear();
	vm_init_stack();
	/* from tests_il.cpp, generated to include switch lookup tables */
	initialize_memory();
}

typedef void (*VMFUNC)(void);

/* call a 1-arg function in the VM */
int vm_call(VMFUNC pfunc) {
	vm_reset();
	vm_precall();
	pfunc();
	return vm_get_retval();
}

/* call a 1-arg function in the VM */
int vm_call(VMFUNC pfunc, int a)
{
	vm_reset();
	vm_set_arg0(a);
	vm_precall();
	pfunc();
	return vm_get_retval();
}

/* call a 2-arg function in the VM */
int vm_call(VMFUNC pfunc, int a, int b)
{
	vm_reset();
	vm_set_arg1(b);
	vm_set_arg0(a);
	vm_precall();
	pfunc();
	return vm_get_retval();
}

/* call a 3-arg function in the VM */
int vm_call(VMFUNC pfunc, int a, int b, int c)
{
	vm_reset();
	vm_set_arg2(c);
	vm_set_arg1(b);
	vm_set_arg0(a);
	vm_precall();
	pfunc();
	return vm_get_retval();
}

void check(int actual, int expected)
{
	if(actual == expected)
		printf("   \x1B[32mPASSED\x1B[0m (actual,expected) = (%d,%d)\n", actual, expected);
	else {
		printf("   \x1B[31mFAILED\x1B[0m (actual,expected) = (%d,%d)\n", actual, expected);
		exit(-1);
	}
}

void test(const char *sfunc, VMFUNC pfunc, int expected)
{
	printf("%s()...\n", sfunc);
	check(vm_call(pfunc), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int expected)
{
	printf("%s(%d)...\n", sfunc, a);
	check(vm_call(pfunc, a), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int b, int expected)
{
	printf("%s(%d, %d)...\n", sfunc, a, b);
	check(vm_call(pfunc, a, b), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int b, int c, int expected)
{
	printf("%s(%d, %d, %d)...\n", sfunc, a, b, c);
	check(vm_call(pfunc, a, b, c), expected);
}

int main(int ac, char **av)
{
	int result;

	test("life_universe_everything()", life_universe_everything, 42);

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

	/* switch statements */
	test("switch_doubler", switch_doubler,0, 0);
	test("switch_doubler", switch_doubler,2, 4);
	test("switch_doubler", switch_doubler,999, -1);
	test("switch_doubler", switch_doubler,9, 18);
}
