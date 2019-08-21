// tests.o: ELF 32-bit LSB relocatable, ARM, EABI5 version 1 (SYSV), with debug_info, not stripped

#include <stdint.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "runtime.h"

extern map<REGTYPE,REGTYPE> vm_mem;

/* int32_t multiply(int32_t arg1, int32_t arg2) */
void multiply(void)
{
	loc_0:
	SET_REG("sp", SUB(REG("sp"), 4));
	STORE(REG("sp"), REG("r11"));
	SET_REG("r11", REG("sp"));
	SET_REG("sp", SUB(REG("sp"), 12));
	STORE(SUB(REG("r11"), 8), REG("r0"));
	STORE(SUB(REG("r11"), 12), REG("r1"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r2", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", MUL(REG("r2"), REG("r3")));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", REG("r11"));
	SET_REG("r11", LOAD(REG("sp")));
	SET_REG("sp", ADD(REG("sp"), 4));
	// jump(lr)
	return;

}

/* int32_t multiply_loop(int32_t arg1, int32_t arg2) */
void multiply_loop(void)
{
	loc_0:
	SET_REG("sp", SUB(REG("sp"), 4));
	STORE(REG("sp"), REG("r11"));
	SET_REG("r11", REG("sp"));
	SET_REG("sp", SUB(REG("sp"), 20));
	STORE(SUB(REG("r11"), 16), REG("r0"));
	STORE(SUB(REG("r11"), 20), REG("r1"));
	SET_REG("r3", 0);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	SET_REG("r3", 0);
	STORE(SUB(REG("r11"), 12), REG("r3"));
	goto loc_11;

	loc_11:
	SET_REG("r2", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_SLT(REG("r2"), REG("r3")))
		goto loc_14;
	else
		goto loc_22;

	loc_14:
	SET_REG("r2", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	SET_REG("r3", ADD(REG("r2"), REG("r3")));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", ADD(REG("r3"), 1));
	STORE(SUB(REG("r11"), 12), REG("r3"));
	goto loc_11;

	loc_22:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_SGE(REG("r3"), 0))
		goto loc_24;
	else
		goto loc_30;

	loc_24:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", REG("r11"));
	SET_REG("r11", LOAD(REG("sp")));
	SET_REG("sp", ADD(REG("sp"), 4));
	// jump(lr)
	return;

	loc_30:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r3", SUB(0, REG("r3")));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_24;

}

/* int32_t exp(int32_t arg1, int32_t arg2) */
void exp(void)
{
	loc_0:
	SET_REG("sp", SUB(REG("sp"), 4));
	STORE(REG("sp"), REG("r11"));
	SET_REG("r11", REG("sp"));
	SET_REG("sp", SUB(REG("sp"), 20));
	STORE(SUB(REG("r11"), 16), REG("r0"));
	STORE(SUB(REG("r11"), 20), REG("r1"));
	SET_REG("r3", 1);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	SET_REG("r3", 0);
	STORE(SUB(REG("r11"), 12), REG("r3"));
	goto loc_11;

	loc_11:
	SET_REG("r2", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_SLT(REG("r2"), REG("r3")))
		goto loc_14;
	else
		goto loc_22;

	loc_14:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r2", LOAD(SUB(REG("r11"), 16)));
	SET_REG("r3", MUL(REG("r2"), REG("r3")));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", ADD(REG("r3"), 1));
	STORE(SUB(REG("r11"), 12), REG("r3"));
	goto loc_11;

	loc_22:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", REG("r11"));
	SET_REG("r11", LOAD(REG("sp")));
	SET_REG("sp", ADD(REG("sp"), 4));
	// jump(lr)
	return;

}

/* int32_t expmod(int32_t arg1, int32_t arg2, int32_t arg3) */
void expmod(void)
{
	loc_0:
	PUSH(REG("lr"));
	PUSH(REG("r11"));
	SET_REG("r11", ADD(REG("sp"), 4));
	SET_REG("sp", SUB(REG("sp"), 24));
	STORE(SUB(REG("r11"), 16), REG("r0"));
	STORE(SUB(REG("r11"), 20), REG("r1"));
	STORE(SUB(REG("r11"), 24), REG("r2"));
	SET_REG("r3", 1);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	STORE(SUB(REG("r11"), 12), REG("r3"));
	goto loc_12;

	loc_12:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_NE(REG("r3"), 0))
		goto loc_14;
	else
		goto loc_17;

	loc_14:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	SET_REG("r3", AND(REG("r3"), 1));
	if(CMP_E(REG("r3"), 0))
		goto loc_22;
	else
		goto loc_34;

	loc_17:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", SUB(REG("r11"), 4));
	SET_REG("r11", POP());
	// jump(pop)
	return;

	loc_22:
	SET_REG("r3", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r2", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", MUL(REG("r2"), REG("r3")));
	SET_REG("r0", REG("r3"));
	SET_REG("r1", LOAD(SUB(REG("r11"), 24)));
	// call(0x380)
	__aeabi_idivmod();
	SET_REG("r3", REG("r1"));
	STORE(SUB(REG("r11"), 12), REG("r3"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	SET_REG("r3", ASR(REG("r3"), 1));
	STORE(SUB(REG("r11"), 20), REG("r3"));
	goto loc_12;

	loc_34:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r2", LOAD(SUB(REG("r11"), 12)));
	SET_REG("r3", MUL(REG("r2"), REG("r3")));
	SET_REG("r0", REG("r3"));
	SET_REG("r1", LOAD(SUB(REG("r11"), 24)));
	// call(0x380)
	__aeabi_idivmod();
	SET_REG("r3", REG("r1"));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_22;

}

/* int32_t gcd(int32_t arg1, int32_t arg2) */
void gcd(void)
{
	loc_0:
	PUSH(REG("lr"));
	PUSH(REG("r11"));
	SET_REG("r11", ADD(REG("sp"), 4));
	SET_REG("sp", SUB(REG("sp"), 16));
	STORE(SUB(REG("r11"), 16), REG("r0"));
	STORE(SUB(REG("r11"), 20), REG("r1"));
	goto loc_7;

	loc_7:
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	if(CMP_NE(REG("r3"), 0))
		goto loc_9;
	else
		goto loc_11;

	loc_9:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_NE(REG("r3"), 0))
		goto loc_14;
	else
		goto loc_17;

	loc_11:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_20;

	loc_14:
	SET_REG("r2", LOAD(SUB(REG("r11"), 16)));
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	if(CMP_SLE(REG("r2"), REG("r3")))
		goto loc_25;
	else
		goto loc_32;

	loc_17:
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_20;

	loc_20:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", SUB(REG("r11"), 4));
	SET_REG("r11", POP());
	// jump(pop)
	return;

	loc_25:
	SET_REG("r3", LOAD(SUB(REG("r11"), 20)));
	SET_REG("r0", REG("r3"));
	SET_REG("r1", LOAD(SUB(REG("r11"), 16)));
	// call(0x380)
	__aeabi_idivmod();
	SET_REG("r3", REG("r1"));
	STORE(SUB(REG("r11"), 20), REG("r3"));
	goto loc_39;

	loc_32:
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	SET_REG("r0", REG("r3"));
	SET_REG("r1", LOAD(SUB(REG("r11"), 20)));
	// call(0x380)
	__aeabi_idivmod();
	SET_REG("r3", REG("r1"));
	STORE(SUB(REG("r11"), 16), REG("r3"));
	goto loc_39;

	loc_39:
	goto loc_7;

}

/* int32_t switch_doubler(int32_t arg1) */
void switch_doubler(void)
{
	loc_0:
	SET_REG("sp", SUB(REG("sp"), 4));
	STORE(REG("sp"), REG("r11"));
	SET_REG("r11", REG("sp"));
	SET_REG("sp", SUB(REG("sp"), 20));
	STORE(SUB(REG("r11"), 16), REG("r0"));
	SET_REG("r3", LOAD(SUB(REG("r11"), 16)));
	if(CMP_ULE(REG("r3"), 10))
		goto loc_7;
	else
		goto loc_8;

	loc_7:
	// jump(0x278 + (r3 << 2) => 9 @ 0x274, 10 @ 0x278, 11 @ 0x27c, 12 @ 0x280, 13 @ 0x284, 14 @ 0x288, 15 @ 0x28c, 16 @ 0x290, 17 @ 0x294, 18 @ 0x298, 19 @ 0x29c, 20 @ 0x2a0)
	switch(ADD(0x278, LSL(REG("r3"), 2)))
	{
		case 0x274: goto loc_9;
		case 0x278: goto loc_10;
		case 0x27C: goto loc_11;
		case 0x280: goto loc_12;
		case 0x284: goto loc_13;
		case 0x288: goto loc_14;
		case 0x28C: goto loc_15;
		case 0x290: goto loc_16;
		case 0x294: goto loc_17;
		case 0x298: goto loc_18;
		case 0x29C: goto loc_19;
		case 0x2A0: goto loc_20;
		default: printf("switch fucked\n"); while(1);
	}

	loc_8:
	goto loc_9;

	loc_9:
	goto loc_21;

	loc_10:
	goto loc_24;

	loc_11:
	goto loc_27;

	loc_12:
	goto loc_30;

	loc_13:
	goto loc_33;

	loc_14:
	goto loc_36;

	loc_15:
	goto loc_39;

	loc_16:
	goto loc_42;

	loc_17:
	goto loc_45;

	loc_18:
	goto loc_48;

	loc_19:
	goto loc_51;

	loc_20:
	goto loc_54;

	loc_21:
	SET_REG("r3", NOT(0));
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_24:
	SET_REG("r3", 0);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_27:
	SET_REG("r3", 2);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_30:
	SET_REG("r3", 4);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_33:
	SET_REG("r3", 6);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_36:
	SET_REG("r3", 8);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_39:
	SET_REG("r3", 10);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_42:
	SET_REG("r3", 12);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_45:
	SET_REG("r3", 14);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_48:
	SET_REG("r3", 16);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_51:
	SET_REG("r3", 18);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_54:
	SET_REG("r3", 20);
	STORE(SUB(REG("r11"), 8), REG("r3"));
	goto loc_57;

	loc_57:
	SET_REG("r3", LOAD(SUB(REG("r11"), 8)));
	SET_REG("r0", REG("r3"));
	SET_REG("sp", REG("r11"));
	SET_REG("r11", LOAD(REG("sp")));
	SET_REG("sp", ADD(REG("sp"), 4));
	// jump(lr)
	return;

}

void initialize_memory()
{
	
}

map<string,struct RegisterInfo> regInfos = {
	{"r0", {0, "r0", 0, 4, 0}}, /* <reg: size 4, offset 0 in r0> */
	{"r1", {1, "r1", 0, 4, 0}}, /* <reg: size 4, offset 0 in r1> */
	{"r2", {2, "r2", 0, 4, 0}}, /* <reg: size 4, offset 0 in r2> */
	{"r3", {3, "r3", 0, 4, 0}}, /* <reg: size 4, offset 0 in r3> */
	{"r4", {4, "r4", 0, 4, 0}}, /* <reg: size 4, offset 0 in r4> */
	{"r5", {5, "r5", 0, 4, 0}}, /* <reg: size 4, offset 0 in r5> */
	{"r6", {6, "r6", 0, 4, 0}}, /* <reg: size 4, offset 0 in r6> */
	{"r7", {7, "r7", 0, 4, 0}}, /* <reg: size 4, offset 0 in r7> */
	{"r8", {8, "r8", 0, 4, 0}}, /* <reg: size 4, offset 0 in r8> */
	{"r9", {9, "r9", 0, 4, 0}}, /* <reg: size 4, offset 0 in r9> */
	{"r10", {10, "r10", 0, 4, 0}}, /* <reg: size 4, offset 0 in r10> */
	{"r11", {11, "r11", 0, 4, 0}}, /* <reg: size 4, offset 0 in r11> */
	{"r12", {12, "r12", 0, 4, 0}}, /* <reg: size 4, offset 0 in r12> */
	{"sp", {13, "sp", 0, 4, 0}}, /* <reg: size 4, offset 0 in sp> */
	{"lr", {14, "lr", 0, 4, 0}}, /* <reg: size 4, offset 0 in lr> */
	{"pc", {15, "pc", 0, 4, 0}}, /* <reg: size 4, offset 0 in pc> */
	{"s0", {16, "q0", 0, 4, 0}}, /* <reg: size 4, offset 0 in q0> */
	{"s1", {17, "q0", 4, 4, 0}}, /* <reg: size 4, offset 4 in q0> */
	{"s2", {18, "q0", 8, 4, 0}}, /* <reg: size 4, offset 8 in q0> */
	{"s3", {19, "q0", 12, 4, 0}}, /* <reg: size 4, offset 12 in q0> */
	{"s4", {20, "q1", 0, 4, 0}}, /* <reg: size 4, offset 0 in q1> */
	{"s5", {21, "q1", 4, 4, 0}}, /* <reg: size 4, offset 4 in q1> */
	{"s6", {22, "q1", 8, 4, 0}}, /* <reg: size 4, offset 8 in q1> */
	{"s7", {23, "q1", 12, 4, 0}}, /* <reg: size 4, offset 12 in q1> */
	{"s8", {24, "q2", 0, 4, 0}}, /* <reg: size 4, offset 0 in q2> */
	{"s9", {25, "q2", 4, 4, 0}}, /* <reg: size 4, offset 4 in q2> */
	{"s10", {26, "q2", 8, 4, 0}}, /* <reg: size 4, offset 8 in q2> */
	{"s11", {27, "q2", 12, 4, 0}}, /* <reg: size 4, offset 12 in q2> */
	{"s12", {28, "q3", 0, 4, 0}}, /* <reg: size 4, offset 0 in q3> */
	{"s13", {29, "q3", 4, 4, 0}}, /* <reg: size 4, offset 4 in q3> */
	{"s14", {30, "q3", 8, 4, 0}}, /* <reg: size 4, offset 8 in q3> */
	{"s15", {31, "q3", 12, 4, 0}}, /* <reg: size 4, offset 12 in q3> */
	{"s16", {32, "q4", 0, 4, 0}}, /* <reg: size 4, offset 0 in q4> */
	{"s17", {33, "q4", 4, 4, 0}}, /* <reg: size 4, offset 4 in q4> */
	{"s18", {34, "q4", 8, 4, 0}}, /* <reg: size 4, offset 8 in q4> */
	{"s19", {35, "q4", 12, 4, 0}}, /* <reg: size 4, offset 12 in q4> */
	{"s20", {36, "q5", 0, 4, 0}}, /* <reg: size 4, offset 0 in q5> */
	{"s21", {37, "q5", 4, 4, 0}}, /* <reg: size 4, offset 4 in q5> */
	{"s22", {38, "q5", 8, 4, 0}}, /* <reg: size 4, offset 8 in q5> */
	{"s23", {39, "q5", 12, 4, 0}}, /* <reg: size 4, offset 12 in q5> */
	{"s24", {40, "q6", 0, 4, 0}}, /* <reg: size 4, offset 0 in q6> */
	{"s25", {41, "q6", 4, 4, 0}}, /* <reg: size 4, offset 4 in q6> */
	{"s26", {42, "q6", 8, 4, 0}}, /* <reg: size 4, offset 8 in q6> */
	{"s27", {43, "q6", 12, 4, 0}}, /* <reg: size 4, offset 12 in q6> */
	{"s28", {44, "q7", 0, 4, 0}}, /* <reg: size 4, offset 0 in q7> */
	{"s29", {45, "q7", 4, 4, 0}}, /* <reg: size 4, offset 4 in q7> */
	{"s30", {46, "q7", 8, 4, 0}}, /* <reg: size 4, offset 8 in q7> */
	{"s31", {47, "q7", 12, 4, 0}}, /* <reg: size 4, offset 12 in q7> */
	{"d0", {48, "q0", 0, 8, 0}}, /* <reg: size 8, offset 0 in q0> */
	{"d1", {49, "q0", 8, 8, 0}}, /* <reg: size 8, offset 8 in q0> */
	{"d2", {50, "q1", 0, 8, 0}}, /* <reg: size 8, offset 0 in q1> */
	{"d3", {51, "q1", 8, 8, 0}}, /* <reg: size 8, offset 8 in q1> */
	{"d4", {52, "q2", 0, 8, 0}}, /* <reg: size 8, offset 0 in q2> */
	{"d5", {53, "q2", 8, 8, 0}}, /* <reg: size 8, offset 8 in q2> */
	{"d6", {54, "q3", 0, 8, 0}}, /* <reg: size 8, offset 0 in q3> */
	{"d7", {55, "q3", 8, 8, 0}}, /* <reg: size 8, offset 8 in q3> */
	{"d8", {56, "q4", 0, 8, 0}}, /* <reg: size 8, offset 0 in q4> */
	{"d9", {57, "q4", 8, 8, 0}}, /* <reg: size 8, offset 8 in q4> */
	{"d10", {58, "q5", 0, 8, 0}}, /* <reg: size 8, offset 0 in q5> */
	{"d11", {59, "q5", 8, 8, 0}}, /* <reg: size 8, offset 8 in q5> */
	{"d12", {60, "q6", 0, 8, 0}}, /* <reg: size 8, offset 0 in q6> */
	{"d13", {61, "q6", 8, 8, 0}}, /* <reg: size 8, offset 8 in q6> */
	{"d14", {62, "q7", 0, 8, 0}}, /* <reg: size 8, offset 0 in q7> */
	{"d15", {63, "q7", 8, 8, 0}}, /* <reg: size 8, offset 8 in q7> */
	{"d16", {64, "q8", 0, 8, 0}}, /* <reg: size 8, offset 0 in q8> */
	{"d17", {65, "q8", 8, 8, 0}}, /* <reg: size 8, offset 8 in q8> */
	{"d18", {66, "q9", 0, 8, 0}}, /* <reg: size 8, offset 0 in q9> */
	{"d19", {67, "q9", 8, 8, 0}}, /* <reg: size 8, offset 8 in q9> */
	{"d20", {68, "q10", 0, 8, 0}}, /* <reg: size 8, offset 0 in q10> */
	{"d21", {69, "q10", 8, 8, 0}}, /* <reg: size 8, offset 8 in q10> */
	{"d22", {70, "q11", 0, 8, 0}}, /* <reg: size 8, offset 0 in q11> */
	{"d23", {71, "q11", 8, 8, 0}}, /* <reg: size 8, offset 8 in q11> */
	{"d24", {72, "q12", 0, 8, 0}}, /* <reg: size 8, offset 0 in q12> */
	{"d25", {73, "q12", 8, 8, 0}}, /* <reg: size 8, offset 8 in q12> */
	{"d26", {74, "q13", 0, 8, 0}}, /* <reg: size 8, offset 0 in q13> */
	{"d27", {75, "q13", 8, 8, 0}}, /* <reg: size 8, offset 8 in q13> */
	{"d28", {76, "q14", 0, 8, 0}}, /* <reg: size 8, offset 0 in q14> */
	{"d29", {77, "q14", 8, 8, 0}}, /* <reg: size 8, offset 8 in q14> */
	{"d30", {78, "q15", 0, 8, 0}}, /* <reg: size 8, offset 0 in q15> */
	{"d31", {79, "q15", 8, 8, 0}}, /* <reg: size 8, offset 8 in q15> */
	{"q0", {80, "q0", 0, 16, 0}}, /* <reg: size 16, offset 0 in q0> */
	{"q1", {81, "q1", 0, 16, 0}}, /* <reg: size 16, offset 0 in q1> */
	{"q2", {82, "q2", 0, 16, 0}}, /* <reg: size 16, offset 0 in q2> */
	{"q3", {83, "q3", 0, 16, 0}}, /* <reg: size 16, offset 0 in q3> */
	{"q4", {84, "q4", 0, 16, 0}}, /* <reg: size 16, offset 0 in q4> */
	{"q5", {85, "q5", 0, 16, 0}}, /* <reg: size 16, offset 0 in q5> */
	{"q6", {86, "q6", 0, 16, 0}}, /* <reg: size 16, offset 0 in q6> */
	{"q7", {87, "q7", 0, 16, 0}}, /* <reg: size 16, offset 0 in q7> */
	{"q8", {88, "q8", 0, 16, 0}}, /* <reg: size 16, offset 0 in q8> */
	{"q9", {89, "q9", 0, 16, 0}}, /* <reg: size 16, offset 0 in q9> */
	{"q10", {90, "q10", 0, 16, 0}}, /* <reg: size 16, offset 0 in q10> */
	{"q11", {91, "q11", 0, 16, 0}}, /* <reg: size 16, offset 0 in q11> */
	{"q12", {92, "q12", 0, 16, 0}}, /* <reg: size 16, offset 0 in q12> */
	{"q13", {93, "q13", 0, 16, 0}}, /* <reg: size 16, offset 0 in q13> */
	{"q14", {94, "q14", 0, 16, 0}}, /* <reg: size 16, offset 0 in q14> */
	{"q15", {95, "q15", 0, 16, 0}}, /* <reg: size 16, offset 0 in q15> */
};

string stackRegName = "sp";
