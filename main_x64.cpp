//
#include <stdio.h>
#include <stdint.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "runtime.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define NONE "\x1B[0m"

extern vector<REGTYPE> vm_stack;
extern map<REGTYPE,REGTYPE> vm_mem;
extern map<string,REGTYPE> vm_regs;
extern map<string,double> vm_regs_double;

void initialize_memory();
void vm_reset()
{
	vm_mem.clear();
	vm_regs.clear();
	vm_regs["rsp"] = 0xC00000000000000;

	/* this is the compiled IL call, loading switch tables and perhaps other
	important data variables in the future */
	initialize_memory();
}

void multiply(void);
int vm_multiply(int a, int b)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = a;
	vm_regs["rsi"] = b;
	/* jump into VM */
	multiply();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void multiply_loop(void);
int vm_multiply_loop(int a, int b)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = a;
	vm_regs["rsi"] = b;
	/* jump into VM */
	multiply();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void exp(void);
int vm_exp(int base, int e)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = base;
	vm_regs["rsi"] = e;
	/* jump into VM */
	exp();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void expmod(void);
int vm_expmod(int base, int e, int m)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = base;
	vm_regs["rsi"] = e;
	vm_regs["rdx"] = m;
	/* jump into VM */
	expmod();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void gcd(void);
int vm_gcd(int a, int b)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = a;
	vm_regs["rsi"] = b;
	/* jump into VM */
	gcd();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void switch_doubler(void);
int vm_switch_doubler(int a)
{
	vm_reset();
	/* sysv: integer args in rdi, rsi, rdx, rcx, r8, r9... */
	vm_regs["rdi"] = a;
	/* jump into VM */
	switch_doubler();
	/* sysv: return value in rax */
	return vm_regs["rax"];
}

void check(int actual, int expected, const char *msg)
{
	if(actual == expected) {
		printf(GREEN "PASSED" NONE " %s (%d is correct)\n", msg, actual);
	}
	else {
		printf(RED "FAILED" NONE " %s (%d is incorrect, expected %d)\n", msg, actual, expected);
		exit(-1);
	}
}

int main(int ac, char **av)
{
	int result;

	/* multiply: easy case with MUL instruction */
	result = vm_multiply(4,7);
	check(result, 28, "multiply(4,7)");

	result = vm_multiply(-4,7);
	check(result, -28, "multiply(-4,7)");

	result = vm_multiply(-4,-7);
	check(result, 28, "multiply(-4,-7)");

	result = vm_multiply(123,456);
	check(result, 56088, "multiply(123,456)");

	/* multiply: using loop */
	result = vm_multiply_loop(4,7);
	check(result, 28, "multiply_loop(4,7)");

	result = vm_multiply_loop(-4,7);
	check(result, -28, "multiply_loop(-4,7)");

	result = vm_multiply_loop(-4,-7);
	check(result, 28, "multiply_loop(-4,-7)");

	result = vm_multiply_loop(123,456);
	check(result, 56088, "multiply_loop(123,456)");

	/* exponentiate */
	result = vm_exp(4,7);
	check(result, 16384, "exp(4,7)");

	result = vm_exp(2,16);
	check(result, 65536, "exp(2,16)");

	result = vm_exp(3,17);
	check(result, 129140163, "exp(3,17)");

	result = vm_exp(17,3);
	check(result, 4913, "exp(17,3)");

	/* exponentiate with a modulus */
	result = vm_expmod(4,7,5);
	check(result, 4, "expmod(4,7,5)");

	result = vm_expmod(2,16,17);
	check(result, 1, "expmod(2,16,17)");

	result = vm_expmod(3,17,19);
	check(result, 13, "expmod(3,17,19)");

	result = vm_expmod(17,3,23);
	check(result, 14, "expmod(17,3,23)");

	/* greatest common divisor */
	result = vm_gcd(5,15);
	check(result, 5, "gcd(5,15)");

	result = vm_gcd(16,24);
	check(result, 8, "gcd(16,24)");	

	result = vm_gcd(51,77);
	check(result, 1, "gcd(51,77)");

	result = vm_gcd(51,119);
	check(result, 17, "gcd(51,119)");

	/* switch statements */
	result = vm_switch_doubler(0);
	check(result, 0, "switch_doubler(0)");

	result = vm_switch_doubler(2);
	check(result, 4, "switch_doubler(2)");	

	result = vm_switch_doubler(999);
	check(result, -1, "switch_doubler(999)");

	result = vm_switch_doubler(9);
	check(result, 18, "switch_doubler(9)");	
}
