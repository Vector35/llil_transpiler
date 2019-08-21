#include <stdio.h>
#include <stdint.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

/* VM components */
#include "runtime.h"
extern vector<REGTYPE> vm_stack;
extern map<REGTYPE,REGTYPE> vm_mem;
extern map<string,REGTYPE> vm_regs;
extern map<string,double> vm_regs_double;

/* functions from generated tests_il.o we'll be using */
void initialize_memory();
void multiply();
void multiply_loop();
void exp();
void expmod();
void gcd();
void gcd_recursive();
void switch_doubler();
void factorial();

/* architecture-specific VM utilities to init stack, set args, return values */
#ifdef ARCH_X64
void vm_init_stack() { vm_regs["rsp"] = 0xC00000000000000; }
void vm_set_arg0(int a) { vm_regs["rdi"] = a; }
void vm_set_arg1(int a) { vm_regs["rsi"] = a; }
void vm_set_arg2(int a) { vm_regs["rdx"] = a; }
int vm_get_retval() { return vm_regs["rax"]; }
#endif

#ifdef ARCH_ARM
void vm_init_stack() { vm_regs["sp"] = 0xC0000000; }
void vm_set_arg0(int a) { vm_regs["r0"] = a; }
void vm_set_arg1(int a) { vm_regs["r1"] = a; }
void vm_set_arg2(int a) { vm_regs["r2"] = a; }
int vm_get_retval() { return vm_regs["r0"]; }
#endif

/* architecture-independent VM utilities */
void vm_reset()
{
	vm_mem.clear();
	vm_regs.clear();
	vm_init_stack();
	/* from tests_il.cpp, generated to include switch lookup tables */
	initialize_memory();
}

typedef void (*VMFUNC)(void);

/* call a 1-arg function in the VM */
int vm_call(VMFUNC pfunc, int a)
{
	vm_reset();
	vm_set_arg0(a);
	pfunc();
	return vm_get_retval();
}

/* call a 2-arg function in the VM */
int vm_call(VMFUNC pfunc, int a, int b)
{
	vm_reset();
	vm_set_arg0(a);
	vm_set_arg1(b);
	pfunc();
	return vm_get_retval();
}

/* call a 2-arg function in the VM */
int vm_call(VMFUNC pfunc, int a, int b, int c)
{
	vm_reset();
	vm_set_arg0(a);
	vm_set_arg1(b);
	vm_set_arg2(c);
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

int main(int ac, char **av)
{
	int result;

	/* multiply: easy case with MUL instruction */
	result = vm_call(multiply, 4,7);
	check(result, 28, "multiply(4,7)");

	result = vm_call(multiply, -4,7);
	check(result, -28, "multiply(-4,7)");

	result = vm_call(multiply, -4,-7);
	check(result, 28, "multiply(-4,-7)");

	result = vm_call(multiply, 123,456);
	check(result, 56088, "multiply(123,456)");

	/* multiply: using loop */
	result = vm_call(multiply_loop, 4,7);
	check(result, 28, "multiply_loop(4,7)");

	result = vm_call(multiply_loop, -4,7);
	check(result, -28, "multiply_loop(-4,7)");

	result = vm_call(multiply_loop, -4,-7);
	check(result, 28, "multiply_loop(-4,-7)");

	result = vm_call(multiply_loop, 123,456);
	check(result, 56088, "multiply_loop(123,456)");

	/* exponentiate */
	result = vm_call(exp, 4,7);
	check(result, 16384, "exp(4,7)");

	result = vm_call(exp, 2,16);
	check(result, 65536, "exp(2,16)");

	result = vm_call(exp, 3,17);
	check(result, 129140163, "exp(3,17)");

	result = vm_call(exp, 17,3);
	check(result, 4913, "exp(17,3)");

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

	/* switch statements */
	result = vm_call(switch_doubler, 0);
	check(result, 0, "switch_doubler(0)");

	result = vm_call(switch_doubler, 2);
	check(result, 4, "switch_doubler(2)");	

	result = vm_call(switch_doubler, 999);
	check(result, -1, "switch_doubler(999)");

	result = vm_call(switch_doubler, 9);
	check(result, 18, "switch_doubler(9)");

	/* recursion */
	result = vm_call(factorial, 0);
	check(result, 1, "factorial(0)");

	result = vm_call(factorial, 5);
	check(result, 120, "factorial(5)");	

	result = vm_call(factorial, 8);
	check(result, 40320, "factorial(8)");

	result = vm_call(factorial, 11);
	check(result, 39916800, "factorial(11)");

	/* recursive version: greatest common divisor */
	result = vm_call(gcd_recursive, 5,15);
	check(result, 5, "gcd_recursive(5,15)");

	result = vm_call(gcd_recursive, 16,24);
	check(result, 8, "gcd_recursive(16,24)");	

	result = vm_call(gcd_recursive, 51,77);
	check(result, 1, "gcd_recursive(51,77)");

	result = vm_call(gcd_recursive, 51,119);
	check(result, 17, "gcd_recursive(51,119)");	
}
