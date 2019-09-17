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
#define is_equal_10 _is_equal_10
#define is_greater_10_unsigned_u8 _is_greater_10_unsigned_u8
#define than_equal_10_unsigned_u8 _than_equal_10_unsigned_u8
#define is_greater_10_signed_s8 _is_greater_10_signed_s8
#define is_less_than_equal_10_signed_s8 _is_less_than_equal_10_signed_s8
#define is_greater_10_signed _is_greater_10_signed
#define is_less_than_equal_10_signed _is_less_than_equal_10_signed
#define is_greater_10_unsigned _is_greater_10_unsigned
#define is_less_than_equal_10_unsigned _is_less_than_equal_10_unsigned
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
void is_equal_10();
void is_greater_10_unsigned_u8();
void than_equal_10_unsigned_u8();
void is_greater_10_signed_s8();
void is_less_than_equal_10_signed_s8();
void is_greater_10_signed();
void is_less_than_equal_10_signed();
void is_greater_10_unsigned();
void is_less_than_equal_10_unsigned();
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
		printf("\x1B[32mPASSED\x1B[0m (%d is correct)\n", actual);
	else {
		printf("\x1B[31mFAILED\x1B[0m (%d != %d)\n", actual, expected);
		exit(-1);
	}
}

void test(const char *sfunc, VMFUNC pfunc, int expected)
{
	printf("%s()...", sfunc);
	check(vm_call(pfunc), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int expected)
{
	printf("%s(%d)...", sfunc, a);
	check(vm_call(pfunc, a), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int b, int expected)
{
	printf("%s(%d, %d)...", sfunc, a, b);
	check(vm_call(pfunc, a, b), expected);
}

void test(const char *sfunc, VMFUNC pfunc, int a, int b, int c, int expected)
{
	printf("%s(%d, %d, %d)...", sfunc, a, b, c);
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
	test("is_equal_10", is_equal_10,3, 0);
	test("is_equal_10", is_equal_10,7, 0);
	test("is_equal_10", is_equal_10,10, 1);
	test("is_equal_10", is_equal_10,13, 0);

	test("is_greater_10_unsigned_u8", is_greater_10_unsigned_u8,3, 0);
	test("is_greater_10_unsigned_u8", is_greater_10_unsigned_u8,7, 0);
	test("is_greater_10_unsigned_u8", is_greater_10_unsigned_u8,11, 1);
	test("is_greater_10_unsigned_u8", is_greater_10_unsigned_u8,13, 1);

	test("than_equal_10_unsigned_u8", than_equal_10_unsigned_u8,3, 1);
	test("than_equal_10_unsigned_u8", than_equal_10_unsigned_u8,7, 1);
	test("than_equal_10_unsigned_u8", than_equal_10_unsigned_u8,11, 0);
	test("than_equal_10_unsigned_u8", than_equal_10_unsigned_u8,13, 0);

	test("is_greater_10_signed_s8", is_greater_10_signed_s8,3, 0);
	test("is_greater_10_signed_s8", is_greater_10_signed_s8,7, 0);
	test("is_greater_10_signed_s8", is_greater_10_signed_s8,11, 1);
	test("is_greater_10_signed_s8", is_greater_10_signed_s8,13, 1);

	test("is_less_than_equal_10_signed_s8", is_less_than_equal_10_signed_s8,3, 1);
	test("is_less_than_equal_10_signed_s8", is_less_than_equal_10_signed_s8,7, 1);
	test("is_less_than_equal_10_signed_s8", is_less_than_equal_10_signed_s8,11, 0);
	test("is_less_than_equal_10_signed_s8", is_less_than_equal_10_signed_s8,13, 0);

	/* comparison, more bytes */
	test("is_greater_10_unsigned", is_greater_10_unsigned,3, 0);
	test("is_greater_10_unsigned", is_greater_10_unsigned,7, 0);
	test("is_greater_10_unsigned", is_greater_10_unsigned,11, 1);
	test("is_greater_10_unsigned", is_greater_10_unsigned,13, 1);

	test("is_less_than_equal_10_unsigned", is_less_than_equal_10_unsigned,3, 1);
	test("is_less_than_equal_10_unsigned", is_less_than_equal_10_unsigned,7, 1);
	test("is_less_than_equal_10_unsigned", is_less_than_equal_10_unsigned,11, 0);
	test("is_less_than_equal_10_unsigned", is_less_than_equal_10_unsigned,13, 0);

	test("is_greater_10_signed", is_greater_10_signed,3, 0);
	test("is_greater_10_signed", is_greater_10_signed,7, 0);
	test("is_greater_10_signed", is_greater_10_signed,11, 1);
	test("is_greater_10_signed", is_greater_10_signed,13, 1);

	test("is_less_than_equal_10_signed", is_less_than_equal_10_signed,3, 1);
	test("is_less_than_equal_10_signed", is_less_than_equal_10_signed,7, 1);
	test("is_less_than_equal_10_signed", is_less_than_equal_10_signed,11, 0);
	test("is_less_than_equal_10_signed", is_less_than_equal_10_signed,13, 0);

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
