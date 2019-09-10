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

void check(int actual, int expected, const char *msg)
{
	if(actual == expected)
		printf("\x1B[32m" "PASSED" "\x1B[0m" " %s (%d is correct)\n", msg, actual);
	else {
		printf("\x1B[31m" "FAILED" "\x1B[0m" " %s (%d is incorrect, expected %d)\n", msg, actual, expected);
		exit(-1);
	}
}

void __divu16(void);

int main(int ac, char **av)
{
	int result;

	result = vm_call(life_universe_everything);
	check(result, 42, "life_universe_everything()");

	/* add */
	result = vm_call(add, 4,7);
	check(result, 11, "add(4,7)");

	result = vm_call(add, -4,7);
	check(result, 3, "add(-4,7)");

	result = vm_call(add, -4,-7);
	check(result, -11, "add(-4,-7)");

	result = vm_call(add, 123,456);
	check(result, 579, "add(123,456)");

	/* comparison, 1 byte */
	result = vm_call(is_greater_10_unsigned_u8, 3);
	check(result, 0, "is_greater_10_unsigned_u8(3)");
	result = vm_call(is_greater_10_unsigned_u8, 7);
	check(result, 0, "is_greater_10_unsigned_u8(7)");
	result = vm_call(is_greater_10_unsigned_u8, 11);
	check(result, 1, "is_greater_10_unsigned_u8(11)");
	result = vm_call(is_greater_10_unsigned_u8, 13);
	check(result, 1, "is_greater_10_unsigned_u8(13)");

	result = vm_call(than_equal_10_unsigned_u8, 3);
	check(result, 1, "than_equal_10_unsigned_u8(3)");
	result = vm_call(than_equal_10_unsigned_u8, 7);
	check(result, 1, "than_equal_10_unsigned_u8(7)");
	result = vm_call(than_equal_10_unsigned_u8, 11);
	check(result, 0, "than_equal_10_unsigned_u8(11)");
	result = vm_call(than_equal_10_unsigned_u8, 13);
	check(result, 0, "than_equal_10_unsigned_u8(13)");

	result = vm_call(is_greater_10_signed_s8, 3);
	check(result, 0, "is_greater_10_signed_s8(3)");
	result = vm_call(is_greater_10_signed_s8, 7);
	check(result, 0, "is_greater_10_signed_s8(7)");
	result = vm_call(is_greater_10_signed_s8, 11);
	check(result, 1, "is_greater_10_signed_s8(11)");
	result = vm_call(is_greater_10_signed_s8, 13);
	check(result, 1, "is_greater_10_signed_s8(13)");

	result = vm_call(is_less_than_equal_10_signed_s8, 3);
	check(result, 1, "is_less_than_equal_10_signed_s8(3)");
	result = vm_call(is_less_than_equal_10_signed_s8, 7);
	check(result, 1, "is_less_than_equal_10_signed_s8(7)");
	result = vm_call(is_less_than_equal_10_signed_s8, 11);
	check(result, 0, "is_less_than_equal_10_signed_s8(11)");
	result = vm_call(is_less_than_equal_10_signed_s8, 13);
	check(result, 0, "is_less_than_equal_10_signed_s8(13)");

	/* comparison, more bytes */
	result = vm_call(is_greater_10_unsigned, 3);
	check(result, 0, "is_greater_10_unsigned(3)");
	result = vm_call(is_greater_10_unsigned, 7);
	check(result, 0, "is_greater_10_unsigned(7)");
	result = vm_call(is_greater_10_unsigned, 11);
	check(result, 1, "is_greater_10_unsigned(11)");
	result = vm_call(is_greater_10_unsigned, 13);
	check(result, 1, "is_greater_10_unsigned(13)");

	result = vm_call(is_less_than_equal_10_unsigned, 3);
	check(result, 1, "is_less_than_equal_10_unsigned(3)");
	result = vm_call(is_less_than_equal_10_unsigned, 7);
	check(result, 1, "is_less_than_equal_10_unsigned(7)");
	result = vm_call(is_less_than_equal_10_unsigned, 11);
	check(result, 0, "is_less_than_equal_10_unsigned(11)");
	result = vm_call(is_less_than_equal_10_unsigned, 13);
	check(result, 0, "is_less_than_equal_10_unsigned(13)");

	result = vm_call(is_greater_10_signed, 3);
	check(result, 0, "is_greater_10_signed(3)");
	result = vm_call(is_greater_10_signed, 7);
	check(result, 0, "is_greater_10_signed(7)");
	result = vm_call(is_greater_10_signed, 11);
	check(result, 1, "is_greater_10_signed(11)");
	result = vm_call(is_greater_10_signed, 13);
	check(result, 1, "is_greater_10_signed(13)");

	result = vm_call(is_less_than_equal_10_signed, 3);
	check(result, 1, "is_less_than_equal_10_signed(3)");
	result = vm_call(is_less_than_equal_10_signed, 7);
	check(result, 1, "is_less_than_equal_10_signed(7)");
	result = vm_call(is_less_than_equal_10_signed, 11);
	check(result, 0, "is_less_than_equal_10_signed(11)");
	result = vm_call(is_less_than_equal_10_signed, 13);
	check(result, 0, "is_less_than_equal_10_signed(13)");

    /* triangle numbers */
	result = vm_call(triangle_up, 4);
	check(result, 10, "triangle_up(4)");

	result = vm_call(triangle_up, 7);
	check(result, 28, "triangle_up(7)");

	result = vm_call(triangle_up, 10);
	check(result, 55, "triangle_up(10)");

	result = vm_call(triangle_up, 100);
	check(result, 5050, "triangle_up(100)");

	result = vm_call(triangle_down, 4);
	check(result, 10, "triangle_down(4)");

	result = vm_call(triangle_down, 7);
	check(result, 28, "triangle_down(7)");

	result = vm_call(triangle_down, 10);
	check(result, 55, "triangle_down(10)");

	result = vm_call(triangle_down, 100);
	check(result, 5050, "triangle_down(100)");

	/* multiply: easy case with MUL instruction, else kinda tough */
	result = vm_call(multiply, 4, 7);
	check(result, 28, "multiply(4, 7)");

	result = vm_call(multiply, -4, 7);
	check(result, -28, "multiply(-4, 7)");

	result = vm_call(multiply, -4, -7);
	check(result, 28, "multiply(-4, -7)");

	result = vm_call(multiply, 151, 217);
	check(result, 32767, "multiply(151, 217)");

	/* multiply: using loop */
	result = vm_call(multiply_loop, 4, 7);
	check(result, 28, "multiply_loop(4, 7)");

	result = vm_call(multiply_loop, -4, 7);
	check(result, -28, "multiply_loop(-4, 7)");

	result = vm_call(multiply_loop, -4, -7);
	check(result, 28, "multiply_loop(-4, -7)");

	result = vm_call(multiply_loop, 151, 217);
	check(result, 32767, "multiply_loop(151, 217)");

	/* div */
	result = vm_call(div, 4, -2);
	check(result, -2, "div(4, -2)");

	result = vm_call(div, 4, 7);
	check(result, 0, "div(4, 7)");

	result = vm_call(div, 7, 4);
	check(result, 1, "div(7, 4)");

	result = vm_call(div, 28, 7);
	check(result, 4, "div(28, 7)");

	result = vm_call(div, 151, -50);
	check(result, -3, "div(151, -50)");

	/* mod */
	result = vm_call(mod, 4, 7);
	check(result, 4, "mod(4, 7)");

	result = vm_call(mod, 7, 4);
	check(result, 3, "mod(7, 4)");

	result = vm_call(mod, 28, 7);
	check(result, 0, "mod(28, 7)");

	result = vm_call(mod, 151, 50);
	check(result, 1, "mod(151, 50)");

	/* exponentiate */
	result = vm_call(exp_dummy, 4, 7);
	check(result, 16384, "exp(4, 7)");

	result = vm_call(exp_dummy, 2, 14);
	check(result, 16384, "exp(2, 14)");

	result = vm_call(exp_dummy, 3, 7);
	check(result, 2187, "exp(3, 7)");

	result = vm_call(exp_dummy, -2, 7);
	check(result, -128, "exp(-2, 7)");

	/* exponentiate with a modulus */
	result = vm_call(expmod, 4,7,5);
	check(result, 4, "expmod(4,7,5)");

	result = vm_call(expmod, 2,16,17);
	check(result, 1, "expmod(2,16,17)");

	result = vm_call(expmod, 3,17,19);
	check(result, 13, "expmod(3,17,19)");

	result = vm_call(expmod, 17,3,23);
	check(result, 14, "expmod(17,3,23)");

	/* greatest common divisor */
	result = vm_call(gcd, 5,15);
	check(result, 5, "gcd(5,15)");

	result = vm_call(gcd, 16,24);
	check(result, 8, "gcd(16,24)");

	result = vm_call(gcd, 51,77);
	check(result, 1, "gcd(51,77)");

	result = vm_call(gcd, 51,119);
	check(result, 17, "gcd(51,119)");

	/* recursion */
	result = vm_call(factorial, 0);
	check(result, 1, "factorial(0)");

	result = vm_call(factorial, 5);
	check(result, 120, "factorial(5)");

#if REGWIDTH == 16
	/* be nice and don't let tests set MSB -> negative */
	result = vm_call(factorial, 6);
	check(result, 720, "factorial(6)");

	result = vm_call(factorial, 7);
	check(result, 5040, "factorial(7)");
#else
	result = vm_call(factorial, 8);
	check(result, 40320, "factorial(8)");

	result = vm_call(factorial, 11);
	check(result, 39916800, "factorial(11)");
#endif

	/* recursive version: greatest common divisor */
	result = vm_call(gcd_recursive, 5,15);
	check(result, 5, "gcd_recursive(5,15)");

	result = vm_call(gcd_recursive, 16,24);
	check(result, 8, "gcd_recursive(16,24)");

	result = vm_call(gcd_recursive, 51,77);
	check(result, 1, "gcd_recursive(51,77)");

	result = vm_call(gcd_recursive, 51,119);
	check(result, 17, "gcd_recursive(51,119)");

	/* switch statements */
	result = vm_call(switch_doubler, 0);
	check(result, 0, "switch_doubler(0)");

	result = vm_call(switch_doubler, 2);
	check(result, 4, "switch_doubler(2)");

	result = vm_call(switch_doubler, 999);
	check(result, -1, "switch_doubler(999)");

	result = vm_call(switch_doubler, 9);
	check(result, 18, "switch_doubler(9)");
}
