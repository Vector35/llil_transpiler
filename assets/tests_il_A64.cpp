// tests.o: ELF 64-bit LSB relocatable, ARM aarch64, version 1 (SYSV), not stripped

#include <stdint.h>

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "runtime.h"

extern uint8_t vm_mem[VM_MEM_SZ];

void life_universe_everything(void);
void add(void);
void test_byte_e_10(void);
void test_byte_ne_10(void);
void test_byte_slt_10(void);
void test_byte_ult_10(void);
void test_byte_sle_10(void);
void test_byte_ule_10(void);
void test_byte_sge_10(void);
void test_byte_uge_10(void);
void test_byte_sgt_10(void);
void test_byte_ugt_10(void);
void test_byte_neg(void);
void test_byte_pos(void);
void test_word_e_10(void);
void test_word_ne_10(void);
void test_word_slt_10(void);
void test_word_ult_10(void);
void test_word_sle_10(void);
void test_word_ule_10(void);
void test_word_sge_10(void);
void test_word_uge_10(void);
void test_word_sgt_10(void);
void test_word_ugt_10(void);
void test_word_neg(void);
void test_word_pos(void);
void triangle_up(void);
void triangle_down(void);
void multiply_u8(void);
void multiply(void);
void multiply_loop(void);
void div(void);
void mod(void);
void exp_dummy(void);
void expmod(void);
void gcd(void);
void gcd_recursive(void);
void switch_doubler(void);
void factorial(void);
void fp_single_add(void);
void fp_single_sub(void);
void fp_single_mul(void);
void fp_single_div(void);

/* int64_t life_universe_everything() */
void life_universe_everything(void)
{
	loc_0:
	// w0 = 0x2a
	SET_REG32("w0", 0x2A);
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t add(int32_t arg1, int32_t arg2) */
void add(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 8 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 8), REG32("w1"));
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w0 = w8 + w9
	SET_REG32("w0", ADD32(REG32("w8"), REG32("w9")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_e_10(char arg1) */
void test_byte_e_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 != 0xa) then 4 else 6
	if(CMP_NE(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x3c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x3c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x4c else 12 @ 0x40
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x54
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x54
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_ne_10(char arg1) */
void test_byte_ne_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 == 0xa) then 4 else 6
	if(CMP_E(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x74
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x74
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x84 else 12 @ 0x78
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x8c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x8c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_slt_10(char arg1) */
void test_byte_slt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s>= 0xa) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0xac
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0xac
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0xbc else 12 @ 0xb0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0xc4
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0xc4
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_ult_10(char arg1) */
void test_byte_ult_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s>= 0xa) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0xe4
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0xe4
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0xf4 else 12 @ 0xe8
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0xfc
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0xfc
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_sle_10(char arg1) */
void test_byte_sle_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s> 0xa) then 4 else 6
	if(CMP_SGT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x11c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x11c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x12c else 12 @ 0x120
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x134
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x134
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_ule_10(char arg1) */
void test_byte_ule_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s> 0xa) then 4 else 6
	if(CMP_SGT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x154
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x154
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x164 else 12 @ 0x158
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x16c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x16c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_sge_10(char arg1) */
void test_byte_sge_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s< 0xa) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x18c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x18c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x19c else 12 @ 0x190
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x1a4
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x1a4
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_uge_10(char arg1) */
void test_byte_uge_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s< 0xa) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x1c4
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x1c4
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x1d4 else 12 @ 0x1c8
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x1dc
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x1dc
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_sgt_10(char arg1) */
void test_byte_sgt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s<= 0xa) then 4 else 6
	if(CMP_SLE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x1fc
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x1fc
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x20c else 12 @ 0x200
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x214
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x214
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_ugt_10(char arg1) */
void test_byte_ugt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = zx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s<= 0xa) then 4 else 6
	if(CMP_SLE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x234
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x234
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x244 else 12 @ 0x238
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x24c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x24c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_neg(char arg1) */
void test_byte_neg(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s>= 0) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 0))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x26c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x26c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x27c else 12 @ 0x270
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x284
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x284
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_byte_pos(char arg1) */
void test_byte_pos(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xb {var_5}].b = w0.b
	STORE8(ADD64(REG64("sp"), 11), LOW_PART8(REG32("w0")));
	// w8 = sx.d([sp + 0xb {var_5}].b)
	SET_REG32("w8", SX8(LOAD8(ADD64(REG64("sp"), 11))));
	// if (w8 s< 0) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 0))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x2a4
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x2a4
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x2b4 else 12 @ 0x2a8
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x2bc
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x2bc
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_e_10(int16_t arg1) */
void test_word_e_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 != 0xa) then 4 else 6
	if(CMP_NE(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x2dc
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x2dc
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x2ec else 12 @ 0x2e0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x2f4
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x2f4
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_ne_10(int16_t arg1) */
void test_word_ne_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 == 0xa) then 4 else 6
	if(CMP_E(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x314
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x314
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x324 else 12 @ 0x318
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x32c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x32c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_slt_10(int16_t arg1) */
void test_word_slt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s>= 0xa) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x34c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x34c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x35c else 12 @ 0x350
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x364
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x364
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_ult_10(int16_t arg1) */
void test_word_ult_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s>= 0xa) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x384
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x384
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x394 else 12 @ 0x388
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x39c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x39c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_sle_10(int16_t arg1) */
void test_word_sle_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s> 0xa) then 4 else 6
	if(CMP_SGT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x3bc
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x3bc
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x3cc else 12 @ 0x3c0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x3d4
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x3d4
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_ule_10(int16_t arg1) */
void test_word_ule_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s> 0xa) then 4 else 6
	if(CMP_SGT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x3f4
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x3f4
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x404 else 12 @ 0x3f8
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x40c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x40c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_sge_10(int16_t arg1) */
void test_word_sge_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s< 0xa) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x42c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x42c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x43c else 12 @ 0x430
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x444
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x444
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_uge_10(int16_t arg1) */
void test_word_uge_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s< 0xa) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x464
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x464
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x474 else 12 @ 0x468
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x47c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x47c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_sgt_10(int16_t arg1) */
void test_word_sgt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s<= 0xa) then 4 else 6
	if(CMP_SLE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x49c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x49c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x4ac else 12 @ 0x4a0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x4b4
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x4b4
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_ugt_10(int16_t arg1) */
void test_word_ugt_10(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = zx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", ZX32(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s<= 0xa) then 4 else 6
	if(CMP_SLE32(REG32("w8"), 10))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x4d4
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x4d4
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x4e4 else 12 @ 0x4d8
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x4ec
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x4ec
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_neg(int16_t arg1) */
void test_word_neg(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s>= 0) then 4 else 6
	if(CMP_SGE32(REG32("w8"), 0))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x50c
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x50c
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x51c else 12 @ 0x510
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x524
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x524
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t test_word_pos(int16_t arg1) */
void test_word_pos(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xa {var_6}].w = w0.w
	STORE16(ADD64(REG64("sp"), 10), LOW_PART16(REG32("w0")));
	// w8 = sx.d([sp + 0xa {var_6}].w)
	SET_REG32("w8", SX16(LOAD16(ADD64(REG64("sp"), 10))));
	// if (w8 s< 0) then 4 else 6
	if(CMP_SLT32(REG32("w8"), 0))
		goto loc_4;
	else
		goto loc_6;

	loc_4:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 8 @ 0x544
	goto loc_8;

	loc_6:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 8 @ 0x544
	goto loc_8;

	loc_8:
	// if ((w8 & 1) != 0) then 9 @ 0x554 else 12 @ 0x548
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_9;
	else
		goto loc_12;

	loc_9:
	// w8 = 0xd
	SET_REG32("w8", 13);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x55c
	goto loc_15;

	loc_12:
	// w8 = 7
	SET_REG32("w8", 7);
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 15 @ 0x55c
	goto loc_15;

	loc_15:
	// w0 = [sp + 0xc {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 12)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t triangle_up(int32_t arg1) */
void triangle_up(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// w8 = 1
	SET_REG32("w8", 1);
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 4 {var_c}].d = 0
	STORE32(ADD64(REG64("sp"), 4), 0);
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// goto 6 @ 0x57c
	goto loc_6;

	loc_6:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 0xc {var_4}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 12)));
	// if (w8 s> w9) then 9 else 11
	if(CMP_SGT32(REG32("w8"), REG32("w9")))
		goto loc_9;
	else
		goto loc_11;

	loc_9:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 13 @ 0x58c
	goto loc_13;

	loc_11:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 13 @ 0x58c
	goto loc_13;

	loc_13:
	// if ((w8 & 1) != 0) then 14 @ 0x5b0 else 17 @ 0x590
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_14;
	else
		goto loc_17;

	loc_14:
	// w0 = [sp + 4 {var_c}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 4)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_17:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 4 {var_c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 4)));
	// w8 = w9 + w8
	SET_REG32("w8", ADD32(REG32("w9"), REG32("w8")));
	// [sp + 4 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 4), REG32("w8"));
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w8 = w8 + 1
	SET_REG32("w8", ADD32(REG32("w8"), 1));
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// goto 6 @ 0x57c
	goto loc_6;
}

/* uint64_t triangle_down(int32_t arg1) */
void triangle_down(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 4 {var_c}].d = 0
	STORE32(ADD64(REG64("sp"), 4), 0);
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// goto 6 @ 0x5d0
	goto loc_6;

	loc_6:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// if (w8 s<= 0) then 8 else 10
	if(CMP_SLE32(REG32("w8"), 0))
		goto loc_8;
	else
		goto loc_10;

	loc_8:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 12 @ 0x5dc
	goto loc_12;

	loc_10:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 12 @ 0x5dc
	goto loc_12;

	loc_12:
	// if ((w8 & 1) != 0) then 13 @ 0x604 else 16 @ 0x5e0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_13;
	else
		goto loc_16;

	loc_13:
	// w0 = [sp + 4 {var_c}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 4)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_16:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 4 {var_c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 4)));
	// w8 = w9 + w8
	SET_REG32("w8", ADD32(REG32("w9"), REG32("w8")));
	// [sp + 4 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 4), REG32("w8"));
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = -1
	SET_REG32("w9", -1);
	// w8 = w8 + w9
	SET_REG32("w8", ADD32(REG32("w8"), REG32("w9")));
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// goto 6 @ 0x5d0
	goto loc_6;
}

/* uint64_t multiply_u8(char arg1, char arg2) */
void multiply_u8(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xf {var_1}].b = w0.b
	STORE8(ADD64(REG64("sp"), 15), LOW_PART8(REG32("w0")));
	// [sp + 0xe {var_2}].b = w1.b
	STORE8(ADD64(REG64("sp"), 14), LOW_PART8(REG32("w1")));
	// w8 = zx.d([sp + 0xf {var_1}].b)
	SET_REG32("w8", ZX32(LOAD8(ADD64(REG64("sp"), 15))));
	// w9 = zx.d([sp + 0xe {var_2}].b)
	SET_REG32("w9", ZX32(LOAD8(ADD64(REG64("sp"), 14))));
	// w8 = w8 * w9
	SET_REG32("w8", MUL(REG32("w8"), REG32("w9")));
	// w0 = w8
	SET_REG32("w0", REG32("w8"));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t multiply(int32_t arg1, int32_t arg2) */
void multiply(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 8 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 8), REG32("w1"));
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w0 = w8 * w9
	SET_REG32("w0", MUL(REG32("w8"), REG32("w9")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t multiply_loop(int32_t arg1, int32_t arg2) */
void multiply_loop(void)
{
	loc_0:
	// sp = sp - 0x20
	SET_REG64("sp", SUB64(REG64("sp"), 0x20));
	// w8 = 1
	SET_REG32("w8", 1);
	// [sp + 0x1c {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 0x1C), REG32("w0"));
	// [sp + 0x18 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 0x18), REG32("w1"));
	// [sp + 0x10 {var_10}].d = 0
	STORE32(ADD64(REG64("sp"), 0x10), 0);
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// w8 = [sp + 0x18 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x18)));
	// if (w8 s>= 0) then 8 else 10
	if(CMP_SGE32(REG32("w8"), 0))
		goto loc_8;
	else
		goto loc_10;

	loc_8:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 12 @ 0x678
	goto loc_12;

	loc_10:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 12 @ 0x678
	goto loc_12;

	loc_12:
	// if ((w8 & 1) != 0) then 13 @ 0x698 else 15 @ 0x67c
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_13;
	else
		goto loc_15;

	loc_13:
	// [sp + 0x14 {var_c}].d = 0
	STORE32(ADD64(REG64("sp"), 0x14), 0);
	// goto 23 @ 0x69c
	goto loc_23;

	loc_15:
	// w8 = [sp + 0x18 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x18)));
	// w9 = 0
	SET_REG32("w9", 0);
	// w8 = w9 - w8
	SET_REG32("w8", SUB32(REG32("w9"), REG32("w8")));
	// [sp + 0x18 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 0x18), REG32("w8"));
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w8 = w9 - w8
	SET_REG32("w8", SUB32(REG32("w9"), REG32("w8")));
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 13 @ 0x698
	goto loc_13;

	loc_23:
	// w8 = [sp + 0x14 {var_c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x14)));
	// w9 = [sp + 0x18 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x18)));
	// if (w8 s>= w9) then 26 else 28
	if(CMP_SGE32(REG32("w8"), REG32("w9")))
		goto loc_26;
	else
		goto loc_28;

	loc_26:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 30 @ 0x6ac
	goto loc_30;

	loc_28:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 30 @ 0x6ac
	goto loc_30;

	loc_30:
	// if ((w8 & 1) != 0) then 31 @ 0x6d0 else 36 @ 0x6b0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_31;
	else
		goto loc_36;

	loc_31:
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 0x10 {var_10}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w0 = w8 * w9
	SET_REG32("w0", MUL(REG32("w8"), REG32("w9")));
	// sp = sp + 0x20
	SET_REG64("sp", ADD64(REG64("sp"), 0x20));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_36:
	// w8 = [sp + 0x10 {var_10}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w9 = [sp + 0x1c {var_4}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x1C)));
	// w8 = w8 + w9
	SET_REG32("w8", ADD32(REG32("w8"), REG32("w9")));
	// [sp + 0x10 {var_10}].d = w8
	STORE32(ADD64(REG64("sp"), 0x10), REG32("w8"));
	// w8 = [sp + 0x14 {var_c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x14)));
	// w8 = w8 + 1
	SET_REG32("w8", ADD32(REG32("w8"), 1));
	// [sp + 0x14 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 0x14), REG32("w8"));
	// goto 23 @ 0x69c
	goto loc_23;
}

/* uint64_t div(int32_t arg1, int32_t arg2) */
void div(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 8 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 8), REG32("w1"));
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w0 = divs.d(w8, w9)
	SET_REG32("w0", DIVS(REG32("w8"), REG32("w9")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t mod(int32_t arg1, int32_t arg2) */
void mod(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 8 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 8), REG32("w1"));
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w10 = divs.d(w8, w9)
	SET_REG32("w10", DIVS(REG32("w8"), REG32("w9")));
	// w9 = w10 * w9
	SET_REG32("w9", MUL(REG32("w10"), REG32("w9")));
	// w0 = w8 - w9
	SET_REG32("w0", SUB32(REG32("w8"), REG32("w9")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* uint64_t exp_dummy(int32_t arg1, int32_t arg2) */
void exp_dummy(void)
{
	loc_0:
	// sp = sp - 0x20
	SET_REG64("sp", SUB64(REG64("sp"), 0x20));
	// w8 = 1
	SET_REG32("w8", 1);
	// [sp + 0x18 {var_8}].d = w0
	STORE32(ADD64(REG64("sp"), 0x18), REG32("w0"));
	// [sp + 0x14 {var_c}].d = w1
	STORE32(ADD64(REG64("sp"), 0x14), REG32("w1"));
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// w8 = [sp + 0x18 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x18)));
	// if (w8 != 0) then 7 @ 0x750 else 9 @ 0x748
	if(CMP_NE(REG32("w8"), 0))
		goto loc_7;
	else
		goto loc_9;

	loc_7:
	// [sp + 0x10 {var_10_1}].d = 0
	STORE32(ADD64(REG64("sp"), 0x10), 0);
	// goto 11 @ 0x754
	goto loc_11;

	loc_9:
	// [sp + 0x1c {var_4}].d = 0
	STORE32(ADD64(REG64("sp"), 0x1C), 0);
	// goto 14 @ 0x790
	goto loc_14;

	loc_11:
	// w8 = [sp + 0x10 {var_10_1}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w9 = [sp + 0x14 {var_c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x14)));
	// if (w8 s>= w9) then 17 else 19
	if(CMP_SGE32(REG32("w8"), REG32("w9")))
		goto loc_17;
	else
		goto loc_19;

	loc_14:
	// w0 = [sp + 0x1c {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 0x1C)));
	// sp = sp + 0x20
	SET_REG64("sp", ADD64(REG64("sp"), 0x20));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_17:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 21 @ 0x764
	goto loc_21;

	loc_19:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 21 @ 0x764
	goto loc_21;

	loc_21:
	// if ((w8 & 1) != 0) then 22 @ 0x788 else 25 @ 0x768
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_22;
	else
		goto loc_25;

	loc_22:
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// [sp + 0x1c {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 0x1C), REG32("w8"));
	// goto 14 @ 0x790
	goto loc_14;

	loc_25:
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 0x18 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x18)));
	// w8 = w8 * w9
	SET_REG32("w8", MUL(REG32("w8"), REG32("w9")));
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// w8 = [sp + 0x10 {var_10_1}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w8 = w8 + 1
	SET_REG32("w8", ADD32(REG32("w8"), 1));
	// [sp + 0x10 {var_10_1}].d = w8
	STORE32(ADD64(REG64("sp"), 0x10), REG32("w8"));
	// goto 11 @ 0x754
	goto loc_11;
}

/* uint64_t expmod(int32_t arg1, int32_t arg2, int32_t arg3) */
void expmod(void)
{
	loc_0:
	// sp = sp - 0x20
	SET_REG64("sp", SUB64(REG64("sp"), 0x20));
	// w8 = 1
	SET_REG32("w8", 1);
	// [sp + 0x18 {var_8}].d = w0
	STORE32(ADD64(REG64("sp"), 0x18), REG32("w0"));
	// [sp + 0x14 {var_c}].d = w1
	STORE32(ADD64(REG64("sp"), 0x14), REG32("w1"));
	// [sp + 0x10 {var_10}].d = w2
	STORE32(ADD64(REG64("sp"), 0x10), REG32("w2"));
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// w8 = [sp + 0x18 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x18)));
	// [sp + 8 {var_18}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// w8 = [sp + 0x18 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x18)));
	// if (w8 != 0) then 10 @ 0x7cc else 12 @ 0x7c4
	if(CMP_NE(REG32("w8"), 0))
		goto loc_10;
	else
		goto loc_12;

	loc_10:
	// w8 = [sp + 0x14 {var_c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x14)));
	// if (w8 == 0) then 14 @ 0x834 else 17 @ 0x7d4
	if(CMP_E(REG32("w8"), 0))
		goto loc_14;
	else
		goto loc_17;

	loc_12:
	// [sp + 0x1c {var_4}].d = 0
	STORE32(ADD64(REG64("sp"), 0x1C), 0);
	// goto 21 @ 0x83c
	goto loc_21;

	loc_14:
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// [sp + 0x1c {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 0x1C), REG32("w8"));
	// goto 21 @ 0x83c
	goto loc_21;

	loc_17:
	// w8 = [sp + 0x14 {var_c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x14)));
	// w9 = 1
	SET_REG32("w9", 1);
	// w8 = w8 & w9
	SET_REG32("w8", AND(REG32("w8"), REG32("w9")));
	// if (w8 == 0) then 24 @ 0x804 else 36 @ 0x7e4
	if(CMP_E(REG32("w8"), 0))
		goto loc_24;
	else
		goto loc_36;

	loc_21:
	// w0 = [sp + 0x1c {var_4}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 0x1C)));
	// sp = sp + 0x20
	SET_REG64("sp", ADD64(REG64("sp"), 0x20));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_24:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 8 {var_18}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w8 = w8 * w9
	SET_REG32("w8", MUL(REG32("w8"), REG32("w9")));
	// w9 = [sp + 0x10 {var_10}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w10 = divs.d(w8, w9)
	SET_REG32("w10", DIVS(REG32("w8"), REG32("w9")));
	// w9 = w10 * w9
	SET_REG32("w9", MUL(REG32("w10"), REG32("w9")));
	// w8 = w8 - w9
	SET_REG32("w8", SUB32(REG32("w8"), REG32("w9")));
	// [sp + 8 {var_18}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// w8 = [sp + 0x14 {var_c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 0x14)));
	// w8 = w8 s>> 1
	SET_REG32("w8", ASR(REG32("w8"), 1));
	// [sp + 0x14 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 0x14), REG32("w8"));
	// goto 10 @ 0x7cc
	goto loc_10;

	loc_36:
	// w8 = [sp + 0xc {var_14}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_18}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w8 = w8 * w9
	SET_REG32("w8", MUL(REG32("w8"), REG32("w9")));
	// w9 = [sp + 0x10 {var_10}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 0x10)));
	// w10 = divs.d(w8, w9)
	SET_REG32("w10", DIVS(REG32("w8"), REG32("w9")));
	// w9 = w10 * w9
	SET_REG32("w9", MUL(REG32("w10"), REG32("w9")));
	// w8 = w8 - w9
	SET_REG32("w8", SUB32(REG32("w8"), REG32("w9")));
	// [sp + 0xc {var_14}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 24 @ 0x804
	goto loc_24;
}

/* uint64_t gcd(int32_t arg1, int32_t arg2) */
void gcd(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// [sp + 8 {var_8}].d = w1
	STORE32(ADD64(REG64("sp"), 8), REG32("w1"));
	// goto 4 @ 0x854
	goto loc_4;

	loc_4:
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// if (w8 != 0) then 6 @ 0x868 else 8 @ 0x85c
	if(CMP_NE(REG32("w8"), 0))
		goto loc_6;
	else
		goto loc_8;

	loc_6:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// if (w8 != 0) then 11 @ 0x87c else 14 @ 0x870
	if(CMP_NE(REG32("w8"), 0))
		goto loc_11;
	else
		goto loc_14;

	loc_8:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// [sp + 4 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 4), REG32("w8"));
	// goto 17 @ 0x8c8
	goto loc_17;

	loc_11:
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// if (w8 s<= w9) then 20 else 22
	if(CMP_SLE32(REG32("w8"), REG32("w9")))
		goto loc_20;
	else
		goto loc_22;

	loc_14:
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// [sp + 4 {var_c}].d = w8
	STORE32(ADD64(REG64("sp"), 4), REG32("w8"));
	// goto 17 @ 0x8c8
	goto loc_17;

	loc_17:
	// w0 = [sp + 4 {var_c}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 4)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_20:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 24 @ 0x88c
	goto loc_24;

	loc_22:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 24 @ 0x88c
	goto loc_24;

	loc_24:
	// if ((w8 & 1) != 0) then 25 @ 0x8ac else 32 @ 0x890
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_25;
	else
		goto loc_32;

	loc_25:
	// w8 = [sp + 8 {var_8}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 0xc {var_4}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 12)));
	// w10 = divs.d(w8, w9)
	SET_REG32("w10", DIVS(REG32("w8"), REG32("w9")));
	// w9 = w10 * w9
	SET_REG32("w9", MUL(REG32("w10"), REG32("w9")));
	// w8 = w8 - w9
	SET_REG32("w8", SUB32(REG32("w8"), REG32("w9")));
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// goto 39 @ 0x8c4
	goto loc_39;

	loc_32:
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w9 = [sp + 8 {var_8}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w10 = divs.d(w8, w9)
	SET_REG32("w10", DIVS(REG32("w8"), REG32("w9")));
	// w9 = w10 * w9
	SET_REG32("w9", MUL(REG32("w10"), REG32("w9")));
	// w8 = w8 - w9
	SET_REG32("w8", SUB32(REG32("w8"), REG32("w9")));
	// [sp + 0xc {var_4}].d = w8
	STORE32(ADD64(REG64("sp"), 12), REG32("w8"));
	// goto 39 @ 0x8c4
	goto loc_39;

	loc_39:
	// goto 4 @ 0x854
	goto loc_4;
}

/* uint64_t gcd_recursive(int32_t arg1, int32_t arg2) */
void gcd_recursive(void)
{
	loc_0:
	// sp = sp - 0x20
	SET_REG64("sp", SUB64(REG64("sp"), 0x20));
	// [sp + 0x10 {__saved_x29}].q = x29
	STORE64(ADD64(REG64("sp"), 0x10), REG64("x29"));
	// [sp + 0x18 {__saved_x30}].q = x30
	STORE64(ADD64(REG64("sp"), 0x18), REG64("x30"));
	// x29 = sp + 0x10 {__saved_x29}
	SET_REG64("x29", ADD64(REG64("sp"), 0x10));
	// [sp + 8 {var_18}].d = w0
	STORE32(ADD64(REG64("sp"), 8), REG32("w0"));
	// [sp + 4 {var_1c}].d = w1
	STORE32(ADD64(REG64("sp"), 4), REG32("w1"));
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// if (w8 != 0) then 8 @ 0x8fc else 10 @ 0x8f0
	if(CMP_NE(REG32("w8"), 0))
		goto loc_8;
	else
		goto loc_10;

	loc_8:
	// w8 = [sp + 4 {var_1c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 4)));
	// if (w8 != 0) then 13 @ 0x910 else 16 @ 0x904
	if(CMP_NE(REG32("w8"), 0))
		goto loc_13;
	else
		goto loc_16;

	loc_10:
	// w8 = [sp + 4 {var_1c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 4)));
	// [x29 - 4 {var_14}].d = w8
	STORE32(ADD64(REG64("x29"), -4), REG32("w8"));
	// goto 19 @ 0x978
	goto loc_19;

	loc_13:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 4 {var_1c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 4)));
	// if (w8 != w9) then 24 else 26
	if(CMP_NE(REG32("w8"), REG32("w9")))
		goto loc_24;
	else
		goto loc_26;

	loc_16:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// [x29 - 4 {var_14}].d = w8
	STORE32(ADD64(REG64("x29"), -4), REG32("w8"));
	// goto 19 @ 0x978
	goto loc_19;

	loc_19:
	// w0 = [x29 - 4 {var_14}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("x29"), -4)));
	// x29 = [sp + 0x10 {__saved_x29}].q
	SET_REG64("x29", LOAD64(ADD64(REG64("sp"), 0x10)));
	// x30 = [sp + 0x18 {__saved_x30}].q
	SET_REG64("x30", LOAD64(ADD64(REG64("sp"), 0x18)));
	// sp = sp + 0x20
	SET_REG64("sp", ADD64(REG64("sp"), 0x20));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_24:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 28 @ 0x920
	goto loc_28;

	loc_26:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 28 @ 0x920
	goto loc_28;

	loc_28:
	// if ((w8 & 1) != 0) then 29 @ 0x930 else 32 @ 0x924
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_29;
	else
		goto loc_32;

	loc_29:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 4 {var_1c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 4)));
	// if (w8 s<= w9) then 35 else 37
	if(CMP_SLE32(REG32("w8"), REG32("w9")))
		goto loc_35;
	else
		goto loc_37;

	loc_32:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// [x29 - 4 {var_14}].d = w8
	STORE32(ADD64(REG64("x29"), -4), REG32("w8"));
	// goto 19 @ 0x978
	goto loc_19;

	loc_35:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 39 @ 0x940
	goto loc_39;

	loc_37:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 39 @ 0x940
	goto loc_39;

	loc_39:
	// if ((w8 & 1) != 0) then 40 @ 0x960 else 47 @ 0x944
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_40;
	else
		goto loc_47;

	loc_40:
	// w0 = [sp + 8 {var_18}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 8)));
	// w8 = [sp + 4 {var_1c}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 4)));
	// w9 = [sp + 8 {var_18}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w1 = w8 - w9
	SET_REG32("w1", SUB32(REG32("w8"), REG32("w9")));
	// call(0x8d4)
	CALL(0x8D4, gcd_recursive, "gcd_recursive");
	// [x29 - 4 {var_14}].d = w0
	STORE32(ADD64(REG64("x29"), -4), REG32("w0"));
	// goto 19 @ 0x978
	goto loc_19;

	loc_47:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 4 {var_1c}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 4)));
	// w0 = w8 - w9
	SET_REG32("w0", SUB32(REG32("w8"), REG32("w9")));
	// w1 = [sp + 4 {var_1c}].d
	SET_REG32("w1", LOAD32(ADD64(REG64("sp"), 4)));
	// call(0x8d4)
	CALL(0x8D4, gcd_recursive, "gcd_recursive");
	// [x29 - 4 {var_14}].d = w0
	STORE32(ADD64(REG64("x29"), -4), REG32("w0"));
	// goto 19 @ 0x978
	goto loc_19;
}

/* int64_t switch_doubler(int32_t arg1) */
void switch_doubler(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = w0
	STORE32(ADD64(REG64("sp"), 12), REG32("w0"));
	// w8 = [sp + 0xc {var_4}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 12)));
	// w8 = w8
	SET_REG32("w8", REG32("w8"));
	// w9 = w8
	SET_REG32("w9", REG32("w8"));
	// x9 = x9.d
	SET_REG64("x9", LOW_PART32(REG64("x9")));
	// if (x9 u> 0xa) then 7 else 9
	if(CMP_UGT(REG64("x9"), 10))
		goto loc_7;
	else
		goto loc_9;

	loc_7:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 11 @ 0x9a8
	goto loc_11;

	loc_9:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 11 @ 0x9a8
	goto loc_11;

	loc_11:
	// [sp {var_10}].q = x9
	STORE64(REG64("sp"), REG64("x9"));
	// if ((w8 & 1) != 0) then 13 @ 0xa48 else 18 @ 0x9b0
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_13;
	else
		goto loc_18;

	loc_13:
	// w8 = -1
	SET_REG32("w8", -1);
	// [sp + 8 {var_8}].d = w8
	STORE32(ADD64(REG64("sp"), 8), REG32("w8"));
	// w0 = [sp + 8 {var_8}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("sp"), 8)));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;

	loc_18:
	// x8 = 0
	SET_REG64("x8", 0x0);
	// x8 = x8 + 0xb40
	SET_REG64("x8", ADD64(REG64("x8"), 0xB40));
	// x11 = [sp {var_10}].q
	SET_REG64("x11", LOAD64(REG64("sp")));
	// x10 = sx.q([x8 + (x11 << 2)].d)
	SET_REG64("x10", SX32(LOAD32(ADD64(REG64("x8"), LSL(REG64("x11"), 2)))));
	// x9 = x8 + x10
	SET_REG64("x9", ADD64(REG64("x8"), REG64("x10")));
	// jump(x9)
	if(JUMP(REG64("x9")) == RETURN_TRUE) return;
}

/* uint64_t factorial(int32_t arg1) */
void factorial(void)
{
	loc_0:
	// sp = sp - 0x20
	SET_REG64("sp", SUB64(REG64("sp"), 0x20));
	// [sp + 0x10 {__saved_x29}].q = x29
	STORE64(ADD64(REG64("sp"), 0x10), REG64("x29"));
	// [sp + 0x18 {__saved_x30}].q = x30
	STORE64(ADD64(REG64("sp"), 0x18), REG64("x30"));
	// x29 = sp + 0x10 {__saved_x29}
	SET_REG64("x29", ADD64(REG64("sp"), 0x10));
	// [sp + 8 {var_18}].d = w0
	STORE32(ADD64(REG64("sp"), 8), REG32("w0"));
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// if (w8 s> 1) then 7 else 9
	if(CMP_SGT32(REG32("w8"), 1))
		goto loc_7;
	else
		goto loc_9;

	loc_7:
	// w8 = 1
	SET_REG32("w8", 1);
	// goto 11 @ 0xa78
	goto loc_11;

	loc_9:
	// w8 = 0
	SET_REG32("w8", 0);
	// goto 11 @ 0xa78
	goto loc_11;

	loc_11:
	// if ((w8 & 1) != 0) then 12 @ 0xa88 else 21 @ 0xa7c
	if(CMP_NE(AND(REG32("w8"), 1), 0))
		goto loc_12;
	else
		goto loc_21;

	loc_12:
	// w8 = [sp + 8 {var_18}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 8)));
	// w9 = [sp + 8 {var_18}].d
	SET_REG32("w9", LOAD32(ADD64(REG64("sp"), 8)));
	// w0 = w9 - 1
	SET_REG32("w0", SUB32(REG32("w9"), 1));
	// [sp + 4 {var_1c_1}].d = w8
	STORE32(ADD64(REG64("sp"), 4), REG32("w8"));
	// call(0xa5c)
	CALL(0xA5C, factorial, "factorial");
	// w8 = [sp + 4 {var_1c_1}].d
	SET_REG32("w8", LOAD32(ADD64(REG64("sp"), 4)));
	// w9 = w8 * w0
	SET_REG32("w9", MUL(REG32("w8"), REG32("w0")));
	// [x29 - 4 {var_14}].d = w9
	STORE32(ADD64(REG64("x29"), -4), REG32("w9"));
	// goto 24 @ 0xaa8
	goto loc_24;

	loc_21:
	// w8 = 1
	SET_REG32("w8", 1);
	// [x29 - 4 {var_14}].d = w8
	STORE32(ADD64(REG64("x29"), -4), REG32("w8"));
	// goto 24 @ 0xaa8
	goto loc_24;

	loc_24:
	// w0 = [x29 - 4 {var_14}].d
	SET_REG32("w0", LOAD32(ADD64(REG64("x29"), -4)));
	// x29 = [sp + 0x10 {__saved_x29}].q
	SET_REG64("x29", LOAD64(ADD64(REG64("sp"), 0x10)));
	// x30 = [sp + 0x18 {__saved_x30}].q
	SET_REG64("x30", LOAD64(ADD64(REG64("sp"), 0x18)));
	// sp = sp + 0x20
	SET_REG64("sp", ADD64(REG64("sp"), 0x20));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* int64_t fp_single_add() */
void fp_single_add(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = s0
	STORE32(ADD64(REG64("sp"), 12), REG32("s0"));
	// [sp + 8 {var_8}].d = s1
	STORE32(ADD64(REG64("sp"), 8), REG32("s1"));
	// s0 = [sp + 0xc {var_4}].d
	SET_REG32("s0", LOAD32(ADD64(REG64("sp"), 12)));
	// s1 = [sp + 8 {var_8}].d
	SET_REG32("s1", LOAD32(ADD64(REG64("sp"), 8)));
	// s0 = s0 f+ s1
	SET_REG32("s0", FADD(REG32("s0"), REG32("s1")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* int64_t fp_single_sub() */
void fp_single_sub(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = s0
	STORE32(ADD64(REG64("sp"), 12), REG32("s0"));
	// [sp + 8 {var_8}].d = s1
	STORE32(ADD64(REG64("sp"), 8), REG32("s1"));
	// s0 = [sp + 0xc {var_4}].d
	SET_REG32("s0", LOAD32(ADD64(REG64("sp"), 12)));
	// s1 = [sp + 8 {var_8}].d
	SET_REG32("s1", LOAD32(ADD64(REG64("sp"), 8)));
	// s0 = s0 f- s1
	SET_REG32("s0", FSUB(REG32("s0"), REG32("s1")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* int64_t fp_single_mul() */
void fp_single_mul(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = s0
	STORE32(ADD64(REG64("sp"), 12), REG32("s0"));
	// [sp + 8 {var_8}].d = s1
	STORE32(ADD64(REG64("sp"), 8), REG32("s1"));
	// s0 = [sp + 0xc {var_4}].d
	SET_REG32("s0", LOAD32(ADD64(REG64("sp"), 12)));
	// s1 = [sp + 8 {var_8}].d
	SET_REG32("s1", LOAD32(ADD64(REG64("sp"), 8)));
	// s0 = s0 f* s1
	SET_REG32("s0", FMUL(REG32("s0"), REG32("s1")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

/* int64_t fp_single_div() */
void fp_single_div(void)
{
	loc_0:
	// sp = sp - 0x10
	SET_REG64("sp", SUB64(REG64("sp"), 0x10));
	// [sp + 0xc {var_4}].d = s0
	STORE32(ADD64(REG64("sp"), 12), REG32("s0"));
	// [sp + 8 {var_8}].d = s1
	STORE32(ADD64(REG64("sp"), 8), REG32("s1"));
	// s0 = [sp + 0xc {var_4}].d
	SET_REG32("s0", LOAD32(ADD64(REG64("sp"), 12)));
	// s1 = [sp + 8 {var_8}].d
	SET_REG32("s1", LOAD32(ADD64(REG64("sp"), 8)));
	// s0 = s0 f/ s1
	SET_REG32("s0", FDIV(REG32("s0"), REG32("s1")));
	// sp = sp + 0x10
	SET_REG64("sp", ADD64(REG64("sp"), 0x10));
	// <return> jump(x30)
	RET(REG64("x30"));
	return;
}

void initialize_memory()
{
	memset(vm_mem, 0, VM_MEM_SZ);
	
}

map<string,struct RegisterInfo> reg_infos = {
	{"w0", {1, "x0", 0, 4, 1}}, /* <reg: size 4, offset 0 in x0, zero extend> */
	{"w1", {2, "x1", 0, 4, 1}}, /* <reg: size 4, offset 0 in x1, zero extend> */
	{"w2", {3, "x2", 0, 4, 1}}, /* <reg: size 4, offset 0 in x2, zero extend> */
	{"w3", {4, "x3", 0, 4, 1}}, /* <reg: size 4, offset 0 in x3, zero extend> */
	{"w4", {5, "x4", 0, 4, 1}}, /* <reg: size 4, offset 0 in x4, zero extend> */
	{"w5", {6, "x5", 0, 4, 1}}, /* <reg: size 4, offset 0 in x5, zero extend> */
	{"w6", {7, "x6", 0, 4, 1}}, /* <reg: size 4, offset 0 in x6, zero extend> */
	{"w7", {8, "x7", 0, 4, 1}}, /* <reg: size 4, offset 0 in x7, zero extend> */
	{"w8", {9, "x8", 0, 4, 1}}, /* <reg: size 4, offset 0 in x8, zero extend> */
	{"w9", {10, "x9", 0, 4, 1}}, /* <reg: size 4, offset 0 in x9, zero extend> */
	{"w10", {11, "x10", 0, 4, 1}}, /* <reg: size 4, offset 0 in x10, zero extend> */
	{"w11", {12, "x11", 0, 4, 1}}, /* <reg: size 4, offset 0 in x11, zero extend> */
	{"w12", {13, "x12", 0, 4, 1}}, /* <reg: size 4, offset 0 in x12, zero extend> */
	{"w13", {14, "x13", 0, 4, 1}}, /* <reg: size 4, offset 0 in x13, zero extend> */
	{"w14", {15, "x14", 0, 4, 1}}, /* <reg: size 4, offset 0 in x14, zero extend> */
	{"w15", {16, "x15", 0, 4, 1}}, /* <reg: size 4, offset 0 in x15, zero extend> */
	{"w16", {17, "x16", 0, 4, 1}}, /* <reg: size 4, offset 0 in x16, zero extend> */
	{"w17", {18, "x17", 0, 4, 1}}, /* <reg: size 4, offset 0 in x17, zero extend> */
	{"w18", {19, "x18", 0, 4, 1}}, /* <reg: size 4, offset 0 in x18, zero extend> */
	{"w19", {20, "x19", 0, 4, 1}}, /* <reg: size 4, offset 0 in x19, zero extend> */
	{"w20", {21, "x20", 0, 4, 1}}, /* <reg: size 4, offset 0 in x20, zero extend> */
	{"w21", {22, "x21", 0, 4, 1}}, /* <reg: size 4, offset 0 in x21, zero extend> */
	{"w22", {23, "x22", 0, 4, 1}}, /* <reg: size 4, offset 0 in x22, zero extend> */
	{"w23", {24, "x23", 0, 4, 1}}, /* <reg: size 4, offset 0 in x23, zero extend> */
	{"w24", {25, "x24", 0, 4, 1}}, /* <reg: size 4, offset 0 in x24, zero extend> */
	{"w25", {26, "x25", 0, 4, 1}}, /* <reg: size 4, offset 0 in x25, zero extend> */
	{"w26", {27, "x26", 0, 4, 1}}, /* <reg: size 4, offset 0 in x26, zero extend> */
	{"w27", {28, "x27", 0, 4, 1}}, /* <reg: size 4, offset 0 in x27, zero extend> */
	{"w28", {29, "x28", 0, 4, 1}}, /* <reg: size 4, offset 0 in x28, zero extend> */
	{"w29", {30, "x29", 0, 4, 1}}, /* <reg: size 4, offset 0 in x29, zero extend> */
	{"w30", {31, "x30", 0, 4, 1}}, /* <reg: size 4, offset 0 in x30, zero extend> */
	{"wsp", {33, "sp", 0, 4, 1}}, /* <reg: size 4, offset 0 in sp, zero extend> */
	{"wzr", {32, "xzr", 0, 4, 1}}, /* <reg: size 4, offset 0 in xzr, zero extend> */
	{"x0", {34, "x0", 0, 8, 0}}, /* <reg: size 8, offset 0 in x0> */
	{"x1", {35, "x1", 0, 8, 0}}, /* <reg: size 8, offset 0 in x1> */
	{"x2", {36, "x2", 0, 8, 0}}, /* <reg: size 8, offset 0 in x2> */
	{"x3", {37, "x3", 0, 8, 0}}, /* <reg: size 8, offset 0 in x3> */
	{"x4", {38, "x4", 0, 8, 0}}, /* <reg: size 8, offset 0 in x4> */
	{"x5", {39, "x5", 0, 8, 0}}, /* <reg: size 8, offset 0 in x5> */
	{"x6", {40, "x6", 0, 8, 0}}, /* <reg: size 8, offset 0 in x6> */
	{"x7", {41, "x7", 0, 8, 0}}, /* <reg: size 8, offset 0 in x7> */
	{"x8", {42, "x8", 0, 8, 0}}, /* <reg: size 8, offset 0 in x8> */
	{"x9", {43, "x9", 0, 8, 0}}, /* <reg: size 8, offset 0 in x9> */
	{"x10", {44, "x10", 0, 8, 0}}, /* <reg: size 8, offset 0 in x10> */
	{"x11", {45, "x11", 0, 8, 0}}, /* <reg: size 8, offset 0 in x11> */
	{"x12", {46, "x12", 0, 8, 0}}, /* <reg: size 8, offset 0 in x12> */
	{"x13", {47, "x13", 0, 8, 0}}, /* <reg: size 8, offset 0 in x13> */
	{"x14", {48, "x14", 0, 8, 0}}, /* <reg: size 8, offset 0 in x14> */
	{"x15", {49, "x15", 0, 8, 0}}, /* <reg: size 8, offset 0 in x15> */
	{"x16", {50, "x16", 0, 8, 0}}, /* <reg: size 8, offset 0 in x16> */
	{"x17", {51, "x17", 0, 8, 0}}, /* <reg: size 8, offset 0 in x17> */
	{"x18", {52, "x18", 0, 8, 0}}, /* <reg: size 8, offset 0 in x18> */
	{"x19", {53, "x19", 0, 8, 0}}, /* <reg: size 8, offset 0 in x19> */
	{"x20", {54, "x20", 0, 8, 0}}, /* <reg: size 8, offset 0 in x20> */
	{"x21", {55, "x21", 0, 8, 0}}, /* <reg: size 8, offset 0 in x21> */
	{"x22", {56, "x22", 0, 8, 0}}, /* <reg: size 8, offset 0 in x22> */
	{"x23", {57, "x23", 0, 8, 0}}, /* <reg: size 8, offset 0 in x23> */
	{"x24", {58, "x24", 0, 8, 0}}, /* <reg: size 8, offset 0 in x24> */
	{"x25", {59, "x25", 0, 8, 0}}, /* <reg: size 8, offset 0 in x25> */
	{"x26", {60, "x26", 0, 8, 0}}, /* <reg: size 8, offset 0 in x26> */
	{"x27", {61, "x27", 0, 8, 0}}, /* <reg: size 8, offset 0 in x27> */
	{"x28", {62, "x28", 0, 8, 0}}, /* <reg: size 8, offset 0 in x28> */
	{"x29", {63, "x29", 0, 8, 0}}, /* <reg: size 8, offset 0 in x29> */
	{"x30", {64, "x30", 0, 8, 0}}, /* <reg: size 8, offset 0 in x30> */
	{"sp", {66, "sp", 0, 8, 0}}, /* <reg: size 8, offset 0 in sp> */
	{"xzr", {65, "xzr", 0, 8, 0}}, /* <reg: size 8, offset 0 in xzr> */
	{"v0", {67, "v0", 0, 16, 0}}, /* <reg: size 16, offset 0 in v0> */
	{"v1", {68, "v1", 0, 16, 0}}, /* <reg: size 16, offset 0 in v1> */
	{"v2", {69, "v2", 0, 16, 0}}, /* <reg: size 16, offset 0 in v2> */
	{"v3", {70, "v3", 0, 16, 0}}, /* <reg: size 16, offset 0 in v3> */
	{"v4", {71, "v4", 0, 16, 0}}, /* <reg: size 16, offset 0 in v4> */
	{"v5", {72, "v5", 0, 16, 0}}, /* <reg: size 16, offset 0 in v5> */
	{"v6", {73, "v6", 0, 16, 0}}, /* <reg: size 16, offset 0 in v6> */
	{"v7", {74, "v7", 0, 16, 0}}, /* <reg: size 16, offset 0 in v7> */
	{"v8", {75, "v8", 0, 16, 0}}, /* <reg: size 16, offset 0 in v8> */
	{"v9", {76, "v9", 0, 16, 0}}, /* <reg: size 16, offset 0 in v9> */
	{"v10", {77, "v10", 0, 16, 0}}, /* <reg: size 16, offset 0 in v10> */
	{"v11", {78, "v11", 0, 16, 0}}, /* <reg: size 16, offset 0 in v11> */
	{"v12", {79, "v12", 0, 16, 0}}, /* <reg: size 16, offset 0 in v12> */
	{"v13", {80, "v13", 0, 16, 0}}, /* <reg: size 16, offset 0 in v13> */
	{"v14", {81, "v14", 0, 16, 0}}, /* <reg: size 16, offset 0 in v14> */
	{"v15", {82, "v15", 0, 16, 0}}, /* <reg: size 16, offset 0 in v15> */
	{"v16", {83, "v16", 0, 16, 0}}, /* <reg: size 16, offset 0 in v16> */
	{"v17", {84, "v17", 0, 16, 0}}, /* <reg: size 16, offset 0 in v17> */
	{"v18", {85, "v18", 0, 16, 0}}, /* <reg: size 16, offset 0 in v18> */
	{"v19", {86, "v19", 0, 16, 0}}, /* <reg: size 16, offset 0 in v19> */
	{"v20", {87, "v20", 0, 16, 0}}, /* <reg: size 16, offset 0 in v20> */
	{"v21", {88, "v21", 0, 16, 0}}, /* <reg: size 16, offset 0 in v21> */
	{"v22", {89, "v22", 0, 16, 0}}, /* <reg: size 16, offset 0 in v22> */
	{"v23", {90, "v23", 0, 16, 0}}, /* <reg: size 16, offset 0 in v23> */
	{"v24", {91, "v24", 0, 16, 0}}, /* <reg: size 16, offset 0 in v24> */
	{"v25", {92, "v25", 0, 16, 0}}, /* <reg: size 16, offset 0 in v25> */
	{"v26", {93, "v26", 0, 16, 0}}, /* <reg: size 16, offset 0 in v26> */
	{"v27", {94, "v27", 0, 16, 0}}, /* <reg: size 16, offset 0 in v27> */
	{"v28", {95, "v28", 0, 16, 0}}, /* <reg: size 16, offset 0 in v28> */
	{"v29", {96, "v29", 0, 16, 0}}, /* <reg: size 16, offset 0 in v29> */
	{"v30", {97, "v30", 0, 16, 0}}, /* <reg: size 16, offset 0 in v30> */
	{"v31", {99, "v31", 0, 16, 0}}, /* <reg: size 16, offset 0 in v31> */
	{"b0", {100, "v0", 0, 1, 0}}, /* <reg: size 1, offset 0 in v0> */
	{"b1", {101, "v1", 0, 1, 0}}, /* <reg: size 1, offset 0 in v1> */
	{"b2", {102, "v2", 0, 1, 0}}, /* <reg: size 1, offset 0 in v2> */
	{"b3", {103, "v3", 0, 1, 0}}, /* <reg: size 1, offset 0 in v3> */
	{"b4", {104, "v4", 0, 1, 0}}, /* <reg: size 1, offset 0 in v4> */
	{"b5", {105, "v5", 0, 1, 0}}, /* <reg: size 1, offset 0 in v5> */
	{"b6", {106, "v6", 0, 1, 0}}, /* <reg: size 1, offset 0 in v6> */
	{"b7", {107, "v7", 0, 1, 0}}, /* <reg: size 1, offset 0 in v7> */
	{"b8", {108, "v8", 0, 1, 0}}, /* <reg: size 1, offset 0 in v8> */
	{"b9", {109, "v9", 0, 1, 0}}, /* <reg: size 1, offset 0 in v9> */
	{"b10", {110, "v10", 0, 1, 0}}, /* <reg: size 1, offset 0 in v10> */
	{"b11", {111, "v11", 0, 1, 0}}, /* <reg: size 1, offset 0 in v11> */
	{"b12", {112, "v12", 0, 1, 0}}, /* <reg: size 1, offset 0 in v12> */
	{"b13", {113, "v13", 0, 1, 0}}, /* <reg: size 1, offset 0 in v13> */
	{"b14", {114, "v14", 0, 1, 0}}, /* <reg: size 1, offset 0 in v14> */
	{"b15", {115, "v15", 0, 1, 0}}, /* <reg: size 1, offset 0 in v15> */
	{"b16", {116, "v16", 0, 1, 0}}, /* <reg: size 1, offset 0 in v16> */
	{"b17", {117, "v17", 0, 1, 0}}, /* <reg: size 1, offset 0 in v17> */
	{"b18", {118, "v18", 0, 1, 0}}, /* <reg: size 1, offset 0 in v18> */
	{"b19", {119, "v19", 0, 1, 0}}, /* <reg: size 1, offset 0 in v19> */
	{"b20", {120, "v20", 0, 1, 0}}, /* <reg: size 1, offset 0 in v20> */
	{"b21", {121, "v21", 0, 1, 0}}, /* <reg: size 1, offset 0 in v21> */
	{"b22", {122, "v22", 0, 1, 0}}, /* <reg: size 1, offset 0 in v22> */
	{"b23", {123, "v23", 0, 1, 0}}, /* <reg: size 1, offset 0 in v23> */
	{"b24", {124, "v24", 0, 1, 0}}, /* <reg: size 1, offset 0 in v24> */
	{"b25", {125, "v25", 0, 1, 0}}, /* <reg: size 1, offset 0 in v25> */
	{"b26", {126, "v26", 0, 1, 0}}, /* <reg: size 1, offset 0 in v26> */
	{"b27", {127, "v27", 0, 1, 0}}, /* <reg: size 1, offset 0 in v27> */
	{"b28", {128, "v28", 0, 1, 0}}, /* <reg: size 1, offset 0 in v28> */
	{"b29", {129, "v29", 0, 1, 0}}, /* <reg: size 1, offset 0 in v29> */
	{"b30", {130, "v30", 0, 1, 0}}, /* <reg: size 1, offset 0 in v30> */
	{"b31", {132, "v31", 0, 1, 0}}, /* <reg: size 1, offset 0 in v31> */
	{"h0", {133, "v0", 0, 2, 0}}, /* <reg: size 2, offset 0 in v0> */
	{"h1", {134, "v1", 0, 2, 0}}, /* <reg: size 2, offset 0 in v1> */
	{"h2", {135, "v2", 0, 2, 0}}, /* <reg: size 2, offset 0 in v2> */
	{"h3", {136, "v3", 0, 2, 0}}, /* <reg: size 2, offset 0 in v3> */
	{"h4", {137, "v4", 0, 2, 0}}, /* <reg: size 2, offset 0 in v4> */
	{"h5", {138, "v5", 0, 2, 0}}, /* <reg: size 2, offset 0 in v5> */
	{"h6", {139, "v6", 0, 2, 0}}, /* <reg: size 2, offset 0 in v6> */
	{"h7", {140, "v7", 0, 2, 0}}, /* <reg: size 2, offset 0 in v7> */
	{"h8", {141, "v8", 0, 2, 0}}, /* <reg: size 2, offset 0 in v8> */
	{"h9", {142, "v9", 0, 2, 0}}, /* <reg: size 2, offset 0 in v9> */
	{"h10", {143, "v10", 0, 2, 0}}, /* <reg: size 2, offset 0 in v10> */
	{"h11", {144, "v11", 0, 2, 0}}, /* <reg: size 2, offset 0 in v11> */
	{"h12", {145, "v12", 0, 2, 0}}, /* <reg: size 2, offset 0 in v12> */
	{"h13", {146, "v13", 0, 2, 0}}, /* <reg: size 2, offset 0 in v13> */
	{"h14", {147, "v14", 0, 2, 0}}, /* <reg: size 2, offset 0 in v14> */
	{"h15", {148, "v15", 0, 2, 0}}, /* <reg: size 2, offset 0 in v15> */
	{"h16", {149, "v16", 0, 2, 0}}, /* <reg: size 2, offset 0 in v16> */
	{"h17", {150, "v17", 0, 2, 0}}, /* <reg: size 2, offset 0 in v17> */
	{"h18", {151, "v18", 0, 2, 0}}, /* <reg: size 2, offset 0 in v18> */
	{"h19", {152, "v19", 0, 2, 0}}, /* <reg: size 2, offset 0 in v19> */
	{"h20", {153, "v20", 0, 2, 0}}, /* <reg: size 2, offset 0 in v20> */
	{"h21", {154, "v21", 0, 2, 0}}, /* <reg: size 2, offset 0 in v21> */
	{"h22", {155, "v22", 0, 2, 0}}, /* <reg: size 2, offset 0 in v22> */
	{"h23", {156, "v23", 0, 2, 0}}, /* <reg: size 2, offset 0 in v23> */
	{"h24", {157, "v24", 0, 2, 0}}, /* <reg: size 2, offset 0 in v24> */
	{"h25", {158, "v25", 0, 2, 0}}, /* <reg: size 2, offset 0 in v25> */
	{"h26", {159, "v26", 0, 2, 0}}, /* <reg: size 2, offset 0 in v26> */
	{"h27", {160, "v27", 0, 2, 0}}, /* <reg: size 2, offset 0 in v27> */
	{"h28", {161, "v28", 0, 2, 0}}, /* <reg: size 2, offset 0 in v28> */
	{"h29", {162, "v29", 0, 2, 0}}, /* <reg: size 2, offset 0 in v29> */
	{"h30", {163, "v30", 0, 2, 0}}, /* <reg: size 2, offset 0 in v30> */
	{"h31", {165, "v31", 0, 2, 0}}, /* <reg: size 2, offset 0 in v31> */
	{"s0", {166, "v0", 0, 4, 0}}, /* <reg: size 4, offset 0 in v0> */
	{"s1", {167, "v1", 0, 4, 0}}, /* <reg: size 4, offset 0 in v1> */
	{"s2", {168, "v2", 0, 4, 0}}, /* <reg: size 4, offset 0 in v2> */
	{"s3", {169, "v3", 0, 4, 0}}, /* <reg: size 4, offset 0 in v3> */
	{"s4", {170, "v4", 0, 4, 0}}, /* <reg: size 4, offset 0 in v4> */
	{"s5", {171, "v5", 0, 4, 0}}, /* <reg: size 4, offset 0 in v5> */
	{"s6", {172, "v6", 0, 4, 0}}, /* <reg: size 4, offset 0 in v6> */
	{"s7", {173, "v7", 0, 4, 0}}, /* <reg: size 4, offset 0 in v7> */
	{"s8", {174, "v8", 0, 4, 0}}, /* <reg: size 4, offset 0 in v8> */
	{"s9", {175, "v9", 0, 4, 0}}, /* <reg: size 4, offset 0 in v9> */
	{"s10", {176, "v10", 0, 4, 0}}, /* <reg: size 4, offset 0 in v10> */
	{"s11", {177, "v11", 0, 4, 0}}, /* <reg: size 4, offset 0 in v11> */
	{"s12", {178, "v12", 0, 4, 0}}, /* <reg: size 4, offset 0 in v12> */
	{"s13", {179, "v13", 0, 4, 0}}, /* <reg: size 4, offset 0 in v13> */
	{"s14", {180, "v14", 0, 4, 0}}, /* <reg: size 4, offset 0 in v14> */
	{"s15", {181, "v15", 0, 4, 0}}, /* <reg: size 4, offset 0 in v15> */
	{"s16", {182, "v16", 0, 4, 0}}, /* <reg: size 4, offset 0 in v16> */
	{"s17", {183, "v17", 0, 4, 0}}, /* <reg: size 4, offset 0 in v17> */
	{"s18", {184, "v18", 0, 4, 0}}, /* <reg: size 4, offset 0 in v18> */
	{"s19", {185, "v19", 0, 4, 0}}, /* <reg: size 4, offset 0 in v19> */
	{"s20", {186, "v20", 0, 4, 0}}, /* <reg: size 4, offset 0 in v20> */
	{"s21", {187, "v21", 0, 4, 0}}, /* <reg: size 4, offset 0 in v21> */
	{"s22", {188, "v22", 0, 4, 0}}, /* <reg: size 4, offset 0 in v22> */
	{"s23", {189, "v23", 0, 4, 0}}, /* <reg: size 4, offset 0 in v23> */
	{"s24", {190, "v24", 0, 4, 0}}, /* <reg: size 4, offset 0 in v24> */
	{"s25", {191, "v25", 0, 4, 0}}, /* <reg: size 4, offset 0 in v25> */
	{"s26", {192, "v26", 0, 4, 0}}, /* <reg: size 4, offset 0 in v26> */
	{"s27", {193, "v27", 0, 4, 0}}, /* <reg: size 4, offset 0 in v27> */
	{"s28", {194, "v28", 0, 4, 0}}, /* <reg: size 4, offset 0 in v28> */
	{"s29", {195, "v29", 0, 4, 0}}, /* <reg: size 4, offset 0 in v29> */
	{"s30", {196, "v30", 0, 4, 0}}, /* <reg: size 4, offset 0 in v30> */
	{"s31", {198, "v31", 0, 4, 0}}, /* <reg: size 4, offset 0 in v31> */
	{"d0", {199, "v0", 0, 8, 0}}, /* <reg: size 8, offset 0 in v0> */
	{"d1", {200, "v1", 0, 8, 0}}, /* <reg: size 8, offset 0 in v1> */
	{"d2", {201, "v2", 0, 8, 0}}, /* <reg: size 8, offset 0 in v2> */
	{"d3", {202, "v3", 0, 8, 0}}, /* <reg: size 8, offset 0 in v3> */
	{"d4", {203, "v4", 0, 8, 0}}, /* <reg: size 8, offset 0 in v4> */
	{"d5", {204, "v5", 0, 8, 0}}, /* <reg: size 8, offset 0 in v5> */
	{"d6", {205, "v6", 0, 8, 0}}, /* <reg: size 8, offset 0 in v6> */
	{"d7", {206, "v7", 0, 8, 0}}, /* <reg: size 8, offset 0 in v7> */
	{"d8", {207, "v8", 0, 8, 0}}, /* <reg: size 8, offset 0 in v8> */
	{"d9", {208, "v9", 0, 8, 0}}, /* <reg: size 8, offset 0 in v9> */
	{"d10", {209, "v10", 0, 8, 0}}, /* <reg: size 8, offset 0 in v10> */
	{"d11", {210, "v11", 0, 8, 0}}, /* <reg: size 8, offset 0 in v11> */
	{"d12", {211, "v12", 0, 8, 0}}, /* <reg: size 8, offset 0 in v12> */
	{"d13", {212, "v13", 0, 8, 0}}, /* <reg: size 8, offset 0 in v13> */
	{"d14", {213, "v14", 0, 8, 0}}, /* <reg: size 8, offset 0 in v14> */
	{"d15", {214, "v15", 0, 8, 0}}, /* <reg: size 8, offset 0 in v15> */
	{"d16", {215, "v16", 0, 8, 0}}, /* <reg: size 8, offset 0 in v16> */
	{"d17", {216, "v17", 0, 8, 0}}, /* <reg: size 8, offset 0 in v17> */
	{"d18", {217, "v18", 0, 8, 0}}, /* <reg: size 8, offset 0 in v18> */
	{"d19", {218, "v19", 0, 8, 0}}, /* <reg: size 8, offset 0 in v19> */
	{"d20", {219, "v20", 0, 8, 0}}, /* <reg: size 8, offset 0 in v20> */
	{"d21", {220, "v21", 0, 8, 0}}, /* <reg: size 8, offset 0 in v21> */
	{"d22", {221, "v22", 0, 8, 0}}, /* <reg: size 8, offset 0 in v22> */
	{"d23", {222, "v23", 0, 8, 0}}, /* <reg: size 8, offset 0 in v23> */
	{"d24", {223, "v24", 0, 8, 0}}, /* <reg: size 8, offset 0 in v24> */
	{"d25", {224, "v25", 0, 8, 0}}, /* <reg: size 8, offset 0 in v25> */
	{"d26", {225, "v26", 0, 8, 0}}, /* <reg: size 8, offset 0 in v26> */
	{"d27", {226, "v27", 0, 8, 0}}, /* <reg: size 8, offset 0 in v27> */
	{"d28", {227, "v28", 0, 8, 0}}, /* <reg: size 8, offset 0 in v28> */
	{"d29", {228, "v29", 0, 8, 0}}, /* <reg: size 8, offset 0 in v29> */
	{"d30", {229, "v30", 0, 8, 0}}, /* <reg: size 8, offset 0 in v30> */
	{"d31", {231, "v31", 0, 8, 0}}, /* <reg: size 8, offset 0 in v31> */
	{"q0", {232, "v0", 0, 16, 0}}, /* <reg: size 16, offset 0 in v0> */
	{"q1", {233, "v1", 0, 16, 0}}, /* <reg: size 16, offset 0 in v1> */
	{"q2", {234, "v2", 0, 16, 0}}, /* <reg: size 16, offset 0 in v2> */
	{"q3", {235, "v3", 0, 16, 0}}, /* <reg: size 16, offset 0 in v3> */
	{"q4", {236, "v4", 0, 16, 0}}, /* <reg: size 16, offset 0 in v4> */
	{"q5", {237, "v5", 0, 16, 0}}, /* <reg: size 16, offset 0 in v5> */
	{"q6", {238, "v6", 0, 16, 0}}, /* <reg: size 16, offset 0 in v6> */
	{"q7", {239, "v7", 0, 16, 0}}, /* <reg: size 16, offset 0 in v7> */
	{"q8", {240, "v8", 0, 16, 0}}, /* <reg: size 16, offset 0 in v8> */
	{"q9", {241, "v9", 0, 16, 0}}, /* <reg: size 16, offset 0 in v9> */
	{"q10", {242, "v10", 0, 16, 0}}, /* <reg: size 16, offset 0 in v10> */
	{"q11", {243, "v11", 0, 16, 0}}, /* <reg: size 16, offset 0 in v11> */
	{"q12", {244, "v12", 0, 16, 0}}, /* <reg: size 16, offset 0 in v12> */
	{"q13", {245, "v13", 0, 16, 0}}, /* <reg: size 16, offset 0 in v13> */
	{"q14", {246, "v14", 0, 16, 0}}, /* <reg: size 16, offset 0 in v14> */
	{"q15", {247, "v15", 0, 16, 0}}, /* <reg: size 16, offset 0 in v15> */
	{"q16", {248, "v16", 0, 16, 0}}, /* <reg: size 16, offset 0 in v16> */
	{"q17", {249, "v17", 0, 16, 0}}, /* <reg: size 16, offset 0 in v17> */
	{"q18", {250, "v18", 0, 16, 0}}, /* <reg: size 16, offset 0 in v18> */
	{"q19", {251, "v19", 0, 16, 0}}, /* <reg: size 16, offset 0 in v19> */
	{"q20", {252, "v20", 0, 16, 0}}, /* <reg: size 16, offset 0 in v20> */
	{"q21", {253, "v21", 0, 16, 0}}, /* <reg: size 16, offset 0 in v21> */
	{"q22", {254, "v22", 0, 16, 0}}, /* <reg: size 16, offset 0 in v22> */
	{"q23", {255, "v23", 0, 16, 0}}, /* <reg: size 16, offset 0 in v23> */
	{"q24", {256, "v24", 0, 16, 0}}, /* <reg: size 16, offset 0 in v24> */
	{"q25", {257, "v25", 0, 16, 0}}, /* <reg: size 16, offset 0 in v25> */
	{"q26", {258, "v26", 0, 16, 0}}, /* <reg: size 16, offset 0 in v26> */
	{"q27", {259, "v27", 0, 16, 0}}, /* <reg: size 16, offset 0 in v27> */
	{"q28", {260, "v28", 0, 16, 0}}, /* <reg: size 16, offset 0 in v28> */
	{"q29", {261, "v29", 0, 16, 0}}, /* <reg: size 16, offset 0 in v29> */
	{"q30", {262, "v30", 0, 16, 0}}, /* <reg: size 16, offset 0 in v30> */
	{"q31", {264, "v31", 0, 16, 0}}, /* <reg: size 16, offset 0 in v31> */
	{"v0.b[0]", {265, "v0", 0, 1, 0}}, /* <reg: size 1, offset 0 in v0> */
	{"v0.b[1]", {266, "v0", 1, 1, 0}}, /* <reg: size 1, offset 1 in v0> */
	{"v0.b[2]", {267, "v0", 2, 1, 0}}, /* <reg: size 1, offset 2 in v0> */
	{"v0.b[3]", {268, "v0", 3, 1, 0}}, /* <reg: size 1, offset 3 in v0> */
	{"v0.b[4]", {269, "v0", 4, 1, 0}}, /* <reg: size 1, offset 4 in v0> */
	{"v0.b[5]", {270, "v0", 5, 1, 0}}, /* <reg: size 1, offset 5 in v0> */
	{"v0.b[6]", {271, "v0", 6, 1, 0}}, /* <reg: size 1, offset 6 in v0> */
	{"v0.b[7]", {272, "v0", 7, 1, 0}}, /* <reg: size 1, offset 7 in v0> */
	{"v0.b[8]", {273, "v0", 8, 1, 0}}, /* <reg: size 1, offset 8 in v0> */
	{"v0.b[9]", {274, "v0", 9, 1, 0}}, /* <reg: size 1, offset 9 in v0> */
	{"v0.b[10]", {275, "v0", 10, 1, 0}}, /* <reg: size 1, offset 10 in v0> */
	{"v0.b[11]", {276, "v0", 11, 1, 0}}, /* <reg: size 1, offset 11 in v0> */
	{"v0.b[12]", {277, "v0", 12, 1, 0}}, /* <reg: size 1, offset 12 in v0> */
	{"v0.b[13]", {278, "v0", 13, 1, 0}}, /* <reg: size 1, offset 13 in v0> */
	{"v0.b[14]", {279, "v0", 14, 1, 0}}, /* <reg: size 1, offset 14 in v0> */
	{"v0.b[15]", {280, "v0", 15, 1, 0}}, /* <reg: size 1, offset 15 in v0> */
	{"v1.b[0]", {281, "v1", 0, 1, 0}}, /* <reg: size 1, offset 0 in v1> */
	{"v1.b[1]", {282, "v1", 1, 1, 0}}, /* <reg: size 1, offset 1 in v1> */
	{"v1.b[2]", {283, "v1", 2, 1, 0}}, /* <reg: size 1, offset 2 in v1> */
	{"v1.b[3]", {284, "v1", 3, 1, 0}}, /* <reg: size 1, offset 3 in v1> */
	{"v1.b[4]", {285, "v1", 4, 1, 0}}, /* <reg: size 1, offset 4 in v1> */
	{"v1.b[5]", {286, "v1", 5, 1, 0}}, /* <reg: size 1, offset 5 in v1> */
	{"v1.b[6]", {287, "v1", 6, 1, 0}}, /* <reg: size 1, offset 6 in v1> */
	{"v1.b[7]", {288, "v1", 7, 1, 0}}, /* <reg: size 1, offset 7 in v1> */
	{"v1.b[8]", {289, "v1", 8, 1, 0}}, /* <reg: size 1, offset 8 in v1> */
	{"v1.b[9]", {290, "v1", 9, 1, 0}}, /* <reg: size 1, offset 9 in v1> */
	{"v1.b[10]", {291, "v1", 10, 1, 0}}, /* <reg: size 1, offset 10 in v1> */
	{"v1.b[11]", {292, "v1", 11, 1, 0}}, /* <reg: size 1, offset 11 in v1> */
	{"v1.b[12]", {293, "v1", 12, 1, 0}}, /* <reg: size 1, offset 12 in v1> */
	{"v1.b[13]", {294, "v1", 13, 1, 0}}, /* <reg: size 1, offset 13 in v1> */
	{"v1.b[14]", {295, "v1", 14, 1, 0}}, /* <reg: size 1, offset 14 in v1> */
	{"v1.b[15]", {296, "v1", 15, 1, 0}}, /* <reg: size 1, offset 15 in v1> */
	{"v2.b[0]", {297, "v2", 0, 1, 0}}, /* <reg: size 1, offset 0 in v2> */
	{"v2.b[1]", {298, "v2", 1, 1, 0}}, /* <reg: size 1, offset 1 in v2> */
	{"v2.b[2]", {299, "v2", 2, 1, 0}}, /* <reg: size 1, offset 2 in v2> */
	{"v2.b[3]", {300, "v2", 3, 1, 0}}, /* <reg: size 1, offset 3 in v2> */
	{"v2.b[4]", {301, "v2", 4, 1, 0}}, /* <reg: size 1, offset 4 in v2> */
	{"v2.b[5]", {302, "v2", 5, 1, 0}}, /* <reg: size 1, offset 5 in v2> */
	{"v2.b[6]", {303, "v2", 6, 1, 0}}, /* <reg: size 1, offset 6 in v2> */
	{"v2.b[7]", {304, "v2", 7, 1, 0}}, /* <reg: size 1, offset 7 in v2> */
	{"v2.b[8]", {305, "v2", 8, 1, 0}}, /* <reg: size 1, offset 8 in v2> */
	{"v2.b[9]", {306, "v2", 9, 1, 0}}, /* <reg: size 1, offset 9 in v2> */
	{"v2.b[10]", {307, "v2", 10, 1, 0}}, /* <reg: size 1, offset 10 in v2> */
	{"v2.b[11]", {308, "v2", 11, 1, 0}}, /* <reg: size 1, offset 11 in v2> */
	{"v2.b[12]", {309, "v2", 12, 1, 0}}, /* <reg: size 1, offset 12 in v2> */
	{"v2.b[13]", {310, "v2", 13, 1, 0}}, /* <reg: size 1, offset 13 in v2> */
	{"v2.b[14]", {311, "v2", 14, 1, 0}}, /* <reg: size 1, offset 14 in v2> */
	{"v2.b[15]", {312, "v2", 15, 1, 0}}, /* <reg: size 1, offset 15 in v2> */
	{"v3.b[0]", {313, "v3", 0, 1, 0}}, /* <reg: size 1, offset 0 in v3> */
	{"v3.b[1]", {314, "v3", 1, 1, 0}}, /* <reg: size 1, offset 1 in v3> */
	{"v3.b[2]", {315, "v3", 2, 1, 0}}, /* <reg: size 1, offset 2 in v3> */
	{"v3.b[3]", {316, "v3", 3, 1, 0}}, /* <reg: size 1, offset 3 in v3> */
	{"v3.b[4]", {317, "v3", 4, 1, 0}}, /* <reg: size 1, offset 4 in v3> */
	{"v3.b[5]", {318, "v3", 5, 1, 0}}, /* <reg: size 1, offset 5 in v3> */
	{"v3.b[6]", {319, "v3", 6, 1, 0}}, /* <reg: size 1, offset 6 in v3> */
	{"v3.b[7]", {320, "v3", 7, 1, 0}}, /* <reg: size 1, offset 7 in v3> */
	{"v3.b[8]", {321, "v3", 8, 1, 0}}, /* <reg: size 1, offset 8 in v3> */
	{"v3.b[9]", {322, "v3", 9, 1, 0}}, /* <reg: size 1, offset 9 in v3> */
	{"v3.b[10]", {323, "v3", 10, 1, 0}}, /* <reg: size 1, offset 10 in v3> */
	{"v3.b[11]", {324, "v3", 11, 1, 0}}, /* <reg: size 1, offset 11 in v3> */
	{"v3.b[12]", {325, "v3", 12, 1, 0}}, /* <reg: size 1, offset 12 in v3> */
	{"v3.b[13]", {326, "v3", 13, 1, 0}}, /* <reg: size 1, offset 13 in v3> */
	{"v3.b[14]", {327, "v3", 14, 1, 0}}, /* <reg: size 1, offset 14 in v3> */
	{"v3.b[15]", {328, "v3", 15, 1, 0}}, /* <reg: size 1, offset 15 in v3> */
	{"v4.b[0]", {329, "v4", 0, 1, 0}}, /* <reg: size 1, offset 0 in v4> */
	{"v4.b[1]", {330, "v4", 1, 1, 0}}, /* <reg: size 1, offset 1 in v4> */
	{"v4.b[2]", {331, "v4", 2, 1, 0}}, /* <reg: size 1, offset 2 in v4> */
	{"v4.b[3]", {332, "v4", 3, 1, 0}}, /* <reg: size 1, offset 3 in v4> */
	{"v4.b[4]", {333, "v4", 4, 1, 0}}, /* <reg: size 1, offset 4 in v4> */
	{"v4.b[5]", {334, "v4", 5, 1, 0}}, /* <reg: size 1, offset 5 in v4> */
	{"v4.b[6]", {335, "v4", 6, 1, 0}}, /* <reg: size 1, offset 6 in v4> */
	{"v4.b[7]", {336, "v4", 7, 1, 0}}, /* <reg: size 1, offset 7 in v4> */
	{"v4.b[8]", {337, "v4", 8, 1, 0}}, /* <reg: size 1, offset 8 in v4> */
	{"v4.b[9]", {338, "v4", 9, 1, 0}}, /* <reg: size 1, offset 9 in v4> */
	{"v4.b[10]", {339, "v4", 10, 1, 0}}, /* <reg: size 1, offset 10 in v4> */
	{"v4.b[11]", {340, "v4", 11, 1, 0}}, /* <reg: size 1, offset 11 in v4> */
	{"v4.b[12]", {341, "v4", 12, 1, 0}}, /* <reg: size 1, offset 12 in v4> */
	{"v4.b[13]", {342, "v4", 13, 1, 0}}, /* <reg: size 1, offset 13 in v4> */
	{"v4.b[14]", {343, "v4", 14, 1, 0}}, /* <reg: size 1, offset 14 in v4> */
	{"v4.b[15]", {344, "v4", 15, 1, 0}}, /* <reg: size 1, offset 15 in v4> */
	{"v5.b[0]", {345, "v5", 0, 1, 0}}, /* <reg: size 1, offset 0 in v5> */
	{"v5.b[1]", {346, "v5", 1, 1, 0}}, /* <reg: size 1, offset 1 in v5> */
	{"v5.b[2]", {347, "v5", 2, 1, 0}}, /* <reg: size 1, offset 2 in v5> */
	{"v5.b[3]", {348, "v5", 3, 1, 0}}, /* <reg: size 1, offset 3 in v5> */
	{"v5.b[4]", {349, "v5", 4, 1, 0}}, /* <reg: size 1, offset 4 in v5> */
	{"v5.b[5]", {350, "v5", 5, 1, 0}}, /* <reg: size 1, offset 5 in v5> */
	{"v5.b[6]", {351, "v5", 6, 1, 0}}, /* <reg: size 1, offset 6 in v5> */
	{"v5.b[7]", {352, "v5", 7, 1, 0}}, /* <reg: size 1, offset 7 in v5> */
	{"v5.b[8]", {353, "v5", 8, 1, 0}}, /* <reg: size 1, offset 8 in v5> */
	{"v5.b[9]", {354, "v5", 9, 1, 0}}, /* <reg: size 1, offset 9 in v5> */
	{"v5.b[10]", {355, "v5", 10, 1, 0}}, /* <reg: size 1, offset 10 in v5> */
	{"v5.b[11]", {356, "v5", 11, 1, 0}}, /* <reg: size 1, offset 11 in v5> */
	{"v5.b[12]", {357, "v5", 12, 1, 0}}, /* <reg: size 1, offset 12 in v5> */
	{"v5.b[13]", {358, "v5", 13, 1, 0}}, /* <reg: size 1, offset 13 in v5> */
	{"v5.b[14]", {359, "v5", 14, 1, 0}}, /* <reg: size 1, offset 14 in v5> */
	{"v5.b[15]", {360, "v5", 15, 1, 0}}, /* <reg: size 1, offset 15 in v5> */
	{"v6.b[0]", {361, "v6", 0, 1, 0}}, /* <reg: size 1, offset 0 in v6> */
	{"v6.b[1]", {362, "v6", 1, 1, 0}}, /* <reg: size 1, offset 1 in v6> */
	{"v6.b[2]", {363, "v6", 2, 1, 0}}, /* <reg: size 1, offset 2 in v6> */
	{"v6.b[3]", {364, "v6", 3, 1, 0}}, /* <reg: size 1, offset 3 in v6> */
	{"v6.b[4]", {365, "v6", 4, 1, 0}}, /* <reg: size 1, offset 4 in v6> */
	{"v6.b[5]", {366, "v6", 5, 1, 0}}, /* <reg: size 1, offset 5 in v6> */
	{"v6.b[6]", {367, "v6", 6, 1, 0}}, /* <reg: size 1, offset 6 in v6> */
	{"v6.b[7]", {368, "v6", 7, 1, 0}}, /* <reg: size 1, offset 7 in v6> */
	{"v6.b[8]", {369, "v6", 8, 1, 0}}, /* <reg: size 1, offset 8 in v6> */
	{"v6.b[9]", {370, "v6", 9, 1, 0}}, /* <reg: size 1, offset 9 in v6> */
	{"v6.b[10]", {371, "v6", 10, 1, 0}}, /* <reg: size 1, offset 10 in v6> */
	{"v6.b[11]", {372, "v6", 11, 1, 0}}, /* <reg: size 1, offset 11 in v6> */
	{"v6.b[12]", {373, "v6", 12, 1, 0}}, /* <reg: size 1, offset 12 in v6> */
	{"v6.b[13]", {374, "v6", 13, 1, 0}}, /* <reg: size 1, offset 13 in v6> */
	{"v6.b[14]", {375, "v6", 14, 1, 0}}, /* <reg: size 1, offset 14 in v6> */
	{"v6.b[15]", {376, "v6", 15, 1, 0}}, /* <reg: size 1, offset 15 in v6> */
	{"v7.b[0]", {377, "v7", 0, 1, 0}}, /* <reg: size 1, offset 0 in v7> */
	{"v7.b[1]", {378, "v7", 1, 1, 0}}, /* <reg: size 1, offset 1 in v7> */
	{"v7.b[2]", {379, "v7", 2, 1, 0}}, /* <reg: size 1, offset 2 in v7> */
	{"v7.b[3]", {380, "v7", 3, 1, 0}}, /* <reg: size 1, offset 3 in v7> */
	{"v7.b[4]", {381, "v7", 4, 1, 0}}, /* <reg: size 1, offset 4 in v7> */
	{"v7.b[5]", {382, "v7", 5, 1, 0}}, /* <reg: size 1, offset 5 in v7> */
	{"v7.b[6]", {383, "v7", 6, 1, 0}}, /* <reg: size 1, offset 6 in v7> */
	{"v7.b[7]", {384, "v7", 7, 1, 0}}, /* <reg: size 1, offset 7 in v7> */
	{"v7.b[8]", {385, "v7", 8, 1, 0}}, /* <reg: size 1, offset 8 in v7> */
	{"v7.b[9]", {386, "v7", 9, 1, 0}}, /* <reg: size 1, offset 9 in v7> */
	{"v7.b[10]", {387, "v7", 10, 1, 0}}, /* <reg: size 1, offset 10 in v7> */
	{"v7.b[11]", {388, "v7", 11, 1, 0}}, /* <reg: size 1, offset 11 in v7> */
	{"v7.b[12]", {389, "v7", 12, 1, 0}}, /* <reg: size 1, offset 12 in v7> */
	{"v7.b[13]", {390, "v7", 13, 1, 0}}, /* <reg: size 1, offset 13 in v7> */
	{"v7.b[14]", {391, "v7", 14, 1, 0}}, /* <reg: size 1, offset 14 in v7> */
	{"v7.b[15]", {392, "v7", 15, 1, 0}}, /* <reg: size 1, offset 15 in v7> */
	{"v8.b[0]", {393, "v8", 0, 1, 0}}, /* <reg: size 1, offset 0 in v8> */
	{"v8.b[1]", {394, "v8", 1, 1, 0}}, /* <reg: size 1, offset 1 in v8> */
	{"v8.b[2]", {395, "v8", 2, 1, 0}}, /* <reg: size 1, offset 2 in v8> */
	{"v8.b[3]", {396, "v8", 3, 1, 0}}, /* <reg: size 1, offset 3 in v8> */
	{"v8.b[4]", {397, "v8", 4, 1, 0}}, /* <reg: size 1, offset 4 in v8> */
	{"v8.b[5]", {398, "v8", 5, 1, 0}}, /* <reg: size 1, offset 5 in v8> */
	{"v8.b[6]", {399, "v8", 6, 1, 0}}, /* <reg: size 1, offset 6 in v8> */
	{"v8.b[7]", {400, "v8", 7, 1, 0}}, /* <reg: size 1, offset 7 in v8> */
	{"v8.b[8]", {401, "v8", 8, 1, 0}}, /* <reg: size 1, offset 8 in v8> */
	{"v8.b[9]", {402, "v8", 9, 1, 0}}, /* <reg: size 1, offset 9 in v8> */
	{"v8.b[10]", {403, "v8", 10, 1, 0}}, /* <reg: size 1, offset 10 in v8> */
	{"v8.b[11]", {404, "v8", 11, 1, 0}}, /* <reg: size 1, offset 11 in v8> */
	{"v8.b[12]", {405, "v8", 12, 1, 0}}, /* <reg: size 1, offset 12 in v8> */
	{"v8.b[13]", {406, "v8", 13, 1, 0}}, /* <reg: size 1, offset 13 in v8> */
	{"v8.b[14]", {407, "v8", 14, 1, 0}}, /* <reg: size 1, offset 14 in v8> */
	{"v8.b[15]", {408, "v8", 15, 1, 0}}, /* <reg: size 1, offset 15 in v8> */
	{"v9.b[0]", {409, "v9", 0, 1, 0}}, /* <reg: size 1, offset 0 in v9> */
	{"v9.b[1]", {410, "v9", 1, 1, 0}}, /* <reg: size 1, offset 1 in v9> */
	{"v9.b[2]", {411, "v9", 2, 1, 0}}, /* <reg: size 1, offset 2 in v9> */
	{"v9.b[3]", {412, "v9", 3, 1, 0}}, /* <reg: size 1, offset 3 in v9> */
	{"v9.b[4]", {413, "v9", 4, 1, 0}}, /* <reg: size 1, offset 4 in v9> */
	{"v9.b[5]", {414, "v9", 5, 1, 0}}, /* <reg: size 1, offset 5 in v9> */
	{"v9.b[6]", {415, "v9", 6, 1, 0}}, /* <reg: size 1, offset 6 in v9> */
	{"v9.b[7]", {416, "v9", 7, 1, 0}}, /* <reg: size 1, offset 7 in v9> */
	{"v9.b[8]", {417, "v9", 8, 1, 0}}, /* <reg: size 1, offset 8 in v9> */
	{"v9.b[9]", {418, "v9", 9, 1, 0}}, /* <reg: size 1, offset 9 in v9> */
	{"v9.b[10]", {419, "v9", 10, 1, 0}}, /* <reg: size 1, offset 10 in v9> */
	{"v9.b[11]", {420, "v9", 11, 1, 0}}, /* <reg: size 1, offset 11 in v9> */
	{"v9.b[12]", {421, "v9", 12, 1, 0}}, /* <reg: size 1, offset 12 in v9> */
	{"v9.b[13]", {422, "v9", 13, 1, 0}}, /* <reg: size 1, offset 13 in v9> */
	{"v9.b[14]", {423, "v9", 14, 1, 0}}, /* <reg: size 1, offset 14 in v9> */
	{"v9.b[15]", {424, "v9", 15, 1, 0}}, /* <reg: size 1, offset 15 in v9> */
	{"v10.b[0]", {425, "v10", 0, 1, 0}}, /* <reg: size 1, offset 0 in v10> */
	{"v10.b[1]", {426, "v10", 1, 1, 0}}, /* <reg: size 1, offset 1 in v10> */
	{"v10.b[2]", {427, "v10", 2, 1, 0}}, /* <reg: size 1, offset 2 in v10> */
	{"v10.b[3]", {428, "v10", 3, 1, 0}}, /* <reg: size 1, offset 3 in v10> */
	{"v10.b[4]", {429, "v10", 4, 1, 0}}, /* <reg: size 1, offset 4 in v10> */
	{"v10.b[5]", {430, "v10", 5, 1, 0}}, /* <reg: size 1, offset 5 in v10> */
	{"v10.b[6]", {431, "v10", 6, 1, 0}}, /* <reg: size 1, offset 6 in v10> */
	{"v10.b[7]", {432, "v10", 7, 1, 0}}, /* <reg: size 1, offset 7 in v10> */
	{"v10.b[8]", {433, "v10", 8, 1, 0}}, /* <reg: size 1, offset 8 in v10> */
	{"v10.b[9]", {434, "v10", 9, 1, 0}}, /* <reg: size 1, offset 9 in v10> */
	{"v10.b[10]", {435, "v10", 10, 1, 0}}, /* <reg: size 1, offset 10 in v10> */
	{"v10.b[11]", {436, "v10", 11, 1, 0}}, /* <reg: size 1, offset 11 in v10> */
	{"v10.b[12]", {437, "v10", 12, 1, 0}}, /* <reg: size 1, offset 12 in v10> */
	{"v10.b[13]", {438, "v10", 13, 1, 0}}, /* <reg: size 1, offset 13 in v10> */
	{"v10.b[14]", {439, "v10", 14, 1, 0}}, /* <reg: size 1, offset 14 in v10> */
	{"v10.b[15]", {440, "v10", 15, 1, 0}}, /* <reg: size 1, offset 15 in v10> */
	{"v11.b[0]", {441, "v11", 0, 1, 0}}, /* <reg: size 1, offset 0 in v11> */
	{"v11.b[1]", {442, "v11", 1, 1, 0}}, /* <reg: size 1, offset 1 in v11> */
	{"v11.b[2]", {443, "v11", 2, 1, 0}}, /* <reg: size 1, offset 2 in v11> */
	{"v11.b[3]", {444, "v11", 3, 1, 0}}, /* <reg: size 1, offset 3 in v11> */
	{"v11.b[4]", {445, "v11", 4, 1, 0}}, /* <reg: size 1, offset 4 in v11> */
	{"v11.b[5]", {446, "v11", 5, 1, 0}}, /* <reg: size 1, offset 5 in v11> */
	{"v11.b[6]", {447, "v11", 6, 1, 0}}, /* <reg: size 1, offset 6 in v11> */
	{"v11.b[7]", {448, "v11", 7, 1, 0}}, /* <reg: size 1, offset 7 in v11> */
	{"v11.b[8]", {449, "v11", 8, 1, 0}}, /* <reg: size 1, offset 8 in v11> */
	{"v11.b[9]", {450, "v11", 9, 1, 0}}, /* <reg: size 1, offset 9 in v11> */
	{"v11.b[10]", {451, "v11", 10, 1, 0}}, /* <reg: size 1, offset 10 in v11> */
	{"v11.b[11]", {452, "v11", 11, 1, 0}}, /* <reg: size 1, offset 11 in v11> */
	{"v11.b[12]", {453, "v11", 12, 1, 0}}, /* <reg: size 1, offset 12 in v11> */
	{"v11.b[13]", {454, "v11", 13, 1, 0}}, /* <reg: size 1, offset 13 in v11> */
	{"v11.b[14]", {455, "v11", 14, 1, 0}}, /* <reg: size 1, offset 14 in v11> */
	{"v11.b[15]", {456, "v11", 15, 1, 0}}, /* <reg: size 1, offset 15 in v11> */
	{"v12.b[0]", {457, "v12", 0, 1, 0}}, /* <reg: size 1, offset 0 in v12> */
	{"v12.b[1]", {458, "v12", 1, 1, 0}}, /* <reg: size 1, offset 1 in v12> */
	{"v12.b[2]", {459, "v12", 2, 1, 0}}, /* <reg: size 1, offset 2 in v12> */
	{"v12.b[3]", {460, "v12", 3, 1, 0}}, /* <reg: size 1, offset 3 in v12> */
	{"v12.b[4]", {461, "v12", 4, 1, 0}}, /* <reg: size 1, offset 4 in v12> */
	{"v12.b[5]", {462, "v12", 5, 1, 0}}, /* <reg: size 1, offset 5 in v12> */
	{"v12.b[6]", {463, "v12", 6, 1, 0}}, /* <reg: size 1, offset 6 in v12> */
	{"v12.b[7]", {464, "v12", 7, 1, 0}}, /* <reg: size 1, offset 7 in v12> */
	{"v12.b[8]", {465, "v12", 8, 1, 0}}, /* <reg: size 1, offset 8 in v12> */
	{"v12.b[9]", {466, "v12", 9, 1, 0}}, /* <reg: size 1, offset 9 in v12> */
	{"v12.b[10]", {467, "v12", 10, 1, 0}}, /* <reg: size 1, offset 10 in v12> */
	{"v12.b[11]", {468, "v12", 11, 1, 0}}, /* <reg: size 1, offset 11 in v12> */
	{"v12.b[12]", {469, "v12", 12, 1, 0}}, /* <reg: size 1, offset 12 in v12> */
	{"v12.b[13]", {470, "v12", 13, 1, 0}}, /* <reg: size 1, offset 13 in v12> */
	{"v12.b[14]", {471, "v12", 14, 1, 0}}, /* <reg: size 1, offset 14 in v12> */
	{"v12.b[15]", {472, "v12", 15, 1, 0}}, /* <reg: size 1, offset 15 in v12> */
	{"v13.b[0]", {473, "v13", 0, 1, 0}}, /* <reg: size 1, offset 0 in v13> */
	{"v13.b[1]", {474, "v13", 1, 1, 0}}, /* <reg: size 1, offset 1 in v13> */
	{"v13.b[2]", {475, "v13", 2, 1, 0}}, /* <reg: size 1, offset 2 in v13> */
	{"v13.b[3]", {476, "v13", 3, 1, 0}}, /* <reg: size 1, offset 3 in v13> */
	{"v13.b[4]", {477, "v13", 4, 1, 0}}, /* <reg: size 1, offset 4 in v13> */
	{"v13.b[5]", {478, "v13", 5, 1, 0}}, /* <reg: size 1, offset 5 in v13> */
	{"v13.b[6]", {479, "v13", 6, 1, 0}}, /* <reg: size 1, offset 6 in v13> */
	{"v13.b[7]", {480, "v13", 7, 1, 0}}, /* <reg: size 1, offset 7 in v13> */
	{"v13.b[8]", {481, "v13", 8, 1, 0}}, /* <reg: size 1, offset 8 in v13> */
	{"v13.b[9]", {482, "v13", 9, 1, 0}}, /* <reg: size 1, offset 9 in v13> */
	{"v13.b[10]", {483, "v13", 10, 1, 0}}, /* <reg: size 1, offset 10 in v13> */
	{"v13.b[11]", {484, "v13", 11, 1, 0}}, /* <reg: size 1, offset 11 in v13> */
	{"v13.b[12]", {485, "v13", 12, 1, 0}}, /* <reg: size 1, offset 12 in v13> */
	{"v13.b[13]", {486, "v13", 13, 1, 0}}, /* <reg: size 1, offset 13 in v13> */
	{"v13.b[14]", {487, "v13", 14, 1, 0}}, /* <reg: size 1, offset 14 in v13> */
	{"v13.b[15]", {488, "v13", 15, 1, 0}}, /* <reg: size 1, offset 15 in v13> */
	{"v14.b[0]", {489, "v14", 0, 1, 0}}, /* <reg: size 1, offset 0 in v14> */
	{"v14.b[1]", {490, "v14", 1, 1, 0}}, /* <reg: size 1, offset 1 in v14> */
	{"v14.b[2]", {491, "v14", 2, 1, 0}}, /* <reg: size 1, offset 2 in v14> */
	{"v14.b[3]", {492, "v14", 3, 1, 0}}, /* <reg: size 1, offset 3 in v14> */
	{"v14.b[4]", {493, "v14", 4, 1, 0}}, /* <reg: size 1, offset 4 in v14> */
	{"v14.b[5]", {494, "v14", 5, 1, 0}}, /* <reg: size 1, offset 5 in v14> */
	{"v14.b[6]", {495, "v14", 6, 1, 0}}, /* <reg: size 1, offset 6 in v14> */
	{"v14.b[7]", {496, "v14", 7, 1, 0}}, /* <reg: size 1, offset 7 in v14> */
	{"v14.b[8]", {497, "v14", 8, 1, 0}}, /* <reg: size 1, offset 8 in v14> */
	{"v14.b[9]", {498, "v14", 9, 1, 0}}, /* <reg: size 1, offset 9 in v14> */
	{"v14.b[10]", {499, "v14", 10, 1, 0}}, /* <reg: size 1, offset 10 in v14> */
	{"v14.b[11]", {500, "v14", 11, 1, 0}}, /* <reg: size 1, offset 11 in v14> */
	{"v14.b[12]", {501, "v14", 12, 1, 0}}, /* <reg: size 1, offset 12 in v14> */
	{"v14.b[13]", {502, "v14", 13, 1, 0}}, /* <reg: size 1, offset 13 in v14> */
	{"v14.b[14]", {503, "v14", 14, 1, 0}}, /* <reg: size 1, offset 14 in v14> */
	{"v14.b[15]", {504, "v14", 15, 1, 0}}, /* <reg: size 1, offset 15 in v14> */
	{"v15.b[0]", {505, "v15", 0, 1, 0}}, /* <reg: size 1, offset 0 in v15> */
	{"v15.b[1]", {506, "v15", 1, 1, 0}}, /* <reg: size 1, offset 1 in v15> */
	{"v15.b[2]", {507, "v15", 2, 1, 0}}, /* <reg: size 1, offset 2 in v15> */
	{"v15.b[3]", {508, "v15", 3, 1, 0}}, /* <reg: size 1, offset 3 in v15> */
	{"v15.b[4]", {509, "v15", 4, 1, 0}}, /* <reg: size 1, offset 4 in v15> */
	{"v15.b[5]", {510, "v15", 5, 1, 0}}, /* <reg: size 1, offset 5 in v15> */
	{"v15.b[6]", {511, "v15", 6, 1, 0}}, /* <reg: size 1, offset 6 in v15> */
	{"v15.b[7]", {512, "v15", 7, 1, 0}}, /* <reg: size 1, offset 7 in v15> */
	{"v15.b[8]", {513, "v15", 8, 1, 0}}, /* <reg: size 1, offset 8 in v15> */
	{"v15.b[9]", {514, "v15", 9, 1, 0}}, /* <reg: size 1, offset 9 in v15> */
	{"v15.b[10]", {515, "v15", 10, 1, 0}}, /* <reg: size 1, offset 10 in v15> */
	{"v15.b[11]", {516, "v15", 11, 1, 0}}, /* <reg: size 1, offset 11 in v15> */
	{"v15.b[12]", {517, "v15", 12, 1, 0}}, /* <reg: size 1, offset 12 in v15> */
	{"v15.b[13]", {518, "v15", 13, 1, 0}}, /* <reg: size 1, offset 13 in v15> */
	{"v15.b[14]", {519, "v15", 14, 1, 0}}, /* <reg: size 1, offset 14 in v15> */
	{"v15.b[15]", {520, "v15", 15, 1, 0}}, /* <reg: size 1, offset 15 in v15> */
	{"v16.b[0]", {521, "v16", 0, 1, 0}}, /* <reg: size 1, offset 0 in v16> */
	{"v16.b[1]", {522, "v16", 1, 1, 0}}, /* <reg: size 1, offset 1 in v16> */
	{"v16.b[2]", {523, "v16", 2, 1, 0}}, /* <reg: size 1, offset 2 in v16> */
	{"v16.b[3]", {524, "v16", 3, 1, 0}}, /* <reg: size 1, offset 3 in v16> */
	{"v16.b[4]", {525, "v16", 4, 1, 0}}, /* <reg: size 1, offset 4 in v16> */
	{"v16.b[5]", {526, "v16", 5, 1, 0}}, /* <reg: size 1, offset 5 in v16> */
	{"v16.b[6]", {527, "v16", 6, 1, 0}}, /* <reg: size 1, offset 6 in v16> */
	{"v16.b[7]", {528, "v16", 7, 1, 0}}, /* <reg: size 1, offset 7 in v16> */
	{"v16.b[8]", {529, "v16", 8, 1, 0}}, /* <reg: size 1, offset 8 in v16> */
	{"v16.b[9]", {530, "v16", 9, 1, 0}}, /* <reg: size 1, offset 9 in v16> */
	{"v16.b[10]", {531, "v16", 10, 1, 0}}, /* <reg: size 1, offset 10 in v16> */
	{"v16.b[11]", {532, "v16", 11, 1, 0}}, /* <reg: size 1, offset 11 in v16> */
	{"v16.b[12]", {533, "v16", 12, 1, 0}}, /* <reg: size 1, offset 12 in v16> */
	{"v16.b[13]", {534, "v16", 13, 1, 0}}, /* <reg: size 1, offset 13 in v16> */
	{"v16.b[14]", {535, "v16", 14, 1, 0}}, /* <reg: size 1, offset 14 in v16> */
	{"v16.b[15]", {536, "v16", 15, 1, 0}}, /* <reg: size 1, offset 15 in v16> */
	{"v17.b[0]", {537, "v17", 0, 1, 0}}, /* <reg: size 1, offset 0 in v17> */
	{"v17.b[1]", {538, "v17", 1, 1, 0}}, /* <reg: size 1, offset 1 in v17> */
	{"v17.b[2]", {539, "v17", 2, 1, 0}}, /* <reg: size 1, offset 2 in v17> */
	{"v17.b[3]", {540, "v17", 3, 1, 0}}, /* <reg: size 1, offset 3 in v17> */
	{"v17.b[4]", {541, "v17", 4, 1, 0}}, /* <reg: size 1, offset 4 in v17> */
	{"v17.b[5]", {542, "v17", 5, 1, 0}}, /* <reg: size 1, offset 5 in v17> */
	{"v17.b[6]", {543, "v17", 6, 1, 0}}, /* <reg: size 1, offset 6 in v17> */
	{"v17.b[7]", {544, "v17", 7, 1, 0}}, /* <reg: size 1, offset 7 in v17> */
	{"v17.b[8]", {545, "v17", 8, 1, 0}}, /* <reg: size 1, offset 8 in v17> */
	{"v17.b[9]", {546, "v17", 9, 1, 0}}, /* <reg: size 1, offset 9 in v17> */
	{"v17.b[10]", {547, "v17", 10, 1, 0}}, /* <reg: size 1, offset 10 in v17> */
	{"v17.b[11]", {548, "v17", 11, 1, 0}}, /* <reg: size 1, offset 11 in v17> */
	{"v17.b[12]", {549, "v17", 12, 1, 0}}, /* <reg: size 1, offset 12 in v17> */
	{"v17.b[13]", {550, "v17", 13, 1, 0}}, /* <reg: size 1, offset 13 in v17> */
	{"v17.b[14]", {551, "v17", 14, 1, 0}}, /* <reg: size 1, offset 14 in v17> */
	{"v17.b[15]", {552, "v17", 15, 1, 0}}, /* <reg: size 1, offset 15 in v17> */
	{"v18.b[0]", {553, "v18", 0, 1, 0}}, /* <reg: size 1, offset 0 in v18> */
	{"v18.b[1]", {554, "v18", 1, 1, 0}}, /* <reg: size 1, offset 1 in v18> */
	{"v18.b[2]", {555, "v18", 2, 1, 0}}, /* <reg: size 1, offset 2 in v18> */
	{"v18.b[3]", {556, "v18", 3, 1, 0}}, /* <reg: size 1, offset 3 in v18> */
	{"v18.b[4]", {557, "v18", 4, 1, 0}}, /* <reg: size 1, offset 4 in v18> */
	{"v18.b[5]", {558, "v18", 5, 1, 0}}, /* <reg: size 1, offset 5 in v18> */
	{"v18.b[6]", {559, "v18", 6, 1, 0}}, /* <reg: size 1, offset 6 in v18> */
	{"v18.b[7]", {560, "v18", 7, 1, 0}}, /* <reg: size 1, offset 7 in v18> */
	{"v18.b[8]", {561, "v18", 8, 1, 0}}, /* <reg: size 1, offset 8 in v18> */
	{"v18.b[9]", {562, "v18", 9, 1, 0}}, /* <reg: size 1, offset 9 in v18> */
	{"v18.b[10]", {563, "v18", 10, 1, 0}}, /* <reg: size 1, offset 10 in v18> */
	{"v18.b[11]", {564, "v18", 11, 1, 0}}, /* <reg: size 1, offset 11 in v18> */
	{"v18.b[12]", {565, "v18", 12, 1, 0}}, /* <reg: size 1, offset 12 in v18> */
	{"v18.b[13]", {566, "v18", 13, 1, 0}}, /* <reg: size 1, offset 13 in v18> */
	{"v18.b[14]", {567, "v18", 14, 1, 0}}, /* <reg: size 1, offset 14 in v18> */
	{"v18.b[15]", {568, "v18", 15, 1, 0}}, /* <reg: size 1, offset 15 in v18> */
	{"v19.b[0]", {569, "v19", 0, 1, 0}}, /* <reg: size 1, offset 0 in v19> */
	{"v19.b[1]", {570, "v19", 1, 1, 0}}, /* <reg: size 1, offset 1 in v19> */
	{"v19.b[2]", {571, "v19", 2, 1, 0}}, /* <reg: size 1, offset 2 in v19> */
	{"v19.b[3]", {572, "v19", 3, 1, 0}}, /* <reg: size 1, offset 3 in v19> */
	{"v19.b[4]", {573, "v19", 4, 1, 0}}, /* <reg: size 1, offset 4 in v19> */
	{"v19.b[5]", {574, "v19", 5, 1, 0}}, /* <reg: size 1, offset 5 in v19> */
	{"v19.b[6]", {575, "v19", 6, 1, 0}}, /* <reg: size 1, offset 6 in v19> */
	{"v19.b[7]", {576, "v19", 7, 1, 0}}, /* <reg: size 1, offset 7 in v19> */
	{"v19.b[8]", {577, "v19", 8, 1, 0}}, /* <reg: size 1, offset 8 in v19> */
	{"v19.b[9]", {578, "v19", 9, 1, 0}}, /* <reg: size 1, offset 9 in v19> */
	{"v19.b[10]", {579, "v19", 10, 1, 0}}, /* <reg: size 1, offset 10 in v19> */
	{"v19.b[11]", {580, "v19", 11, 1, 0}}, /* <reg: size 1, offset 11 in v19> */
	{"v19.b[12]", {581, "v19", 12, 1, 0}}, /* <reg: size 1, offset 12 in v19> */
	{"v19.b[13]", {582, "v19", 13, 1, 0}}, /* <reg: size 1, offset 13 in v19> */
	{"v19.b[14]", {583, "v19", 14, 1, 0}}, /* <reg: size 1, offset 14 in v19> */
	{"v19.b[15]", {584, "v19", 15, 1, 0}}, /* <reg: size 1, offset 15 in v19> */
	{"v20.b[0]", {585, "v20", 0, 1, 0}}, /* <reg: size 1, offset 0 in v20> */
	{"v20.b[1]", {586, "v20", 1, 1, 0}}, /* <reg: size 1, offset 1 in v20> */
	{"v20.b[2]", {587, "v20", 2, 1, 0}}, /* <reg: size 1, offset 2 in v20> */
	{"v20.b[3]", {588, "v20", 3, 1, 0}}, /* <reg: size 1, offset 3 in v20> */
	{"v20.b[4]", {589, "v20", 4, 1, 0}}, /* <reg: size 1, offset 4 in v20> */
	{"v20.b[5]", {590, "v20", 5, 1, 0}}, /* <reg: size 1, offset 5 in v20> */
	{"v20.b[6]", {591, "v20", 6, 1, 0}}, /* <reg: size 1, offset 6 in v20> */
	{"v20.b[7]", {592, "v20", 7, 1, 0}}, /* <reg: size 1, offset 7 in v20> */
	{"v20.b[8]", {593, "v20", 8, 1, 0}}, /* <reg: size 1, offset 8 in v20> */
	{"v20.b[9]", {594, "v20", 9, 1, 0}}, /* <reg: size 1, offset 9 in v20> */
	{"v20.b[10]", {595, "v20", 10, 1, 0}}, /* <reg: size 1, offset 10 in v20> */
	{"v20.b[11]", {596, "v20", 11, 1, 0}}, /* <reg: size 1, offset 11 in v20> */
	{"v20.b[12]", {597, "v20", 12, 1, 0}}, /* <reg: size 1, offset 12 in v20> */
	{"v20.b[13]", {598, "v20", 13, 1, 0}}, /* <reg: size 1, offset 13 in v20> */
	{"v20.b[14]", {599, "v20", 14, 1, 0}}, /* <reg: size 1, offset 14 in v20> */
	{"v20.b[15]", {600, "v20", 15, 1, 0}}, /* <reg: size 1, offset 15 in v20> */
	{"v21.b[0]", {601, "v21", 0, 1, 0}}, /* <reg: size 1, offset 0 in v21> */
	{"v21.b[1]", {602, "v21", 1, 1, 0}}, /* <reg: size 1, offset 1 in v21> */
	{"v21.b[2]", {603, "v21", 2, 1, 0}}, /* <reg: size 1, offset 2 in v21> */
	{"v21.b[3]", {604, "v21", 3, 1, 0}}, /* <reg: size 1, offset 3 in v21> */
	{"v21.b[4]", {605, "v21", 4, 1, 0}}, /* <reg: size 1, offset 4 in v21> */
	{"v21.b[5]", {606, "v21", 5, 1, 0}}, /* <reg: size 1, offset 5 in v21> */
	{"v21.b[6]", {607, "v21", 6, 1, 0}}, /* <reg: size 1, offset 6 in v21> */
	{"v21.b[7]", {608, "v21", 7, 1, 0}}, /* <reg: size 1, offset 7 in v21> */
	{"v21.b[8]", {609, "v21", 8, 1, 0}}, /* <reg: size 1, offset 8 in v21> */
	{"v21.b[9]", {610, "v21", 9, 1, 0}}, /* <reg: size 1, offset 9 in v21> */
	{"v21.b[10]", {611, "v21", 10, 1, 0}}, /* <reg: size 1, offset 10 in v21> */
	{"v21.b[11]", {612, "v21", 11, 1, 0}}, /* <reg: size 1, offset 11 in v21> */
	{"v21.b[12]", {613, "v21", 12, 1, 0}}, /* <reg: size 1, offset 12 in v21> */
	{"v21.b[13]", {614, "v21", 13, 1, 0}}, /* <reg: size 1, offset 13 in v21> */
	{"v21.b[14]", {615, "v21", 14, 1, 0}}, /* <reg: size 1, offset 14 in v21> */
	{"v21.b[15]", {616, "v21", 15, 1, 0}}, /* <reg: size 1, offset 15 in v21> */
	{"v22.b[0]", {617, "v22", 0, 1, 0}}, /* <reg: size 1, offset 0 in v22> */
	{"v22.b[1]", {618, "v22", 1, 1, 0}}, /* <reg: size 1, offset 1 in v22> */
	{"v22.b[2]", {619, "v22", 2, 1, 0}}, /* <reg: size 1, offset 2 in v22> */
	{"v22.b[3]", {620, "v22", 3, 1, 0}}, /* <reg: size 1, offset 3 in v22> */
	{"v22.b[4]", {621, "v22", 4, 1, 0}}, /* <reg: size 1, offset 4 in v22> */
	{"v22.b[5]", {622, "v22", 5, 1, 0}}, /* <reg: size 1, offset 5 in v22> */
	{"v22.b[6]", {623, "v22", 6, 1, 0}}, /* <reg: size 1, offset 6 in v22> */
	{"v22.b[7]", {624, "v22", 7, 1, 0}}, /* <reg: size 1, offset 7 in v22> */
	{"v22.b[8]", {625, "v22", 8, 1, 0}}, /* <reg: size 1, offset 8 in v22> */
	{"v22.b[9]", {626, "v22", 9, 1, 0}}, /* <reg: size 1, offset 9 in v22> */
	{"v22.b[10]", {627, "v22", 10, 1, 0}}, /* <reg: size 1, offset 10 in v22> */
	{"v22.b[11]", {628, "v22", 11, 1, 0}}, /* <reg: size 1, offset 11 in v22> */
	{"v22.b[12]", {629, "v22", 12, 1, 0}}, /* <reg: size 1, offset 12 in v22> */
	{"v22.b[13]", {630, "v22", 13, 1, 0}}, /* <reg: size 1, offset 13 in v22> */
	{"v22.b[14]", {631, "v22", 14, 1, 0}}, /* <reg: size 1, offset 14 in v22> */
	{"v22.b[15]", {632, "v22", 15, 1, 0}}, /* <reg: size 1, offset 15 in v22> */
	{"v23.b[0]", {633, "v23", 0, 1, 0}}, /* <reg: size 1, offset 0 in v23> */
	{"v23.b[1]", {634, "v23", 1, 1, 0}}, /* <reg: size 1, offset 1 in v23> */
	{"v23.b[2]", {635, "v23", 2, 1, 0}}, /* <reg: size 1, offset 2 in v23> */
	{"v23.b[3]", {636, "v23", 3, 1, 0}}, /* <reg: size 1, offset 3 in v23> */
	{"v23.b[4]", {637, "v23", 4, 1, 0}}, /* <reg: size 1, offset 4 in v23> */
	{"v23.b[5]", {638, "v23", 5, 1, 0}}, /* <reg: size 1, offset 5 in v23> */
	{"v23.b[6]", {639, "v23", 6, 1, 0}}, /* <reg: size 1, offset 6 in v23> */
	{"v23.b[7]", {640, "v23", 7, 1, 0}}, /* <reg: size 1, offset 7 in v23> */
	{"v23.b[8]", {641, "v23", 8, 1, 0}}, /* <reg: size 1, offset 8 in v23> */
	{"v23.b[9]", {642, "v23", 9, 1, 0}}, /* <reg: size 1, offset 9 in v23> */
	{"v23.b[10]", {643, "v23", 10, 1, 0}}, /* <reg: size 1, offset 10 in v23> */
	{"v23.b[11]", {644, "v23", 11, 1, 0}}, /* <reg: size 1, offset 11 in v23> */
	{"v23.b[12]", {645, "v23", 12, 1, 0}}, /* <reg: size 1, offset 12 in v23> */
	{"v23.b[13]", {646, "v23", 13, 1, 0}}, /* <reg: size 1, offset 13 in v23> */
	{"v23.b[14]", {647, "v23", 14, 1, 0}}, /* <reg: size 1, offset 14 in v23> */
	{"v23.b[15]", {648, "v23", 15, 1, 0}}, /* <reg: size 1, offset 15 in v23> */
	{"v24.b[0]", {649, "v24", 0, 1, 0}}, /* <reg: size 1, offset 0 in v24> */
	{"v24.b[1]", {650, "v24", 1, 1, 0}}, /* <reg: size 1, offset 1 in v24> */
	{"v24.b[2]", {651, "v24", 2, 1, 0}}, /* <reg: size 1, offset 2 in v24> */
	{"v24.b[3]", {652, "v24", 3, 1, 0}}, /* <reg: size 1, offset 3 in v24> */
	{"v24.b[4]", {653, "v24", 4, 1, 0}}, /* <reg: size 1, offset 4 in v24> */
	{"v24.b[5]", {654, "v24", 5, 1, 0}}, /* <reg: size 1, offset 5 in v24> */
	{"v24.b[6]", {655, "v24", 6, 1, 0}}, /* <reg: size 1, offset 6 in v24> */
	{"v24.b[7]", {656, "v24", 7, 1, 0}}, /* <reg: size 1, offset 7 in v24> */
	{"v24.b[8]", {657, "v24", 8, 1, 0}}, /* <reg: size 1, offset 8 in v24> */
	{"v24.b[9]", {658, "v24", 9, 1, 0}}, /* <reg: size 1, offset 9 in v24> */
	{"v24.b[10]", {659, "v24", 10, 1, 0}}, /* <reg: size 1, offset 10 in v24> */
	{"v24.b[11]", {660, "v24", 11, 1, 0}}, /* <reg: size 1, offset 11 in v24> */
	{"v24.b[12]", {661, "v24", 12, 1, 0}}, /* <reg: size 1, offset 12 in v24> */
	{"v24.b[13]", {662, "v24", 13, 1, 0}}, /* <reg: size 1, offset 13 in v24> */
	{"v24.b[14]", {663, "v24", 14, 1, 0}}, /* <reg: size 1, offset 14 in v24> */
	{"v24.b[15]", {664, "v24", 15, 1, 0}}, /* <reg: size 1, offset 15 in v24> */
	{"v25.b[0]", {665, "v25", 0, 1, 0}}, /* <reg: size 1, offset 0 in v25> */
	{"v25.b[1]", {666, "v25", 1, 1, 0}}, /* <reg: size 1, offset 1 in v25> */
	{"v25.b[2]", {667, "v25", 2, 1, 0}}, /* <reg: size 1, offset 2 in v25> */
	{"v25.b[3]", {668, "v25", 3, 1, 0}}, /* <reg: size 1, offset 3 in v25> */
	{"v25.b[4]", {669, "v25", 4, 1, 0}}, /* <reg: size 1, offset 4 in v25> */
	{"v25.b[5]", {670, "v25", 5, 1, 0}}, /* <reg: size 1, offset 5 in v25> */
	{"v25.b[6]", {671, "v25", 6, 1, 0}}, /* <reg: size 1, offset 6 in v25> */
	{"v25.b[7]", {672, "v25", 7, 1, 0}}, /* <reg: size 1, offset 7 in v25> */
	{"v25.b[8]", {673, "v25", 8, 1, 0}}, /* <reg: size 1, offset 8 in v25> */
	{"v25.b[9]", {674, "v25", 9, 1, 0}}, /* <reg: size 1, offset 9 in v25> */
	{"v25.b[10]", {675, "v25", 10, 1, 0}}, /* <reg: size 1, offset 10 in v25> */
	{"v25.b[11]", {676, "v25", 11, 1, 0}}, /* <reg: size 1, offset 11 in v25> */
	{"v25.b[12]", {677, "v25", 12, 1, 0}}, /* <reg: size 1, offset 12 in v25> */
	{"v25.b[13]", {678, "v25", 13, 1, 0}}, /* <reg: size 1, offset 13 in v25> */
	{"v25.b[14]", {679, "v25", 14, 1, 0}}, /* <reg: size 1, offset 14 in v25> */
	{"v25.b[15]", {680, "v25", 15, 1, 0}}, /* <reg: size 1, offset 15 in v25> */
	{"v26.b[0]", {681, "v26", 0, 1, 0}}, /* <reg: size 1, offset 0 in v26> */
	{"v26.b[1]", {682, "v26", 1, 1, 0}}, /* <reg: size 1, offset 1 in v26> */
	{"v26.b[2]", {683, "v26", 2, 1, 0}}, /* <reg: size 1, offset 2 in v26> */
	{"v26.b[3]", {684, "v26", 3, 1, 0}}, /* <reg: size 1, offset 3 in v26> */
	{"v26.b[4]", {685, "v26", 4, 1, 0}}, /* <reg: size 1, offset 4 in v26> */
	{"v26.b[5]", {686, "v26", 5, 1, 0}}, /* <reg: size 1, offset 5 in v26> */
	{"v26.b[6]", {687, "v26", 6, 1, 0}}, /* <reg: size 1, offset 6 in v26> */
	{"v26.b[7]", {688, "v26", 7, 1, 0}}, /* <reg: size 1, offset 7 in v26> */
	{"v26.b[8]", {689, "v26", 8, 1, 0}}, /* <reg: size 1, offset 8 in v26> */
	{"v26.b[9]", {690, "v26", 9, 1, 0}}, /* <reg: size 1, offset 9 in v26> */
	{"v26.b[10]", {691, "v26", 10, 1, 0}}, /* <reg: size 1, offset 10 in v26> */
	{"v26.b[11]", {692, "v26", 11, 1, 0}}, /* <reg: size 1, offset 11 in v26> */
	{"v26.b[12]", {693, "v26", 12, 1, 0}}, /* <reg: size 1, offset 12 in v26> */
	{"v26.b[13]", {694, "v26", 13, 1, 0}}, /* <reg: size 1, offset 13 in v26> */
	{"v26.b[14]", {695, "v26", 14, 1, 0}}, /* <reg: size 1, offset 14 in v26> */
	{"v26.b[15]", {696, "v26", 15, 1, 0}}, /* <reg: size 1, offset 15 in v26> */
	{"v27.b[0]", {697, "v27", 0, 1, 0}}, /* <reg: size 1, offset 0 in v27> */
	{"v27.b[1]", {698, "v27", 1, 1, 0}}, /* <reg: size 1, offset 1 in v27> */
	{"v27.b[2]", {699, "v27", 2, 1, 0}}, /* <reg: size 1, offset 2 in v27> */
	{"v27.b[3]", {700, "v27", 3, 1, 0}}, /* <reg: size 1, offset 3 in v27> */
	{"v27.b[4]", {701, "v27", 4, 1, 0}}, /* <reg: size 1, offset 4 in v27> */
	{"v27.b[5]", {702, "v27", 5, 1, 0}}, /* <reg: size 1, offset 5 in v27> */
	{"v27.b[6]", {703, "v27", 6, 1, 0}}, /* <reg: size 1, offset 6 in v27> */
	{"v27.b[7]", {704, "v27", 7, 1, 0}}, /* <reg: size 1, offset 7 in v27> */
	{"v27.b[8]", {705, "v27", 8, 1, 0}}, /* <reg: size 1, offset 8 in v27> */
	{"v27.b[9]", {706, "v27", 9, 1, 0}}, /* <reg: size 1, offset 9 in v27> */
	{"v27.b[10]", {707, "v27", 10, 1, 0}}, /* <reg: size 1, offset 10 in v27> */
	{"v27.b[11]", {708, "v27", 11, 1, 0}}, /* <reg: size 1, offset 11 in v27> */
	{"v27.b[12]", {709, "v27", 12, 1, 0}}, /* <reg: size 1, offset 12 in v27> */
	{"v27.b[13]", {710, "v27", 13, 1, 0}}, /* <reg: size 1, offset 13 in v27> */
	{"v27.b[14]", {711, "v27", 14, 1, 0}}, /* <reg: size 1, offset 14 in v27> */
	{"v27.b[15]", {712, "v27", 15, 1, 0}}, /* <reg: size 1, offset 15 in v27> */
	{"v28.b[0]", {713, "v28", 0, 1, 0}}, /* <reg: size 1, offset 0 in v28> */
	{"v28.b[1]", {714, "v28", 1, 1, 0}}, /* <reg: size 1, offset 1 in v28> */
	{"v28.b[2]", {715, "v28", 2, 1, 0}}, /* <reg: size 1, offset 2 in v28> */
	{"v28.b[3]", {716, "v28", 3, 1, 0}}, /* <reg: size 1, offset 3 in v28> */
	{"v28.b[4]", {717, "v28", 4, 1, 0}}, /* <reg: size 1, offset 4 in v28> */
	{"v28.b[5]", {718, "v28", 5, 1, 0}}, /* <reg: size 1, offset 5 in v28> */
	{"v28.b[6]", {719, "v28", 6, 1, 0}}, /* <reg: size 1, offset 6 in v28> */
	{"v28.b[7]", {720, "v28", 7, 1, 0}}, /* <reg: size 1, offset 7 in v28> */
	{"v28.b[8]", {721, "v28", 8, 1, 0}}, /* <reg: size 1, offset 8 in v28> */
	{"v28.b[9]", {722, "v28", 9, 1, 0}}, /* <reg: size 1, offset 9 in v28> */
	{"v28.b[10]", {723, "v28", 10, 1, 0}}, /* <reg: size 1, offset 10 in v28> */
	{"v28.b[11]", {724, "v28", 11, 1, 0}}, /* <reg: size 1, offset 11 in v28> */
	{"v28.b[12]", {725, "v28", 12, 1, 0}}, /* <reg: size 1, offset 12 in v28> */
	{"v28.b[13]", {726, "v28", 13, 1, 0}}, /* <reg: size 1, offset 13 in v28> */
	{"v28.b[14]", {727, "v28", 14, 1, 0}}, /* <reg: size 1, offset 14 in v28> */
	{"v28.b[15]", {728, "v28", 15, 1, 0}}, /* <reg: size 1, offset 15 in v28> */
	{"v29.b[0]", {729, "v29", 0, 1, 0}}, /* <reg: size 1, offset 0 in v29> */
	{"v29.b[1]", {730, "v29", 1, 1, 0}}, /* <reg: size 1, offset 1 in v29> */
	{"v29.b[2]", {731, "v29", 2, 1, 0}}, /* <reg: size 1, offset 2 in v29> */
	{"v29.b[3]", {732, "v29", 3, 1, 0}}, /* <reg: size 1, offset 3 in v29> */
	{"v29.b[4]", {733, "v29", 4, 1, 0}}, /* <reg: size 1, offset 4 in v29> */
	{"v29.b[5]", {734, "v29", 5, 1, 0}}, /* <reg: size 1, offset 5 in v29> */
	{"v29.b[6]", {735, "v29", 6, 1, 0}}, /* <reg: size 1, offset 6 in v29> */
	{"v29.b[7]", {736, "v29", 7, 1, 0}}, /* <reg: size 1, offset 7 in v29> */
	{"v29.b[8]", {737, "v29", 8, 1, 0}}, /* <reg: size 1, offset 8 in v29> */
	{"v29.b[9]", {738, "v29", 9, 1, 0}}, /* <reg: size 1, offset 9 in v29> */
	{"v29.b[10]", {739, "v29", 10, 1, 0}}, /* <reg: size 1, offset 10 in v29> */
	{"v29.b[11]", {740, "v29", 11, 1, 0}}, /* <reg: size 1, offset 11 in v29> */
	{"v29.b[12]", {741, "v29", 12, 1, 0}}, /* <reg: size 1, offset 12 in v29> */
	{"v29.b[13]", {742, "v29", 13, 1, 0}}, /* <reg: size 1, offset 13 in v29> */
	{"v29.b[14]", {743, "v29", 14, 1, 0}}, /* <reg: size 1, offset 14 in v29> */
	{"v29.b[15]", {744, "v29", 15, 1, 0}}, /* <reg: size 1, offset 15 in v29> */
	{"v30.b[0]", {745, "v30", 0, 1, 0}}, /* <reg: size 1, offset 0 in v30> */
	{"v30.b[1]", {746, "v30", 1, 1, 0}}, /* <reg: size 1, offset 1 in v30> */
	{"v30.b[2]", {747, "v30", 2, 1, 0}}, /* <reg: size 1, offset 2 in v30> */
	{"v30.b[3]", {748, "v30", 3, 1, 0}}, /* <reg: size 1, offset 3 in v30> */
	{"v30.b[4]", {749, "v30", 4, 1, 0}}, /* <reg: size 1, offset 4 in v30> */
	{"v30.b[5]", {750, "v30", 5, 1, 0}}, /* <reg: size 1, offset 5 in v30> */
	{"v30.b[6]", {751, "v30", 6, 1, 0}}, /* <reg: size 1, offset 6 in v30> */
	{"v30.b[7]", {752, "v30", 7, 1, 0}}, /* <reg: size 1, offset 7 in v30> */
	{"v30.b[8]", {753, "v30", 8, 1, 0}}, /* <reg: size 1, offset 8 in v30> */
	{"v30.b[9]", {754, "v30", 9, 1, 0}}, /* <reg: size 1, offset 9 in v30> */
	{"v30.b[10]", {755, "v30", 10, 1, 0}}, /* <reg: size 1, offset 10 in v30> */
	{"v30.b[11]", {756, "v30", 11, 1, 0}}, /* <reg: size 1, offset 11 in v30> */
	{"v30.b[12]", {757, "v30", 12, 1, 0}}, /* <reg: size 1, offset 12 in v30> */
	{"v30.b[13]", {758, "v30", 13, 1, 0}}, /* <reg: size 1, offset 13 in v30> */
	{"v30.b[14]", {759, "v30", 14, 1, 0}}, /* <reg: size 1, offset 14 in v30> */
	{"v30.b[15]", {760, "v30", 15, 1, 0}}, /* <reg: size 1, offset 15 in v30> */
	{"v31.b[0]", {761, "v31", 0, 1, 0}}, /* <reg: size 1, offset 0 in v31> */
	{"v31.b[1]", {762, "v31", 1, 1, 0}}, /* <reg: size 1, offset 1 in v31> */
	{"v31.b[2]", {763, "v31", 2, 1, 0}}, /* <reg: size 1, offset 2 in v31> */
	{"v31.b[3]", {764, "v31", 3, 1, 0}}, /* <reg: size 1, offset 3 in v31> */
	{"v31.b[4]", {765, "v31", 4, 1, 0}}, /* <reg: size 1, offset 4 in v31> */
	{"v31.b[5]", {766, "v31", 5, 1, 0}}, /* <reg: size 1, offset 5 in v31> */
	{"v31.b[6]", {767, "v31", 6, 1, 0}}, /* <reg: size 1, offset 6 in v31> */
	{"v31.b[7]", {768, "v31", 7, 1, 0}}, /* <reg: size 1, offset 7 in v31> */
	{"v31.b[8]", {769, "v31", 8, 1, 0}}, /* <reg: size 1, offset 8 in v31> */
	{"v31.b[9]", {770, "v31", 9, 1, 0}}, /* <reg: size 1, offset 9 in v31> */
	{"v31.b[10]", {771, "v31", 10, 1, 0}}, /* <reg: size 1, offset 10 in v31> */
	{"v31.b[11]", {772, "v31", 11, 1, 0}}, /* <reg: size 1, offset 11 in v31> */
	{"v31.b[12]", {773, "v31", 12, 1, 0}}, /* <reg: size 1, offset 12 in v31> */
	{"v31.b[13]", {774, "v31", 13, 1, 0}}, /* <reg: size 1, offset 13 in v31> */
	{"v31.b[14]", {775, "v31", 14, 1, 0}}, /* <reg: size 1, offset 14 in v31> */
	{"v31.b[15]", {776, "v31", 15, 1, 0}}, /* <reg: size 1, offset 15 in v31> */
	{"v0.h[0]", {777, "v0", 0, 2, 0}}, /* <reg: size 2, offset 0 in v0> */
	{"v0.h[1]", {778, "v0", 2, 2, 0}}, /* <reg: size 2, offset 2 in v0> */
	{"v0.h[2]", {779, "v0", 4, 2, 0}}, /* <reg: size 2, offset 4 in v0> */
	{"v0.h[3]", {780, "v0", 6, 2, 0}}, /* <reg: size 2, offset 6 in v0> */
	{"v0.h[4]", {781, "v0", 8, 2, 0}}, /* <reg: size 2, offset 8 in v0> */
	{"v0.h[5]", {782, "v0", 10, 2, 0}}, /* <reg: size 2, offset 10 in v0> */
	{"v0.h[6]", {783, "v0", 12, 2, 0}}, /* <reg: size 2, offset 12 in v0> */
	{"v0.h[7]", {784, "v0", 14, 2, 0}}, /* <reg: size 2, offset 14 in v0> */
	{"v1.h[0]", {785, "v1", 0, 2, 0}}, /* <reg: size 2, offset 0 in v1> */
	{"v1.h[1]", {786, "v1", 2, 2, 0}}, /* <reg: size 2, offset 2 in v1> */
	{"v1.h[2]", {787, "v1", 4, 2, 0}}, /* <reg: size 2, offset 4 in v1> */
	{"v1.h[3]", {788, "v1", 6, 2, 0}}, /* <reg: size 2, offset 6 in v1> */
	{"v1.h[4]", {789, "v1", 8, 2, 0}}, /* <reg: size 2, offset 8 in v1> */
	{"v1.h[5]", {790, "v1", 10, 2, 0}}, /* <reg: size 2, offset 10 in v1> */
	{"v1.h[6]", {791, "v1", 12, 2, 0}}, /* <reg: size 2, offset 12 in v1> */
	{"v1.h[7]", {792, "v1", 14, 2, 0}}, /* <reg: size 2, offset 14 in v1> */
	{"v2.h[0]", {793, "v2", 0, 2, 0}}, /* <reg: size 2, offset 0 in v2> */
	{"v2.h[1]", {794, "v2", 2, 2, 0}}, /* <reg: size 2, offset 2 in v2> */
	{"v2.h[2]", {795, "v2", 4, 2, 0}}, /* <reg: size 2, offset 4 in v2> */
	{"v2.h[3]", {796, "v2", 6, 2, 0}}, /* <reg: size 2, offset 6 in v2> */
	{"v2.h[4]", {797, "v2", 8, 2, 0}}, /* <reg: size 2, offset 8 in v2> */
	{"v2.h[5]", {798, "v2", 10, 2, 0}}, /* <reg: size 2, offset 10 in v2> */
	{"v2.h[6]", {799, "v2", 12, 2, 0}}, /* <reg: size 2, offset 12 in v2> */
	{"v2.h[7]", {800, "v2", 14, 2, 0}}, /* <reg: size 2, offset 14 in v2> */
	{"v3.h[0]", {801, "v3", 0, 2, 0}}, /* <reg: size 2, offset 0 in v3> */
	{"v3.h[1]", {802, "v3", 2, 2, 0}}, /* <reg: size 2, offset 2 in v3> */
	{"v3.h[2]", {803, "v3", 4, 2, 0}}, /* <reg: size 2, offset 4 in v3> */
	{"v3.h[3]", {804, "v3", 6, 2, 0}}, /* <reg: size 2, offset 6 in v3> */
	{"v3.h[4]", {805, "v3", 8, 2, 0}}, /* <reg: size 2, offset 8 in v3> */
	{"v3.h[5]", {806, "v3", 10, 2, 0}}, /* <reg: size 2, offset 10 in v3> */
	{"v3.h[6]", {807, "v3", 12, 2, 0}}, /* <reg: size 2, offset 12 in v3> */
	{"v3.h[7]", {808, "v3", 14, 2, 0}}, /* <reg: size 2, offset 14 in v3> */
	{"v4.h[0]", {809, "v4", 0, 2, 0}}, /* <reg: size 2, offset 0 in v4> */
	{"v4.h[1]", {810, "v4", 2, 2, 0}}, /* <reg: size 2, offset 2 in v4> */
	{"v4.h[2]", {811, "v4", 4, 2, 0}}, /* <reg: size 2, offset 4 in v4> */
	{"v4.h[3]", {812, "v4", 6, 2, 0}}, /* <reg: size 2, offset 6 in v4> */
	{"v4.h[4]", {813, "v4", 8, 2, 0}}, /* <reg: size 2, offset 8 in v4> */
	{"v4.h[5]", {814, "v4", 10, 2, 0}}, /* <reg: size 2, offset 10 in v4> */
	{"v4.h[6]", {815, "v4", 12, 2, 0}}, /* <reg: size 2, offset 12 in v4> */
	{"v4.h[7]", {816, "v4", 14, 2, 0}}, /* <reg: size 2, offset 14 in v4> */
	{"v5.h[0]", {817, "v5", 0, 2, 0}}, /* <reg: size 2, offset 0 in v5> */
	{"v5.h[1]", {818, "v5", 2, 2, 0}}, /* <reg: size 2, offset 2 in v5> */
	{"v5.h[2]", {819, "v5", 4, 2, 0}}, /* <reg: size 2, offset 4 in v5> */
	{"v5.h[3]", {820, "v5", 6, 2, 0}}, /* <reg: size 2, offset 6 in v5> */
	{"v5.h[4]", {821, "v5", 8, 2, 0}}, /* <reg: size 2, offset 8 in v5> */
	{"v5.h[5]", {822, "v5", 10, 2, 0}}, /* <reg: size 2, offset 10 in v5> */
	{"v5.h[6]", {823, "v5", 12, 2, 0}}, /* <reg: size 2, offset 12 in v5> */
	{"v5.h[7]", {824, "v5", 14, 2, 0}}, /* <reg: size 2, offset 14 in v5> */
	{"v6.h[0]", {825, "v6", 0, 2, 0}}, /* <reg: size 2, offset 0 in v6> */
	{"v6.h[1]", {826, "v6", 2, 2, 0}}, /* <reg: size 2, offset 2 in v6> */
	{"v6.h[2]", {827, "v6", 4, 2, 0}}, /* <reg: size 2, offset 4 in v6> */
	{"v6.h[3]", {828, "v6", 6, 2, 0}}, /* <reg: size 2, offset 6 in v6> */
	{"v6.h[4]", {829, "v6", 8, 2, 0}}, /* <reg: size 2, offset 8 in v6> */
	{"v6.h[5]", {830, "v6", 10, 2, 0}}, /* <reg: size 2, offset 10 in v6> */
	{"v6.h[6]", {831, "v6", 12, 2, 0}}, /* <reg: size 2, offset 12 in v6> */
	{"v6.h[7]", {832, "v6", 14, 2, 0}}, /* <reg: size 2, offset 14 in v6> */
	{"v7.h[0]", {833, "v7", 0, 2, 0}}, /* <reg: size 2, offset 0 in v7> */
	{"v7.h[1]", {834, "v7", 2, 2, 0}}, /* <reg: size 2, offset 2 in v7> */
	{"v7.h[2]", {835, "v7", 4, 2, 0}}, /* <reg: size 2, offset 4 in v7> */
	{"v7.h[3]", {836, "v7", 6, 2, 0}}, /* <reg: size 2, offset 6 in v7> */
	{"v7.h[4]", {837, "v7", 8, 2, 0}}, /* <reg: size 2, offset 8 in v7> */
	{"v7.h[5]", {838, "v7", 10, 2, 0}}, /* <reg: size 2, offset 10 in v7> */
	{"v7.h[6]", {839, "v7", 12, 2, 0}}, /* <reg: size 2, offset 12 in v7> */
	{"v7.h[7]", {840, "v7", 14, 2, 0}}, /* <reg: size 2, offset 14 in v7> */
	{"v8.h[0]", {841, "v8", 0, 2, 0}}, /* <reg: size 2, offset 0 in v8> */
	{"v8.h[1]", {842, "v8", 2, 2, 0}}, /* <reg: size 2, offset 2 in v8> */
	{"v8.h[2]", {843, "v8", 4, 2, 0}}, /* <reg: size 2, offset 4 in v8> */
	{"v8.h[3]", {844, "v8", 6, 2, 0}}, /* <reg: size 2, offset 6 in v8> */
	{"v8.h[4]", {845, "v8", 8, 2, 0}}, /* <reg: size 2, offset 8 in v8> */
	{"v8.h[5]", {846, "v8", 10, 2, 0}}, /* <reg: size 2, offset 10 in v8> */
	{"v8.h[6]", {847, "v8", 12, 2, 0}}, /* <reg: size 2, offset 12 in v8> */
	{"v8.h[7]", {848, "v8", 14, 2, 0}}, /* <reg: size 2, offset 14 in v8> */
	{"v9.h[0]", {849, "v9", 0, 2, 0}}, /* <reg: size 2, offset 0 in v9> */
	{"v9.h[1]", {850, "v9", 2, 2, 0}}, /* <reg: size 2, offset 2 in v9> */
	{"v9.h[2]", {851, "v9", 4, 2, 0}}, /* <reg: size 2, offset 4 in v9> */
	{"v9.h[3]", {852, "v9", 6, 2, 0}}, /* <reg: size 2, offset 6 in v9> */
	{"v9.h[4]", {853, "v9", 8, 2, 0}}, /* <reg: size 2, offset 8 in v9> */
	{"v9.h[5]", {854, "v9", 10, 2, 0}}, /* <reg: size 2, offset 10 in v9> */
	{"v9.h[6]", {855, "v9", 12, 2, 0}}, /* <reg: size 2, offset 12 in v9> */
	{"v9.h[7]", {856, "v9", 14, 2, 0}}, /* <reg: size 2, offset 14 in v9> */
	{"v10.h[0]", {857, "v10", 0, 2, 0}}, /* <reg: size 2, offset 0 in v10> */
	{"v10.h[1]", {858, "v10", 2, 2, 0}}, /* <reg: size 2, offset 2 in v10> */
	{"v10.h[2]", {859, "v10", 4, 2, 0}}, /* <reg: size 2, offset 4 in v10> */
	{"v10.h[3]", {860, "v10", 6, 2, 0}}, /* <reg: size 2, offset 6 in v10> */
	{"v10.h[4]", {861, "v10", 8, 2, 0}}, /* <reg: size 2, offset 8 in v10> */
	{"v10.h[5]", {862, "v10", 10, 2, 0}}, /* <reg: size 2, offset 10 in v10> */
	{"v10.h[6]", {863, "v10", 12, 2, 0}}, /* <reg: size 2, offset 12 in v10> */
	{"v10.h[7]", {864, "v10", 14, 2, 0}}, /* <reg: size 2, offset 14 in v10> */
	{"v11.h[0]", {865, "v11", 0, 2, 0}}, /* <reg: size 2, offset 0 in v11> */
	{"v11.h[1]", {866, "v11", 2, 2, 0}}, /* <reg: size 2, offset 2 in v11> */
	{"v11.h[2]", {867, "v11", 4, 2, 0}}, /* <reg: size 2, offset 4 in v11> */
	{"v11.h[3]", {868, "v11", 6, 2, 0}}, /* <reg: size 2, offset 6 in v11> */
	{"v11.h[4]", {869, "v11", 8, 2, 0}}, /* <reg: size 2, offset 8 in v11> */
	{"v11.h[5]", {870, "v11", 10, 2, 0}}, /* <reg: size 2, offset 10 in v11> */
	{"v11.h[6]", {871, "v11", 12, 2, 0}}, /* <reg: size 2, offset 12 in v11> */
	{"v11.h[7]", {872, "v11", 14, 2, 0}}, /* <reg: size 2, offset 14 in v11> */
	{"v12.h[0]", {873, "v12", 0, 2, 0}}, /* <reg: size 2, offset 0 in v12> */
	{"v12.h[1]", {874, "v12", 2, 2, 0}}, /* <reg: size 2, offset 2 in v12> */
	{"v12.h[2]", {875, "v12", 4, 2, 0}}, /* <reg: size 2, offset 4 in v12> */
	{"v12.h[3]", {876, "v12", 6, 2, 0}}, /* <reg: size 2, offset 6 in v12> */
	{"v12.h[4]", {877, "v12", 8, 2, 0}}, /* <reg: size 2, offset 8 in v12> */
	{"v12.h[5]", {878, "v12", 10, 2, 0}}, /* <reg: size 2, offset 10 in v12> */
	{"v12.h[6]", {879, "v12", 12, 2, 0}}, /* <reg: size 2, offset 12 in v12> */
	{"v12.h[7]", {880, "v12", 14, 2, 0}}, /* <reg: size 2, offset 14 in v12> */
	{"v13.h[0]", {881, "v13", 0, 2, 0}}, /* <reg: size 2, offset 0 in v13> */
	{"v13.h[1]", {882, "v13", 2, 2, 0}}, /* <reg: size 2, offset 2 in v13> */
	{"v13.h[2]", {883, "v13", 4, 2, 0}}, /* <reg: size 2, offset 4 in v13> */
	{"v13.h[3]", {884, "v13", 6, 2, 0}}, /* <reg: size 2, offset 6 in v13> */
	{"v13.h[4]", {885, "v13", 8, 2, 0}}, /* <reg: size 2, offset 8 in v13> */
	{"v13.h[5]", {886, "v13", 10, 2, 0}}, /* <reg: size 2, offset 10 in v13> */
	{"v13.h[6]", {887, "v13", 12, 2, 0}}, /* <reg: size 2, offset 12 in v13> */
	{"v13.h[7]", {888, "v13", 14, 2, 0}}, /* <reg: size 2, offset 14 in v13> */
	{"v14.h[0]", {889, "v14", 0, 2, 0}}, /* <reg: size 2, offset 0 in v14> */
	{"v14.h[1]", {890, "v14", 2, 2, 0}}, /* <reg: size 2, offset 2 in v14> */
	{"v14.h[2]", {891, "v14", 4, 2, 0}}, /* <reg: size 2, offset 4 in v14> */
	{"v14.h[3]", {892, "v14", 6, 2, 0}}, /* <reg: size 2, offset 6 in v14> */
	{"v14.h[4]", {893, "v14", 8, 2, 0}}, /* <reg: size 2, offset 8 in v14> */
	{"v14.h[5]", {894, "v14", 10, 2, 0}}, /* <reg: size 2, offset 10 in v14> */
	{"v14.h[6]", {895, "v14", 12, 2, 0}}, /* <reg: size 2, offset 12 in v14> */
	{"v14.h[7]", {896, "v14", 14, 2, 0}}, /* <reg: size 2, offset 14 in v14> */
	{"v15.h[0]", {897, "v15", 0, 2, 0}}, /* <reg: size 2, offset 0 in v15> */
	{"v15.h[1]", {898, "v15", 2, 2, 0}}, /* <reg: size 2, offset 2 in v15> */
	{"v15.h[2]", {899, "v15", 4, 2, 0}}, /* <reg: size 2, offset 4 in v15> */
	{"v15.h[3]", {900, "v15", 6, 2, 0}}, /* <reg: size 2, offset 6 in v15> */
	{"v15.h[4]", {901, "v15", 8, 2, 0}}, /* <reg: size 2, offset 8 in v15> */
	{"v15.h[5]", {902, "v15", 10, 2, 0}}, /* <reg: size 2, offset 10 in v15> */
	{"v15.h[6]", {903, "v15", 12, 2, 0}}, /* <reg: size 2, offset 12 in v15> */
	{"v15.h[7]", {904, "v15", 14, 2, 0}}, /* <reg: size 2, offset 14 in v15> */
	{"v16.h[0]", {905, "v16", 0, 2, 0}}, /* <reg: size 2, offset 0 in v16> */
	{"v16.h[1]", {906, "v16", 2, 2, 0}}, /* <reg: size 2, offset 2 in v16> */
	{"v16.h[2]", {907, "v16", 4, 2, 0}}, /* <reg: size 2, offset 4 in v16> */
	{"v16.h[3]", {908, "v16", 6, 2, 0}}, /* <reg: size 2, offset 6 in v16> */
	{"v16.h[4]", {909, "v16", 8, 2, 0}}, /* <reg: size 2, offset 8 in v16> */
	{"v16.h[5]", {910, "v16", 10, 2, 0}}, /* <reg: size 2, offset 10 in v16> */
	{"v16.h[6]", {911, "v16", 12, 2, 0}}, /* <reg: size 2, offset 12 in v16> */
	{"v16.h[7]", {912, "v16", 14, 2, 0}}, /* <reg: size 2, offset 14 in v16> */
	{"v17.h[0]", {913, "v17", 0, 2, 0}}, /* <reg: size 2, offset 0 in v17> */
	{"v17.h[1]", {914, "v17", 2, 2, 0}}, /* <reg: size 2, offset 2 in v17> */
	{"v17.h[2]", {915, "v17", 4, 2, 0}}, /* <reg: size 2, offset 4 in v17> */
	{"v17.h[3]", {916, "v17", 6, 2, 0}}, /* <reg: size 2, offset 6 in v17> */
	{"v17.h[4]", {917, "v17", 8, 2, 0}}, /* <reg: size 2, offset 8 in v17> */
	{"v17.h[5]", {918, "v17", 10, 2, 0}}, /* <reg: size 2, offset 10 in v17> */
	{"v17.h[6]", {919, "v17", 12, 2, 0}}, /* <reg: size 2, offset 12 in v17> */
	{"v17.h[7]", {920, "v17", 14, 2, 0}}, /* <reg: size 2, offset 14 in v17> */
	{"v18.h[0]", {921, "v18", 0, 2, 0}}, /* <reg: size 2, offset 0 in v18> */
	{"v18.h[1]", {922, "v18", 2, 2, 0}}, /* <reg: size 2, offset 2 in v18> */
	{"v18.h[2]", {923, "v18", 4, 2, 0}}, /* <reg: size 2, offset 4 in v18> */
	{"v18.h[3]", {924, "v18", 6, 2, 0}}, /* <reg: size 2, offset 6 in v18> */
	{"v18.h[4]", {925, "v18", 8, 2, 0}}, /* <reg: size 2, offset 8 in v18> */
	{"v18.h[5]", {926, "v18", 10, 2, 0}}, /* <reg: size 2, offset 10 in v18> */
	{"v18.h[6]", {927, "v18", 12, 2, 0}}, /* <reg: size 2, offset 12 in v18> */
	{"v18.h[7]", {928, "v18", 14, 2, 0}}, /* <reg: size 2, offset 14 in v18> */
	{"v19.h[0]", {929, "v19", 0, 2, 0}}, /* <reg: size 2, offset 0 in v19> */
	{"v19.h[1]", {930, "v19", 2, 2, 0}}, /* <reg: size 2, offset 2 in v19> */
	{"v19.h[2]", {931, "v19", 4, 2, 0}}, /* <reg: size 2, offset 4 in v19> */
	{"v19.h[3]", {932, "v19", 6, 2, 0}}, /* <reg: size 2, offset 6 in v19> */
	{"v19.h[4]", {933, "v19", 8, 2, 0}}, /* <reg: size 2, offset 8 in v19> */
	{"v19.h[5]", {934, "v19", 10, 2, 0}}, /* <reg: size 2, offset 10 in v19> */
	{"v19.h[6]", {935, "v19", 12, 2, 0}}, /* <reg: size 2, offset 12 in v19> */
	{"v19.h[7]", {936, "v19", 14, 2, 0}}, /* <reg: size 2, offset 14 in v19> */
	{"v20.h[0]", {937, "v20", 0, 2, 0}}, /* <reg: size 2, offset 0 in v20> */
	{"v20.h[1]", {938, "v20", 2, 2, 0}}, /* <reg: size 2, offset 2 in v20> */
	{"v20.h[2]", {939, "v20", 4, 2, 0}}, /* <reg: size 2, offset 4 in v20> */
	{"v20.h[3]", {940, "v20", 6, 2, 0}}, /* <reg: size 2, offset 6 in v20> */
	{"v20.h[4]", {941, "v20", 8, 2, 0}}, /* <reg: size 2, offset 8 in v20> */
	{"v20.h[5]", {942, "v20", 10, 2, 0}}, /* <reg: size 2, offset 10 in v20> */
	{"v20.h[6]", {943, "v20", 12, 2, 0}}, /* <reg: size 2, offset 12 in v20> */
	{"v20.h[7]", {944, "v20", 14, 2, 0}}, /* <reg: size 2, offset 14 in v20> */
	{"v21.h[0]", {945, "v21", 0, 2, 0}}, /* <reg: size 2, offset 0 in v21> */
	{"v21.h[1]", {946, "v21", 2, 2, 0}}, /* <reg: size 2, offset 2 in v21> */
	{"v21.h[2]", {947, "v21", 4, 2, 0}}, /* <reg: size 2, offset 4 in v21> */
	{"v21.h[3]", {948, "v21", 6, 2, 0}}, /* <reg: size 2, offset 6 in v21> */
	{"v21.h[4]", {949, "v21", 8, 2, 0}}, /* <reg: size 2, offset 8 in v21> */
	{"v21.h[5]", {950, "v21", 10, 2, 0}}, /* <reg: size 2, offset 10 in v21> */
	{"v21.h[6]", {951, "v21", 12, 2, 0}}, /* <reg: size 2, offset 12 in v21> */
	{"v21.h[7]", {952, "v21", 14, 2, 0}}, /* <reg: size 2, offset 14 in v21> */
	{"v22.h[0]", {953, "v22", 0, 2, 0}}, /* <reg: size 2, offset 0 in v22> */
	{"v22.h[1]", {954, "v22", 2, 2, 0}}, /* <reg: size 2, offset 2 in v22> */
	{"v22.h[2]", {955, "v22", 4, 2, 0}}, /* <reg: size 2, offset 4 in v22> */
	{"v22.h[3]", {956, "v22", 6, 2, 0}}, /* <reg: size 2, offset 6 in v22> */
	{"v22.h[4]", {957, "v22", 8, 2, 0}}, /* <reg: size 2, offset 8 in v22> */
	{"v22.h[5]", {958, "v22", 10, 2, 0}}, /* <reg: size 2, offset 10 in v22> */
	{"v22.h[6]", {959, "v22", 12, 2, 0}}, /* <reg: size 2, offset 12 in v22> */
	{"v22.h[7]", {960, "v22", 14, 2, 0}}, /* <reg: size 2, offset 14 in v22> */
	{"v23.h[0]", {961, "v23", 0, 2, 0}}, /* <reg: size 2, offset 0 in v23> */
	{"v23.h[1]", {962, "v23", 2, 2, 0}}, /* <reg: size 2, offset 2 in v23> */
	{"v23.h[2]", {963, "v23", 4, 2, 0}}, /* <reg: size 2, offset 4 in v23> */
	{"v23.h[3]", {964, "v23", 6, 2, 0}}, /* <reg: size 2, offset 6 in v23> */
	{"v23.h[4]", {965, "v23", 8, 2, 0}}, /* <reg: size 2, offset 8 in v23> */
	{"v23.h[5]", {966, "v23", 10, 2, 0}}, /* <reg: size 2, offset 10 in v23> */
	{"v23.h[6]", {967, "v23", 12, 2, 0}}, /* <reg: size 2, offset 12 in v23> */
	{"v23.h[7]", {968, "v23", 14, 2, 0}}, /* <reg: size 2, offset 14 in v23> */
	{"v24.h[0]", {969, "v24", 0, 2, 0}}, /* <reg: size 2, offset 0 in v24> */
	{"v24.h[1]", {970, "v24", 2, 2, 0}}, /* <reg: size 2, offset 2 in v24> */
	{"v24.h[2]", {971, "v24", 4, 2, 0}}, /* <reg: size 2, offset 4 in v24> */
	{"v24.h[3]", {972, "v24", 6, 2, 0}}, /* <reg: size 2, offset 6 in v24> */
	{"v24.h[4]", {973, "v24", 8, 2, 0}}, /* <reg: size 2, offset 8 in v24> */
	{"v24.h[5]", {974, "v24", 10, 2, 0}}, /* <reg: size 2, offset 10 in v24> */
	{"v24.h[6]", {975, "v24", 12, 2, 0}}, /* <reg: size 2, offset 12 in v24> */
	{"v24.h[7]", {976, "v24", 14, 2, 0}}, /* <reg: size 2, offset 14 in v24> */
	{"v25.h[0]", {977, "v25", 0, 2, 0}}, /* <reg: size 2, offset 0 in v25> */
	{"v25.h[1]", {978, "v25", 2, 2, 0}}, /* <reg: size 2, offset 2 in v25> */
	{"v25.h[2]", {979, "v25", 4, 2, 0}}, /* <reg: size 2, offset 4 in v25> */
	{"v25.h[3]", {980, "v25", 6, 2, 0}}, /* <reg: size 2, offset 6 in v25> */
	{"v25.h[4]", {981, "v25", 8, 2, 0}}, /* <reg: size 2, offset 8 in v25> */
	{"v25.h[5]", {982, "v25", 10, 2, 0}}, /* <reg: size 2, offset 10 in v25> */
	{"v25.h[6]", {983, "v25", 12, 2, 0}}, /* <reg: size 2, offset 12 in v25> */
	{"v25.h[7]", {984, "v25", 14, 2, 0}}, /* <reg: size 2, offset 14 in v25> */
	{"v26.h[0]", {985, "v26", 0, 2, 0}}, /* <reg: size 2, offset 0 in v26> */
	{"v26.h[1]", {986, "v26", 2, 2, 0}}, /* <reg: size 2, offset 2 in v26> */
	{"v26.h[2]", {987, "v26", 4, 2, 0}}, /* <reg: size 2, offset 4 in v26> */
	{"v26.h[3]", {988, "v26", 6, 2, 0}}, /* <reg: size 2, offset 6 in v26> */
	{"v26.h[4]", {989, "v26", 8, 2, 0}}, /* <reg: size 2, offset 8 in v26> */
	{"v26.h[5]", {990, "v26", 10, 2, 0}}, /* <reg: size 2, offset 10 in v26> */
	{"v26.h[6]", {991, "v26", 12, 2, 0}}, /* <reg: size 2, offset 12 in v26> */
	{"v26.h[7]", {992, "v26", 14, 2, 0}}, /* <reg: size 2, offset 14 in v26> */
	{"v27.h[0]", {993, "v27", 0, 2, 0}}, /* <reg: size 2, offset 0 in v27> */
	{"v27.h[1]", {994, "v27", 2, 2, 0}}, /* <reg: size 2, offset 2 in v27> */
	{"v27.h[2]", {995, "v27", 4, 2, 0}}, /* <reg: size 2, offset 4 in v27> */
	{"v27.h[3]", {996, "v27", 6, 2, 0}}, /* <reg: size 2, offset 6 in v27> */
	{"v27.h[4]", {997, "v27", 8, 2, 0}}, /* <reg: size 2, offset 8 in v27> */
	{"v27.h[5]", {998, "v27", 10, 2, 0}}, /* <reg: size 2, offset 10 in v27> */
	{"v27.h[6]", {999, "v27", 12, 2, 0}}, /* <reg: size 2, offset 12 in v27> */
	{"v27.h[7]", {1000, "v27", 14, 2, 0}}, /* <reg: size 2, offset 14 in v27> */
	{"v28.h[0]", {1001, "v28", 0, 2, 0}}, /* <reg: size 2, offset 0 in v28> */
	{"v28.h[1]", {1002, "v28", 2, 2, 0}}, /* <reg: size 2, offset 2 in v28> */
	{"v28.h[2]", {1003, "v28", 4, 2, 0}}, /* <reg: size 2, offset 4 in v28> */
	{"v28.h[3]", {1004, "v28", 6, 2, 0}}, /* <reg: size 2, offset 6 in v28> */
	{"v28.h[4]", {1005, "v28", 8, 2, 0}}, /* <reg: size 2, offset 8 in v28> */
	{"v28.h[5]", {1006, "v28", 10, 2, 0}}, /* <reg: size 2, offset 10 in v28> */
	{"v28.h[6]", {1007, "v28", 12, 2, 0}}, /* <reg: size 2, offset 12 in v28> */
	{"v28.h[7]", {1008, "v28", 14, 2, 0}}, /* <reg: size 2, offset 14 in v28> */
	{"v29.h[0]", {1009, "v29", 0, 2, 0}}, /* <reg: size 2, offset 0 in v29> */
	{"v29.h[1]", {1010, "v29", 2, 2, 0}}, /* <reg: size 2, offset 2 in v29> */
	{"v29.h[2]", {1011, "v29", 4, 2, 0}}, /* <reg: size 2, offset 4 in v29> */
	{"v29.h[3]", {1012, "v29", 6, 2, 0}}, /* <reg: size 2, offset 6 in v29> */
	{"v29.h[4]", {1013, "v29", 8, 2, 0}}, /* <reg: size 2, offset 8 in v29> */
	{"v29.h[5]", {1014, "v29", 10, 2, 0}}, /* <reg: size 2, offset 10 in v29> */
	{"v29.h[6]", {1015, "v29", 12, 2, 0}}, /* <reg: size 2, offset 12 in v29> */
	{"v29.h[7]", {1016, "v29", 14, 2, 0}}, /* <reg: size 2, offset 14 in v29> */
	{"v30.h[0]", {1017, "v30", 0, 2, 0}}, /* <reg: size 2, offset 0 in v30> */
	{"v30.h[1]", {1018, "v30", 2, 2, 0}}, /* <reg: size 2, offset 2 in v30> */
	{"v30.h[2]", {1019, "v30", 4, 2, 0}}, /* <reg: size 2, offset 4 in v30> */
	{"v30.h[3]", {1020, "v30", 6, 2, 0}}, /* <reg: size 2, offset 6 in v30> */
	{"v30.h[4]", {1021, "v30", 8, 2, 0}}, /* <reg: size 2, offset 8 in v30> */
	{"v30.h[5]", {1022, "v30", 10, 2, 0}}, /* <reg: size 2, offset 10 in v30> */
	{"v30.h[6]", {1023, "v30", 12, 2, 0}}, /* <reg: size 2, offset 12 in v30> */
	{"v30.h[7]", {1024, "v30", 14, 2, 0}}, /* <reg: size 2, offset 14 in v30> */
	{"v31.h[0]", {1025, "v31", 0, 2, 0}}, /* <reg: size 2, offset 0 in v31> */
	{"v31.h[1]", {1026, "v31", 2, 2, 0}}, /* <reg: size 2, offset 2 in v31> */
	{"v31.h[2]", {1027, "v31", 4, 2, 0}}, /* <reg: size 2, offset 4 in v31> */
	{"v31.h[3]", {1028, "v31", 6, 2, 0}}, /* <reg: size 2, offset 6 in v31> */
	{"v31.h[4]", {1029, "v31", 8, 2, 0}}, /* <reg: size 2, offset 8 in v31> */
	{"v31.h[5]", {1030, "v31", 10, 2, 0}}, /* <reg: size 2, offset 10 in v31> */
	{"v31.h[6]", {1031, "v31", 12, 2, 0}}, /* <reg: size 2, offset 12 in v31> */
	{"v31.h[7]", {1032, "v31", 14, 2, 0}}, /* <reg: size 2, offset 14 in v31> */
	{"v0.s[0]", {1033, "v0", 0, 4, 0}}, /* <reg: size 4, offset 0 in v0> */
	{"v0.s[1]", {1034, "v0", 4, 4, 0}}, /* <reg: size 4, offset 4 in v0> */
	{"v0.s[2]", {1035, "v0", 8, 4, 0}}, /* <reg: size 4, offset 8 in v0> */
	{"v0.s[3]", {1036, "v0", 12, 4, 0}}, /* <reg: size 4, offset 12 in v0> */
	{"v1.s[0]", {1037, "v1", 0, 4, 0}}, /* <reg: size 4, offset 0 in v1> */
	{"v1.s[1]", {1038, "v1", 4, 4, 0}}, /* <reg: size 4, offset 4 in v1> */
	{"v1.s[2]", {1039, "v1", 8, 4, 0}}, /* <reg: size 4, offset 8 in v1> */
	{"v1.s[3]", {1040, "v1", 12, 4, 0}}, /* <reg: size 4, offset 12 in v1> */
	{"v2.s[0]", {1041, "v2", 0, 4, 0}}, /* <reg: size 4, offset 0 in v2> */
	{"v2.s[1]", {1042, "v2", 4, 4, 0}}, /* <reg: size 4, offset 4 in v2> */
	{"v2.s[2]", {1043, "v2", 8, 4, 0}}, /* <reg: size 4, offset 8 in v2> */
	{"v2.s[3]", {1044, "v2", 12, 4, 0}}, /* <reg: size 4, offset 12 in v2> */
	{"v3.s[0]", {1045, "v3", 0, 4, 0}}, /* <reg: size 4, offset 0 in v3> */
	{"v3.s[1]", {1046, "v3", 4, 4, 0}}, /* <reg: size 4, offset 4 in v3> */
	{"v3.s[2]", {1047, "v3", 8, 4, 0}}, /* <reg: size 4, offset 8 in v3> */
	{"v3.s[3]", {1048, "v3", 12, 4, 0}}, /* <reg: size 4, offset 12 in v3> */
	{"v4.s[0]", {1049, "v4", 0, 4, 0}}, /* <reg: size 4, offset 0 in v4> */
	{"v4.s[1]", {1050, "v4", 4, 4, 0}}, /* <reg: size 4, offset 4 in v4> */
	{"v4.s[2]", {1051, "v4", 8, 4, 0}}, /* <reg: size 4, offset 8 in v4> */
	{"v4.s[3]", {1052, "v4", 12, 4, 0}}, /* <reg: size 4, offset 12 in v4> */
	{"v5.s[0]", {1053, "v5", 0, 4, 0}}, /* <reg: size 4, offset 0 in v5> */
	{"v5.s[1]", {1054, "v5", 4, 4, 0}}, /* <reg: size 4, offset 4 in v5> */
	{"v5.s[2]", {1055, "v5", 8, 4, 0}}, /* <reg: size 4, offset 8 in v5> */
	{"v5.s[3]", {1056, "v5", 12, 4, 0}}, /* <reg: size 4, offset 12 in v5> */
	{"v6.s[0]", {1057, "v6", 0, 4, 0}}, /* <reg: size 4, offset 0 in v6> */
	{"v6.s[1]", {1058, "v6", 4, 4, 0}}, /* <reg: size 4, offset 4 in v6> */
	{"v6.s[2]", {1059, "v6", 8, 4, 0}}, /* <reg: size 4, offset 8 in v6> */
	{"v6.s[3]", {1060, "v6", 12, 4, 0}}, /* <reg: size 4, offset 12 in v6> */
	{"v7.s[0]", {1061, "v7", 0, 4, 0}}, /* <reg: size 4, offset 0 in v7> */
	{"v7.s[1]", {1062, "v7", 4, 4, 0}}, /* <reg: size 4, offset 4 in v7> */
	{"v7.s[2]", {1063, "v7", 8, 4, 0}}, /* <reg: size 4, offset 8 in v7> */
	{"v7.s[3]", {1064, "v7", 12, 4, 0}}, /* <reg: size 4, offset 12 in v7> */
	{"v8.s[0]", {1065, "v8", 0, 4, 0}}, /* <reg: size 4, offset 0 in v8> */
	{"v8.s[1]", {1066, "v8", 4, 4, 0}}, /* <reg: size 4, offset 4 in v8> */
	{"v8.s[2]", {1067, "v8", 8, 4, 0}}, /* <reg: size 4, offset 8 in v8> */
	{"v8.s[3]", {1068, "v8", 12, 4, 0}}, /* <reg: size 4, offset 12 in v8> */
	{"v9.s[0]", {1069, "v9", 0, 4, 0}}, /* <reg: size 4, offset 0 in v9> */
	{"v9.s[1]", {1070, "v9", 4, 4, 0}}, /* <reg: size 4, offset 4 in v9> */
	{"v9.s[2]", {1071, "v9", 8, 4, 0}}, /* <reg: size 4, offset 8 in v9> */
	{"v9.s[3]", {1072, "v9", 12, 4, 0}}, /* <reg: size 4, offset 12 in v9> */
	{"v10.s[0]", {1073, "v10", 0, 4, 0}}, /* <reg: size 4, offset 0 in v10> */
	{"v10.s[1]", {1074, "v10", 4, 4, 0}}, /* <reg: size 4, offset 4 in v10> */
	{"v10.s[2]", {1075, "v10", 8, 4, 0}}, /* <reg: size 4, offset 8 in v10> */
	{"v10.s[3]", {1076, "v10", 12, 4, 0}}, /* <reg: size 4, offset 12 in v10> */
	{"v11.s[0]", {1077, "v11", 0, 4, 0}}, /* <reg: size 4, offset 0 in v11> */
	{"v11.s[1]", {1078, "v11", 4, 4, 0}}, /* <reg: size 4, offset 4 in v11> */
	{"v11.s[2]", {1079, "v11", 8, 4, 0}}, /* <reg: size 4, offset 8 in v11> */
	{"v11.s[3]", {1080, "v11", 12, 4, 0}}, /* <reg: size 4, offset 12 in v11> */
	{"v12.s[0]", {1081, "v12", 0, 4, 0}}, /* <reg: size 4, offset 0 in v12> */
	{"v12.s[1]", {1082, "v12", 4, 4, 0}}, /* <reg: size 4, offset 4 in v12> */
	{"v12.s[2]", {1083, "v12", 8, 4, 0}}, /* <reg: size 4, offset 8 in v12> */
	{"v12.s[3]", {1084, "v12", 12, 4, 0}}, /* <reg: size 4, offset 12 in v12> */
	{"v13.s[0]", {1085, "v13", 0, 4, 0}}, /* <reg: size 4, offset 0 in v13> */
	{"v13.s[1]", {1086, "v13", 4, 4, 0}}, /* <reg: size 4, offset 4 in v13> */
	{"v13.s[2]", {1087, "v13", 8, 4, 0}}, /* <reg: size 4, offset 8 in v13> */
	{"v13.s[3]", {1088, "v13", 12, 4, 0}}, /* <reg: size 4, offset 12 in v13> */
	{"v14.s[0]", {1089, "v14", 0, 4, 0}}, /* <reg: size 4, offset 0 in v14> */
	{"v14.s[1]", {1090, "v14", 4, 4, 0}}, /* <reg: size 4, offset 4 in v14> */
	{"v14.s[2]", {1091, "v14", 8, 4, 0}}, /* <reg: size 4, offset 8 in v14> */
	{"v14.s[3]", {1092, "v14", 12, 4, 0}}, /* <reg: size 4, offset 12 in v14> */
	{"v15.s[0]", {1093, "v15", 0, 4, 0}}, /* <reg: size 4, offset 0 in v15> */
	{"v15.s[1]", {1094, "v15", 4, 4, 0}}, /* <reg: size 4, offset 4 in v15> */
	{"v15.s[2]", {1095, "v15", 8, 4, 0}}, /* <reg: size 4, offset 8 in v15> */
	{"v15.s[3]", {1096, "v15", 12, 4, 0}}, /* <reg: size 4, offset 12 in v15> */
	{"v16.s[0]", {1097, "v16", 0, 4, 0}}, /* <reg: size 4, offset 0 in v16> */
	{"v16.s[1]", {1098, "v16", 4, 4, 0}}, /* <reg: size 4, offset 4 in v16> */
	{"v16.s[2]", {1099, "v16", 8, 4, 0}}, /* <reg: size 4, offset 8 in v16> */
	{"v16.s[3]", {1100, "v16", 12, 4, 0}}, /* <reg: size 4, offset 12 in v16> */
	{"v17.s[0]", {1101, "v17", 0, 4, 0}}, /* <reg: size 4, offset 0 in v17> */
	{"v17.s[1]", {1102, "v17", 4, 4, 0}}, /* <reg: size 4, offset 4 in v17> */
	{"v17.s[2]", {1103, "v17", 8, 4, 0}}, /* <reg: size 4, offset 8 in v17> */
	{"v17.s[3]", {1104, "v17", 12, 4, 0}}, /* <reg: size 4, offset 12 in v17> */
	{"v18.s[0]", {1105, "v18", 0, 4, 0}}, /* <reg: size 4, offset 0 in v18> */
	{"v18.s[1]", {1106, "v18", 4, 4, 0}}, /* <reg: size 4, offset 4 in v18> */
	{"v18.s[2]", {1107, "v18", 8, 4, 0}}, /* <reg: size 4, offset 8 in v18> */
	{"v18.s[3]", {1108, "v18", 12, 4, 0}}, /* <reg: size 4, offset 12 in v18> */
	{"v19.s[0]", {1109, "v19", 0, 4, 0}}, /* <reg: size 4, offset 0 in v19> */
	{"v19.s[1]", {1110, "v19", 4, 4, 0}}, /* <reg: size 4, offset 4 in v19> */
	{"v19.s[2]", {1111, "v19", 8, 4, 0}}, /* <reg: size 4, offset 8 in v19> */
	{"v19.s[3]", {1112, "v19", 12, 4, 0}}, /* <reg: size 4, offset 12 in v19> */
	{"v20.s[0]", {1113, "v20", 0, 4, 0}}, /* <reg: size 4, offset 0 in v20> */
	{"v20.s[1]", {1114, "v20", 4, 4, 0}}, /* <reg: size 4, offset 4 in v20> */
	{"v20.s[2]", {1115, "v20", 8, 4, 0}}, /* <reg: size 4, offset 8 in v20> */
	{"v20.s[3]", {1116, "v20", 12, 4, 0}}, /* <reg: size 4, offset 12 in v20> */
	{"v21.s[0]", {1117, "v21", 0, 4, 0}}, /* <reg: size 4, offset 0 in v21> */
	{"v21.s[1]", {1118, "v21", 4, 4, 0}}, /* <reg: size 4, offset 4 in v21> */
	{"v21.s[2]", {1119, "v21", 8, 4, 0}}, /* <reg: size 4, offset 8 in v21> */
	{"v21.s[3]", {1120, "v21", 12, 4, 0}}, /* <reg: size 4, offset 12 in v21> */
	{"v22.s[0]", {1121, "v22", 0, 4, 0}}, /* <reg: size 4, offset 0 in v22> */
	{"v22.s[1]", {1122, "v22", 4, 4, 0}}, /* <reg: size 4, offset 4 in v22> */
	{"v22.s[2]", {1123, "v22", 8, 4, 0}}, /* <reg: size 4, offset 8 in v22> */
	{"v22.s[3]", {1124, "v22", 12, 4, 0}}, /* <reg: size 4, offset 12 in v22> */
	{"v23.s[0]", {1125, "v23", 0, 4, 0}}, /* <reg: size 4, offset 0 in v23> */
	{"v23.s[1]", {1126, "v23", 4, 4, 0}}, /* <reg: size 4, offset 4 in v23> */
	{"v23.s[2]", {1127, "v23", 8, 4, 0}}, /* <reg: size 4, offset 8 in v23> */
	{"v23.s[3]", {1128, "v23", 12, 4, 0}}, /* <reg: size 4, offset 12 in v23> */
	{"v24.s[0]", {1129, "v24", 0, 4, 0}}, /* <reg: size 4, offset 0 in v24> */
	{"v24.s[1]", {1130, "v24", 4, 4, 0}}, /* <reg: size 4, offset 4 in v24> */
	{"v24.s[2]", {1131, "v24", 8, 4, 0}}, /* <reg: size 4, offset 8 in v24> */
	{"v24.s[3]", {1132, "v24", 12, 4, 0}}, /* <reg: size 4, offset 12 in v24> */
	{"v25.s[0]", {1133, "v25", 0, 4, 0}}, /* <reg: size 4, offset 0 in v25> */
	{"v25.s[1]", {1134, "v25", 4, 4, 0}}, /* <reg: size 4, offset 4 in v25> */
	{"v25.s[2]", {1135, "v25", 8, 4, 0}}, /* <reg: size 4, offset 8 in v25> */
	{"v25.s[3]", {1136, "v25", 12, 4, 0}}, /* <reg: size 4, offset 12 in v25> */
	{"v26.s[0]", {1137, "v26", 0, 4, 0}}, /* <reg: size 4, offset 0 in v26> */
	{"v26.s[1]", {1138, "v26", 4, 4, 0}}, /* <reg: size 4, offset 4 in v26> */
	{"v26.s[2]", {1139, "v26", 8, 4, 0}}, /* <reg: size 4, offset 8 in v26> */
	{"v26.s[3]", {1140, "v26", 12, 4, 0}}, /* <reg: size 4, offset 12 in v26> */
	{"v27.s[0]", {1141, "v27", 0, 4, 0}}, /* <reg: size 4, offset 0 in v27> */
	{"v27.s[1]", {1142, "v27", 4, 4, 0}}, /* <reg: size 4, offset 4 in v27> */
	{"v27.s[2]", {1143, "v27", 8, 4, 0}}, /* <reg: size 4, offset 8 in v27> */
	{"v27.s[3]", {1144, "v27", 12, 4, 0}}, /* <reg: size 4, offset 12 in v27> */
	{"v28.s[0]", {1145, "v28", 0, 4, 0}}, /* <reg: size 4, offset 0 in v28> */
	{"v28.s[1]", {1146, "v28", 4, 4, 0}}, /* <reg: size 4, offset 4 in v28> */
	{"v28.s[2]", {1147, "v28", 8, 4, 0}}, /* <reg: size 4, offset 8 in v28> */
	{"v28.s[3]", {1148, "v28", 12, 4, 0}}, /* <reg: size 4, offset 12 in v28> */
	{"v29.s[0]", {1149, "v29", 0, 4, 0}}, /* <reg: size 4, offset 0 in v29> */
	{"v29.s[1]", {1150, "v29", 4, 4, 0}}, /* <reg: size 4, offset 4 in v29> */
	{"v29.s[2]", {1151, "v29", 8, 4, 0}}, /* <reg: size 4, offset 8 in v29> */
	{"v29.s[3]", {1152, "v29", 12, 4, 0}}, /* <reg: size 4, offset 12 in v29> */
	{"v30.s[0]", {1153, "v30", 0, 4, 0}}, /* <reg: size 4, offset 0 in v30> */
	{"v30.s[1]", {1154, "v30", 4, 4, 0}}, /* <reg: size 4, offset 4 in v30> */
	{"v30.s[2]", {1155, "v30", 8, 4, 0}}, /* <reg: size 4, offset 8 in v30> */
	{"v30.s[3]", {1156, "v30", 12, 4, 0}}, /* <reg: size 4, offset 12 in v30> */
	{"v31.s[0]", {1157, "v31", 0, 4, 0}}, /* <reg: size 4, offset 0 in v31> */
	{"v31.s[1]", {1158, "v31", 4, 4, 0}}, /* <reg: size 4, offset 4 in v31> */
	{"v31.s[2]", {1159, "v31", 8, 4, 0}}, /* <reg: size 4, offset 8 in v31> */
	{"v31.s[3]", {1160, "v31", 12, 4, 0}}, /* <reg: size 4, offset 12 in v31> */
	{"v0.d[0]", {1161, "v0", 0, 8, 0}}, /* <reg: size 8, offset 0 in v0> */
	{"v0.d[1]", {1162, "v0", 8, 8, 0}}, /* <reg: size 8, offset 8 in v0> */
	{"v1.d[0]", {1163, "v1", 0, 8, 0}}, /* <reg: size 8, offset 0 in v1> */
	{"v1.d[1]", {1164, "v1", 8, 8, 0}}, /* <reg: size 8, offset 8 in v1> */
	{"v2.d[0]", {1165, "v2", 0, 8, 0}}, /* <reg: size 8, offset 0 in v2> */
	{"v2.d[1]", {1166, "v2", 8, 8, 0}}, /* <reg: size 8, offset 8 in v2> */
	{"v3.d[0]", {1167, "v3", 0, 8, 0}}, /* <reg: size 8, offset 0 in v3> */
	{"v3.d[1]", {1168, "v3", 8, 8, 0}}, /* <reg: size 8, offset 8 in v3> */
	{"v4.d[0]", {1169, "v4", 0, 8, 0}}, /* <reg: size 8, offset 0 in v4> */
	{"v4.d[1]", {1170, "v4", 8, 8, 0}}, /* <reg: size 8, offset 8 in v4> */
	{"v5.d[0]", {1171, "v5", 0, 8, 0}}, /* <reg: size 8, offset 0 in v5> */
	{"v5.d[1]", {1172, "v5", 8, 8, 0}}, /* <reg: size 8, offset 8 in v5> */
	{"v6.d[0]", {1173, "v6", 0, 8, 0}}, /* <reg: size 8, offset 0 in v6> */
	{"v6.d[1]", {1174, "v6", 8, 8, 0}}, /* <reg: size 8, offset 8 in v6> */
	{"v7.d[0]", {1175, "v7", 0, 8, 0}}, /* <reg: size 8, offset 0 in v7> */
	{"v7.d[1]", {1176, "v7", 8, 8, 0}}, /* <reg: size 8, offset 8 in v7> */
	{"v8.d[0]", {1177, "v8", 0, 8, 0}}, /* <reg: size 8, offset 0 in v8> */
	{"v8.d[1]", {1178, "v8", 8, 8, 0}}, /* <reg: size 8, offset 8 in v8> */
	{"v9.d[0]", {1179, "v9", 0, 8, 0}}, /* <reg: size 8, offset 0 in v9> */
	{"v9.d[1]", {1180, "v9", 8, 8, 0}}, /* <reg: size 8, offset 8 in v9> */
	{"v10.d[0]", {1181, "v10", 0, 8, 0}}, /* <reg: size 8, offset 0 in v10> */
	{"v10.d[1]", {1182, "v10", 8, 8, 0}}, /* <reg: size 8, offset 8 in v10> */
	{"v11.d[0]", {1183, "v11", 0, 8, 0}}, /* <reg: size 8, offset 0 in v11> */
	{"v11.d[1]", {1184, "v11", 8, 8, 0}}, /* <reg: size 8, offset 8 in v11> */
	{"v12.d[0]", {1185, "v12", 0, 8, 0}}, /* <reg: size 8, offset 0 in v12> */
	{"v12.d[1]", {1186, "v12", 8, 8, 0}}, /* <reg: size 8, offset 8 in v12> */
	{"v13.d[0]", {1187, "v13", 0, 8, 0}}, /* <reg: size 8, offset 0 in v13> */
	{"v13.d[1]", {1188, "v13", 8, 8, 0}}, /* <reg: size 8, offset 8 in v13> */
	{"v14.d[0]", {1189, "v14", 0, 8, 0}}, /* <reg: size 8, offset 0 in v14> */
	{"v14.d[1]", {1190, "v14", 8, 8, 0}}, /* <reg: size 8, offset 8 in v14> */
	{"v15.d[0]", {1191, "v15", 0, 8, 0}}, /* <reg: size 8, offset 0 in v15> */
	{"v15.d[1]", {1192, "v15", 8, 8, 0}}, /* <reg: size 8, offset 8 in v15> */
	{"v16.d[0]", {1193, "v16", 0, 8, 0}}, /* <reg: size 8, offset 0 in v16> */
	{"v16.d[1]", {1194, "v16", 8, 8, 0}}, /* <reg: size 8, offset 8 in v16> */
	{"v17.d[0]", {1195, "v17", 0, 8, 0}}, /* <reg: size 8, offset 0 in v17> */
	{"v17.d[1]", {1196, "v17", 8, 8, 0}}, /* <reg: size 8, offset 8 in v17> */
	{"v18.d[0]", {1197, "v18", 0, 8, 0}}, /* <reg: size 8, offset 0 in v18> */
	{"v18.d[1]", {1198, "v18", 8, 8, 0}}, /* <reg: size 8, offset 8 in v18> */
	{"v19.d[0]", {1199, "v19", 0, 8, 0}}, /* <reg: size 8, offset 0 in v19> */
	{"v19.d[1]", {1200, "v19", 8, 8, 0}}, /* <reg: size 8, offset 8 in v19> */
	{"v20.d[0]", {1201, "v20", 0, 8, 0}}, /* <reg: size 8, offset 0 in v20> */
	{"v20.d[1]", {1202, "v20", 8, 8, 0}}, /* <reg: size 8, offset 8 in v20> */
	{"v21.d[0]", {1203, "v21", 0, 8, 0}}, /* <reg: size 8, offset 0 in v21> */
	{"v21.d[1]", {1204, "v21", 8, 8, 0}}, /* <reg: size 8, offset 8 in v21> */
	{"v22.d[0]", {1205, "v22", 0, 8, 0}}, /* <reg: size 8, offset 0 in v22> */
	{"v22.d[1]", {1206, "v22", 8, 8, 0}}, /* <reg: size 8, offset 8 in v22> */
	{"v23.d[0]", {1207, "v23", 0, 8, 0}}, /* <reg: size 8, offset 0 in v23> */
	{"v23.d[1]", {1208, "v23", 8, 8, 0}}, /* <reg: size 8, offset 8 in v23> */
	{"v24.d[0]", {1209, "v24", 0, 8, 0}}, /* <reg: size 8, offset 0 in v24> */
	{"v24.d[1]", {1210, "v24", 8, 8, 0}}, /* <reg: size 8, offset 8 in v24> */
	{"v25.d[0]", {1211, "v25", 0, 8, 0}}, /* <reg: size 8, offset 0 in v25> */
	{"v25.d[1]", {1212, "v25", 8, 8, 0}}, /* <reg: size 8, offset 8 in v25> */
	{"v26.d[0]", {1213, "v26", 0, 8, 0}}, /* <reg: size 8, offset 0 in v26> */
	{"v26.d[1]", {1214, "v26", 8, 8, 0}}, /* <reg: size 8, offset 8 in v26> */
	{"v27.d[0]", {1215, "v27", 0, 8, 0}}, /* <reg: size 8, offset 0 in v27> */
	{"v27.d[1]", {1216, "v27", 8, 8, 0}}, /* <reg: size 8, offset 8 in v27> */
	{"v28.d[0]", {1217, "v28", 0, 8, 0}}, /* <reg: size 8, offset 0 in v28> */
	{"v28.d[1]", {1218, "v28", 8, 8, 0}}, /* <reg: size 8, offset 8 in v28> */
	{"v29.d[0]", {1219, "v29", 0, 8, 0}}, /* <reg: size 8, offset 0 in v29> */
	{"v29.d[1]", {1220, "v29", 8, 8, 0}}, /* <reg: size 8, offset 8 in v29> */
	{"v30.d[0]", {1221, "v30", 0, 8, 0}}, /* <reg: size 8, offset 0 in v30> */
	{"v30.d[1]", {1222, "v30", 8, 8, 0}}, /* <reg: size 8, offset 8 in v30> */
	{"v31.d[0]", {1223, "v31", 0, 8, 0}}, /* <reg: size 8, offset 0 in v31> */
	{"v31.d[1]", {1224, "v31", 8, 8, 0}}, /* <reg: size 8, offset 8 in v31> */
	{"osdtrrx_el1", {32770, "osdtrrx_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in osdtrrx_el1> */
	{"dbgbvr0_el1", {32772, "dbgbvr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr0_el1> */
	{"dbgbcr0_el1", {32773, "dbgbcr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr0_el1> */
	{"dbgwvr0_el1", {32774, "dbgwvr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr0_el1> */
	{"dbgwcr0_el1", {32775, "dbgwcr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr0_el1> */
	{"dbgbvr1_el1", {32780, "dbgbvr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr1_el1> */
	{"dbgbcr1_el1", {32781, "dbgbcr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr1_el1> */
	{"dbgwvr1_el1", {32782, "dbgwvr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr1_el1> */
	{"dbgwcr1_el1", {32783, "dbgwcr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr1_el1> */
	{"mdccint_el1", {32784, "mdccint_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in mdccint_el1> */
	{"mdscr_el1", {32786, "mdscr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in mdscr_el1> */
	{"dbgbvr2_el1", {32788, "dbgbvr2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr2_el1> */
	{"dbgbcr2_el1", {32789, "dbgbcr2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr2_el1> */
	{"dbgwvr2_el1", {32790, "dbgwvr2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr2_el1> */
	{"dbgwcr2_el1", {32791, "dbgwcr2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr2_el1> */
	{"osdtrtx_el1", {32794, "osdtrtx_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in osdtrtx_el1> */
	{"dbgbvr3_el1", {32796, "dbgbvr3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr3_el1> */
	{"dbgbcr3_el1", {32797, "dbgbcr3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr3_el1> */
	{"dbgwvr3_el1", {32798, "dbgwvr3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr3_el1> */
	{"dbgwcr3_el1", {32799, "dbgwcr3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr3_el1> */
	{"dbgbvr4_el1", {32804, "dbgbvr4_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr4_el1> */
	{"dbgbcr4_el1", {32805, "dbgbcr4_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr4_el1> */
	{"dbgwvr4_el1", {32806, "dbgwvr4_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr4_el1> */
	{"dbgwcr4_el1", {32807, "dbgwcr4_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr4_el1> */
	{"dbgbvr5_el1", {32812, "dbgbvr5_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr5_el1> */
	{"dbgbcr5_el1", {32813, "dbgbcr5_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr5_el1> */
	{"dbgwvr5_el1", {32814, "dbgwvr5_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr5_el1> */
	{"dbgwcr5_el1", {32815, "dbgwcr5_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr5_el1> */
	{"oseccr_el1", {32818, "oseccr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in oseccr_el1> */
	{"dbgbvr6_el1", {32820, "dbgbvr6_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr6_el1> */
	{"dbgbcr6_el1", {32821, "dbgbcr6_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr6_el1> */
	{"dbgwvr6_el1", {32822, "dbgwvr6_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr6_el1> */
	{"dbgwcr6_el1", {32823, "dbgwcr6_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr6_el1> */
	{"dbgbvr7_el1", {32828, "dbgbvr7_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr7_el1> */
	{"dbgbcr7_el1", {32829, "dbgbcr7_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr7_el1> */
	{"dbgwvr7_el1", {32830, "dbgwvr7_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr7_el1> */
	{"dbgwcr7_el1", {32831, "dbgwcr7_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr7_el1> */
	{"dbgbvr8_el1", {32836, "dbgbvr8_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr8_el1> */
	{"dbgbcr8_el1", {32837, "dbgbcr8_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr8_el1> */
	{"dbgwvr8_el1", {32838, "dbgwvr8_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr8_el1> */
	{"dbgwcr8_el1", {32839, "dbgwcr8_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr8_el1> */
	{"dbgbvr9_el1", {32844, "dbgbvr9_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr9_el1> */
	{"dbgbcr9_el1", {32845, "dbgbcr9_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr9_el1> */
	{"dbgwvr9_el1", {32846, "dbgwvr9_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr9_el1> */
	{"dbgwcr9_el1", {32847, "dbgwcr9_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr9_el1> */
	{"dbgbvr10_el1", {32852, "dbgbvr10_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr10_el1> */
	{"dbgbcr10_el1", {32853, "dbgbcr10_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr10_el1> */
	{"dbgwvr10_el1", {32854, "dbgwvr10_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr10_el1> */
	{"dbgwcr10_el1", {32855, "dbgwcr10_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr10_el1> */
	{"dbgbvr11_el1", {32860, "dbgbvr11_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr11_el1> */
	{"dbgbcr11_el1", {32861, "dbgbcr11_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr11_el1> */
	{"dbgwvr11_el1", {32862, "dbgwvr11_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr11_el1> */
	{"dbgwcr11_el1", {32863, "dbgwcr11_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr11_el1> */
	{"dbgbvr12_el1", {32868, "dbgbvr12_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr12_el1> */
	{"dbgbcr12_el1", {32869, "dbgbcr12_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr12_el1> */
	{"dbgwvr12_el1", {32870, "dbgwvr12_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr12_el1> */
	{"dbgwcr12_el1", {32871, "dbgwcr12_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr12_el1> */
	{"dbgbvr13_el1", {32876, "dbgbvr13_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr13_el1> */
	{"dbgbcr13_el1", {32877, "dbgbcr13_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr13_el1> */
	{"dbgwvr13_el1", {32878, "dbgwvr13_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr13_el1> */
	{"dbgwcr13_el1", {32879, "dbgwcr13_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr13_el1> */
	{"dbgbvr14_el1", {32884, "dbgbvr14_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr14_el1> */
	{"dbgbcr14_el1", {32885, "dbgbcr14_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr14_el1> */
	{"dbgwvr14_el1", {32886, "dbgwvr14_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr14_el1> */
	{"dbgwcr14_el1", {32887, "dbgwcr14_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr14_el1> */
	{"dbgbvr15_el1", {32892, "dbgbvr15_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbvr15_el1> */
	{"dbgbcr15_el1", {32893, "dbgbcr15_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgbcr15_el1> */
	{"dbgwvr15_el1", {32894, "dbgwvr15_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwvr15_el1> */
	{"dbgwcr15_el1", {32895, "dbgwcr15_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgwcr15_el1> */
	{"oslar_el1", {32900, "oslar_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in oslar_el1> */
	{"osdlr_el1", {32924, "osdlr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in osdlr_el1> */
	{"dbgprcr_el1", {32932, "dbgprcr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgprcr_el1> */
	{"dbgclaimset_el1", {33734, "dbgclaimset_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgclaimset_el1> */
	{"dbgclaimclr_el1", {33742, "dbgclaimclr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgclaimclr_el1> */
	{"trctraceidr", {34817, "trctraceidr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trctraceidr> */
	{"trcvictlr", {34818, "trcvictlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvictlr> */
	{"trcseqevr0", {34820, "trcseqevr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcseqevr0> */
	{"trccntrldvr0", {34821, "trccntrldvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntrldvr0> */
	{"trcimspec0", {34823, "trcimspec0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec0> */
	{"trcprgctlr", {34824, "trcprgctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcprgctlr> */
	{"trcqctlr", {34825, "trcqctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcqctlr> */
	{"trcviiectlr", {34826, "trcviiectlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcviiectlr> */
	{"trcseqevr1", {34828, "trcseqevr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcseqevr1> */
	{"trccntrldvr1", {34829, "trccntrldvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntrldvr1> */
	{"trcimspec1", {34831, "trcimspec1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec1> */
	{"trcprocselr", {34832, "trcprocselr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcprocselr> */
	{"trcvissctlr", {34834, "trcvissctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvissctlr> */
	{"trcseqevr2", {34836, "trcseqevr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcseqevr2> */
	{"trccntrldvr2", {34837, "trccntrldvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntrldvr2> */
	{"trcimspec2", {34839, "trcimspec2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec2> */
	{"trcvipcssctlr", {34842, "trcvipcssctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvipcssctlr> */
	{"trccntrldvr3", {34845, "trccntrldvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntrldvr3> */
	{"trcimspec3", {34847, "trcimspec3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec3> */
	{"trcconfigr", {34848, "trcconfigr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcconfigr> */
	{"trccntctlr0", {34853, "trccntctlr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntctlr0> */
	{"trcimspec4", {34855, "trcimspec4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec4> */
	{"trccntctlr1", {34861, "trccntctlr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntctlr1> */
	{"trcimspec5", {34863, "trcimspec5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec5> */
	{"trcauxctlr", {34864, "trcauxctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcauxctlr> */
	{"trcseqrstevr", {34868, "trcseqrstevr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcseqrstevr> */
	{"trccntctlr2", {34869, "trccntctlr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntctlr2> */
	{"trcimspec6", {34871, "trcimspec6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec6> */
	{"trcseqstr", {34876, "trcseqstr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcseqstr> */
	{"trccntctlr3", {34877, "trccntctlr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntctlr3> */
	{"trcimspec7", {34879, "trcimspec7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcimspec7> */
	{"trceventctl0r", {34880, "trceventctl0r", 0, 8, 0}}, /* <reg: size 8, offset 0 in trceventctl0r> */
	{"trcvdctlr", {34882, "trcvdctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvdctlr> */
	{"trcextinselr", {34884, "trcextinselr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcextinselr> */
	{"trccntvr0", {34885, "trccntvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntvr0> */
	{"trceventctl1r", {34888, "trceventctl1r", 0, 8, 0}}, /* <reg: size 8, offset 0 in trceventctl1r> */
	{"trcvdsacctlr", {34890, "trcvdsacctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvdsacctlr> */
	{"trcextinselr1", {34892, "trcextinselr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcextinselr1> */
	{"trccntvr1", {34893, "trccntvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntvr1> */
	{"trcrsr", {34896, "trcrsr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsr> */
	{"trcvdarcctlr", {34898, "trcvdarcctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvdarcctlr> */
	{"trcextinselr2", {34900, "trcextinselr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcextinselr2> */
	{"trccntvr2", {34901, "trccntvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntvr2> */
	{"trcstallctlr", {34904, "trcstallctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcstallctlr> */
	{"trcextinselr3", {34908, "trcextinselr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcextinselr3> */
	{"trccntvr3", {34909, "trccntvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccntvr3> */
	{"trctsctlr", {34912, "trctsctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trctsctlr> */
	{"trcsyncpr", {34920, "trcsyncpr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsyncpr> */
	{"trcccctlr", {34928, "trcccctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcccctlr> */
	{"trcbbctlr", {34936, "trcbbctlr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcbbctlr> */
	{"trcrsctlr16", {34945, "trcrsctlr16", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr16> */
	{"trcssccr0", {34946, "trcssccr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr0> */
	{"trcsspcicr0", {34947, "trcsspcicr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr0> */
	{"trcoslar", {34948, "trcoslar", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcoslar> */
	{"trcrsctlr17", {34953, "trcrsctlr17", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr17> */
	{"trcssccr1", {34954, "trcssccr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr1> */
	{"trcsspcicr1", {34955, "trcsspcicr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr1> */
	{"trcrsctlr2", {34960, "trcrsctlr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr2> */
	{"trcrsctlr18", {34961, "trcrsctlr18", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr18> */
	{"trcssccr2", {34962, "trcssccr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr2> */
	{"trcsspcicr2", {34963, "trcsspcicr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr2> */
	{"trcrsctlr3", {34968, "trcrsctlr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr3> */
	{"trcrsctlr19", {34969, "trcrsctlr19", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr19> */
	{"trcssccr3", {34970, "trcssccr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr3> */
	{"trcsspcicr3", {34971, "trcsspcicr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr3> */
	{"trcrsctlr4", {34976, "trcrsctlr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr4> */
	{"trcrsctlr20", {34977, "trcrsctlr20", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr20> */
	{"trcssccr4", {34978, "trcssccr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr4> */
	{"trcsspcicr4", {34979, "trcsspcicr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr4> */
	{"trcpdcr", {34980, "trcpdcr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcpdcr> */
	{"trcrsctlr5", {34984, "trcrsctlr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr5> */
	{"trcrsctlr21", {34985, "trcrsctlr21", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr21> */
	{"trcssccr5", {34986, "trcssccr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr5> */
	{"trcsspcicr5", {34987, "trcsspcicr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr5> */
	{"trcrsctlr6", {34992, "trcrsctlr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr6> */
	{"trcrsctlr22", {34993, "trcrsctlr22", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr22> */
	{"trcssccr6", {34994, "trcssccr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr6> */
	{"trcsspcicr6", {34995, "trcsspcicr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr6> */
	{"trcrsctlr7", {35000, "trcrsctlr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr7> */
	{"trcrsctlr23", {35001, "trcrsctlr23", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr23> */
	{"trcssccr7", {35002, "trcssccr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcssccr7> */
	{"trcsspcicr7", {35003, "trcsspcicr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsspcicr7> */
	{"trcrsctlr8", {35008, "trcrsctlr8", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr8> */
	{"trcrsctlr24", {35009, "trcrsctlr24", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr24> */
	{"trcsscsr0", {35010, "trcsscsr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr0> */
	{"trcrsctlr9", {35016, "trcrsctlr9", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr9> */
	{"trcrsctlr25", {35017, "trcrsctlr25", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr25> */
	{"trcsscsr1", {35018, "trcsscsr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr1> */
	{"trcrsctlr10", {35024, "trcrsctlr10", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr10> */
	{"trcrsctlr26", {35025, "trcrsctlr26", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr26> */
	{"trcsscsr2", {35026, "trcsscsr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr2> */
	{"trcrsctlr11", {35032, "trcrsctlr11", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr11> */
	{"trcrsctlr27", {35033, "trcrsctlr27", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr27> */
	{"trcsscsr3", {35034, "trcsscsr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr3> */
	{"trcrsctlr12", {35040, "trcrsctlr12", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr12> */
	{"trcrsctlr28", {35041, "trcrsctlr28", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr28> */
	{"trcsscsr4", {35042, "trcsscsr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr4> */
	{"trcrsctlr13", {35048, "trcrsctlr13", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr13> */
	{"trcrsctlr29", {35049, "trcrsctlr29", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr29> */
	{"trcsscsr5", {35050, "trcsscsr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr5> */
	{"trcrsctlr14", {35056, "trcrsctlr14", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr14> */
	{"trcrsctlr30", {35057, "trcrsctlr30", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr30> */
	{"trcsscsr6", {35058, "trcsscsr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr6> */
	{"trcrsctlr15", {35064, "trcrsctlr15", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr15> */
	{"trcrsctlr31", {35065, "trcrsctlr31", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcrsctlr31> */
	{"trcsscsr7", {35066, "trcsscsr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcsscsr7> */
	{"trcacvr0", {35072, "trcacvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr0> */
	{"trcacvr8", {35073, "trcacvr8", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr8> */
	{"trcacatr0", {35074, "trcacatr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr0> */
	{"trcacatr8", {35075, "trcacatr8", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr8> */
	{"trcdvcvr0", {35076, "trcdvcvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr0> */
	{"trcdvcvr4", {35077, "trcdvcvr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr4> */
	{"trcdvcmr0", {35078, "trcdvcmr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr0> */
	{"trcdvcmr4", {35079, "trcdvcmr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr4> */
	{"trcacvr1", {35088, "trcacvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr1> */
	{"trcacvr9", {35089, "trcacvr9", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr9> */
	{"trcacatr1", {35090, "trcacatr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr1> */
	{"trcacatr9", {35091, "trcacatr9", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr9> */
	{"trcacvr2", {35104, "trcacvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr2> */
	{"trcacvr10", {35105, "trcacvr10", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr10> */
	{"trcacatr2", {35106, "trcacatr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr2> */
	{"trcacatr10", {35107, "trcacatr10", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr10> */
	{"trcdvcvr1", {35108, "trcdvcvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr1> */
	{"trcdvcvr5", {35109, "trcdvcvr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr5> */
	{"trcdvcmr1", {35110, "trcdvcmr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr1> */
	{"trcdvcmr5", {35111, "trcdvcmr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr5> */
	{"trcacvr3", {35120, "trcacvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr3> */
	{"trcacvr11", {35121, "trcacvr11", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr11> */
	{"trcacatr3", {35122, "trcacatr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr3> */
	{"trcacatr11", {35123, "trcacatr11", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr11> */
	{"trcacvr4", {35136, "trcacvr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr4> */
	{"trcacvr12", {35137, "trcacvr12", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr12> */
	{"trcacatr4", {35138, "trcacatr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr4> */
	{"trcacatr12", {35139, "trcacatr12", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr12> */
	{"trcdvcvr2", {35140, "trcdvcvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr2> */
	{"trcdvcvr6", {35141, "trcdvcvr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr6> */
	{"trcdvcmr2", {35142, "trcdvcmr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr2> */
	{"trcdvcmr6", {35143, "trcdvcmr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr6> */
	{"trcacvr5", {35152, "trcacvr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr5> */
	{"trcacvr13", {35153, "trcacvr13", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr13> */
	{"trcacatr5", {35154, "trcacatr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr5> */
	{"trcacatr13", {35155, "trcacatr13", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr13> */
	{"trcacvr6", {35168, "trcacvr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr6> */
	{"trcacvr14", {35169, "trcacvr14", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr14> */
	{"trcacatr6", {35170, "trcacatr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr6> */
	{"trcacatr14", {35171, "trcacatr14", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr14> */
	{"trcdvcvr3", {35172, "trcdvcvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr3> */
	{"trcdvcvr7", {35173, "trcdvcvr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcvr7> */
	{"trcdvcmr3", {35174, "trcdvcmr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr3> */
	{"trcdvcmr7", {35175, "trcdvcmr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcdvcmr7> */
	{"trcacvr7", {35184, "trcacvr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr7> */
	{"trcacvr15", {35185, "trcacvr15", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacvr15> */
	{"trcacatr7", {35186, "trcacatr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr7> */
	{"trcacatr15", {35187, "trcacatr15", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcacatr15> */
	{"trccidcvr0", {35200, "trccidcvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr0> */
	{"trcvmidcvr0", {35201, "trcvmidcvr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr0> */
	{"trccidcctlr0", {35202, "trccidcctlr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcctlr0> */
	{"trccidcctlr1", {35210, "trccidcctlr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcctlr1> */
	{"trccidcvr1", {35216, "trccidcvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr1> */
	{"trcvmidcvr1", {35217, "trcvmidcvr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr1> */
	{"trcvmidcctlr0", {35218, "trcvmidcctlr0", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcctlr0> */
	{"trcvmidcctlr1", {35226, "trcvmidcctlr1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcctlr1> */
	{"trccidcvr2", {35232, "trccidcvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr2> */
	{"trcvmidcvr2", {35233, "trcvmidcvr2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr2> */
	{"trccidcvr3", {35248, "trccidcvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr3> */
	{"trcvmidcvr3", {35249, "trcvmidcvr3", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr3> */
	{"trccidcvr4", {35264, "trccidcvr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr4> */
	{"trcvmidcvr4", {35265, "trcvmidcvr4", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr4> */
	{"trccidcvr5", {35280, "trccidcvr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr5> */
	{"trcvmidcvr5", {35281, "trcvmidcvr5", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr5> */
	{"trccidcvr6", {35296, "trccidcvr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr6> */
	{"trcvmidcvr6", {35297, "trcvmidcvr6", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr6> */
	{"trccidcvr7", {35312, "trccidcvr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trccidcvr7> */
	{"trcvmidcvr7", {35313, "trcvmidcvr7", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcvmidcvr7> */
	{"trcitctrl", {35716, "trcitctrl", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcitctrl> */
	{"trcclaimset", {35782, "trcclaimset", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcclaimset> */
	{"trcclaimclr", {35790, "trcclaimclr", 0, 8, 0}}, /* <reg: size 8, offset 0 in trcclaimclr> */
	{"trclar", {35814, "trclar", 0, 8, 0}}, /* <reg: size 8, offset 0 in trclar> */
	{"teecr32_el1", {36864, "teecr32_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in teecr32_el1> */
	{"teehbr32_el1", {36992, "teehbr32_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in teehbr32_el1> */
	{"dbgdtr_el0", {38944, "dbgdtr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgdtr_el0> */
	{"dbgdtrtx_el0", {38952, "dbgdtrtx_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgdtrtx_el0> */
	{"dbgvcr32_el2", {41016, "dbgvcr32_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in dbgvcr32_el2> */
	{"sctlr_el1", {49280, "sctlr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in sctlr_el1> */
	{"actlr_el1", {49281, "actlr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in actlr_el1> */
	{"cpacr_el1", {49282, "cpacr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in cpacr_el1> */
	{"rgsr_el1", {49285, "rgsr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in rgsr_el1> */
	{"gcr_el1", {49286, "gcr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in gcr_el1> */
	{"trfcr_el1", {49297, "trfcr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trfcr_el1> */
	{"ttbr0_el1", {49408, "ttbr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr0_el1> */
	{"ttbr1_el1", {49409, "ttbr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr1_el1> */
	{"tcr_el1", {49410, "tcr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in tcr_el1> */
	{"apiakeylo_el1", {49416, "apiakeylo_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apiakeylo_el1> */
	{"apiakeyhi_el1", {49417, "apiakeyhi_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apiakeyhi_el1> */
	{"apibkeylo_el1", {49418, "apibkeylo_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apibkeylo_el1> */
	{"apibkeyhi_el1", {49419, "apibkeyhi_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apibkeyhi_el1> */
	{"apdakeylo_el1", {49424, "apdakeylo_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apdakeylo_el1> */
	{"apdakeyhi_el1", {49425, "apdakeyhi_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apdakeyhi_el1> */
	{"apdbkeylo_el1", {49426, "apdbkeylo_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apdbkeylo_el1> */
	{"apdbkeyhi_el1", {49427, "apdbkeyhi_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apdbkeyhi_el1> */
	{"apgakeylo_el1", {49432, "apgakeylo_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apgakeylo_el1> */
	{"apgakeyhi_el1", {49433, "apgakeyhi_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in apgakeyhi_el1> */
	{"spsr_el1", {49664, "spsr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_el1> */
	{"elr_el1", {49665, "elr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in elr_el1> */
	{"sp_el0", {49672, "sp_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in sp_el0> */
	{"spsel", {65299, "spsel", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsel> */
	{"currentel", {49682, "currentel", 0, 8, 0}}, /* <reg: size 8, offset 0 in currentel> */
	{"pan", {49683, "pan", 0, 8, 0}}, /* <reg: size 8, offset 0 in pan> */
	{"uao", {49684, "uao", 0, 8, 0}}, /* <reg: size 8, offset 0 in uao> */
	{"icc_pmr_el1", {49712, "icc_pmr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_pmr_el1> */
	{"afsr0_el1", {49800, "afsr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr0_el1> */
	{"afsr1_el1", {49801, "afsr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr1_el1> */
	{"esr_el1", {49808, "esr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in esr_el1> */
	{"errselr_el1", {49817, "errselr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in errselr_el1> */
	{"erxctlr_el1", {49825, "erxctlr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxctlr_el1> */
	{"erxstatus_el1", {49826, "erxstatus_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxstatus_el1> */
	{"erxaddr_el1", {49827, "erxaddr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxaddr_el1> */
	{"erxpfgctl_el1", {49829, "erxpfgctl_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxpfgctl_el1> */
	{"erxpfgcdn_el1", {49830, "erxpfgcdn_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxpfgcdn_el1> */
	{"erxmisc0_el1", {49832, "erxmisc0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxmisc0_el1> */
	{"erxmisc1_el1", {49833, "erxmisc1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxmisc1_el1> */
	{"erxmisc2_el1", {49834, "erxmisc2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxmisc2_el1> */
	{"erxmisc3_el1", {49835, "erxmisc3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxmisc3_el1> */
	{"erxts_el1", {49839, "erxts_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in erxts_el1> */
	{"tfsr_el1", {49840, "tfsr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in tfsr_el1> */
	{"tfsre0_el1", {49841, "tfsre0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in tfsre0_el1> */
	{"far_el1", {49920, "far_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in far_el1> */
	{"par_el1", {50080, "par_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in par_el1> */
	{"pmscr_el1", {50376, "pmscr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmscr_el1> */
	{"pmsicr_el1", {50378, "pmsicr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmsicr_el1> */
	{"pmsirr_el1", {50379, "pmsirr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmsirr_el1> */
	{"pmsfcr_el1", {50380, "pmsfcr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmsfcr_el1> */
	{"pmsevfr_el1", {50381, "pmsevfr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmsevfr_el1> */
	{"pmslatfr_el1", {50382, "pmslatfr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmslatfr_el1> */
	{"pmsidr_el1", {50383, "pmsidr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmsidr_el1> */
	{"pmblimitr_el1", {50384, "pmblimitr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmblimitr_el1> */
	{"pmbptr_el1", {50385, "pmbptr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmbptr_el1> */
	{"pmbsr_el1", {50387, "pmbsr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmbsr_el1> */
	{"pmbidr_el1", {50391, "pmbidr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmbidr_el1> */
	{"trblimitr_el1", {50392, "trblimitr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trblimitr_el1> */
	{"trbptr_el1", {50393, "trbptr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trbptr_el1> */
	{"trbbaser_el1", {50394, "trbbaser_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trbbaser_el1> */
	{"trbsr_el1", {50395, "trbsr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trbsr_el1> */
	{"trbmar_el1", {50396, "trbmar_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trbmar_el1> */
	{"trbtrg_el1", {50398, "trbtrg_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in trbtrg_el1> */
	{"pmintenset_el1", {50417, "pmintenset_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmintenset_el1> */
	{"pmintenclr_el1", {50418, "pmintenclr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmintenclr_el1> */
	{"pmmir_el1", {50422, "pmmir_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmmir_el1> */
	{"mair_el1", {50448, "mair_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in mair_el1> */
	{"amair_el1", {50456, "amair_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in amair_el1> */
	{"lorsa_el1", {50464, "lorsa_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in lorsa_el1> */
	{"lorea_el1", {50465, "lorea_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in lorea_el1> */
	{"lorn_el1", {50466, "lorn_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in lorn_el1> */
	{"lorc_el1", {50467, "lorc_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in lorc_el1> */
	{"mpam1_el1", {50472, "mpam1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpam1_el1> */
	{"mpam0_el1", {50473, "mpam0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpam0_el1> */
	{"vbar_el1", {50688, "vbar_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in vbar_el1> */
	{"rmr_el1", {50690, "rmr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in rmr_el1> */
	{"disr_el1", {50697, "disr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in disr_el1> */
	{"icc_eoir0_el1", {50753, "icc_eoir0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_eoir0_el1> */
	{"icc_bpr0_el1", {50755, "icc_bpr0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_bpr0_el1> */
	{"icc_ap0r0_el1", {50756, "icc_ap0r0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap0r0_el1> */
	{"icc_ap0r1_el1", {50757, "icc_ap0r1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap0r1_el1> */
	{"icc_ap0r2_el1", {50758, "icc_ap0r2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap0r2_el1> */
	{"icc_ap0r3_el1", {50759, "icc_ap0r3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap0r3_el1> */
	{"icc_ap1r0_el1", {50760, "icc_ap1r0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap1r0_el1> */
	{"icc_ap1r1_el1", {50761, "icc_ap1r1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap1r1_el1> */
	{"icc_ap1r2_el1", {50762, "icc_ap1r2_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap1r2_el1> */
	{"icc_ap1r3_el1", {50763, "icc_ap1r3_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ap1r3_el1> */
	{"icc_dir_el1", {50777, "icc_dir_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_dir_el1> */
	{"icc_sgi1r_el1", {50781, "icc_sgi1r_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_sgi1r_el1> */
	{"icc_asgi1r_el1", {50782, "icc_asgi1r_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_asgi1r_el1> */
	{"icc_sgi0r_el1", {50783, "icc_sgi0r_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_sgi0r_el1> */
	{"icc_eoir1_el1", {50785, "icc_eoir1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_eoir1_el1> */
	{"icc_bpr1_el1", {50787, "icc_bpr1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_bpr1_el1> */
	{"icc_ctlr_el1", {50788, "icc_ctlr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ctlr_el1> */
	{"icc_sre_el1", {50789, "icc_sre_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_sre_el1> */
	{"icc_igrpen0_el1", {50790, "icc_igrpen0_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_igrpen0_el1> */
	{"icc_igrpen1_el1", {50791, "icc_igrpen1_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_igrpen1_el1> */
	{"icc_seien_el1", {50792, "icc_seien_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_seien_el1> */
	{"contextidr_el1", {50817, "contextidr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in contextidr_el1> */
	{"tpidr_el1", {50820, "tpidr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in tpidr_el1> */
	{"scxtnum_el1", {50823, "scxtnum_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in scxtnum_el1> */
	{"cntkctl_el1", {50952, "cntkctl_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntkctl_el1> */
	{"csselr_el1", {53248, "csselr_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in csselr_el1> */
	{"nzcv", {55824, "nzcv", 0, 8, 0}}, /* <reg: size 8, offset 0 in nzcv> */
	{"daifset", {55825, "daifset", 0, 8, 0}}, /* <reg: size 8, offset 0 in daifset> */
	{"dit", {55829, "dit", 0, 8, 0}}, /* <reg: size 8, offset 0 in dit> */
	{"ssbs", {55830, "ssbs", 0, 8, 0}}, /* <reg: size 8, offset 0 in ssbs> */
	{"tco", {55831, "tco", 0, 8, 0}}, /* <reg: size 8, offset 0 in tco> */
	{"fpcr", {55840, "fpcr", 0, 8, 0}}, /* <reg: size 8, offset 0 in fpcr> */
	{"fpsr", {55841, "fpsr", 0, 8, 0}}, /* <reg: size 8, offset 0 in fpsr> */
	{"dspsr_el0", {55848, "dspsr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in dspsr_el0> */
	{"dlr_el0", {55849, "dlr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in dlr_el0> */
	{"pmcr_el0", {56544, "pmcr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmcr_el0> */
	{"pmcntenset_el0", {56545, "pmcntenset_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmcntenset_el0> */
	{"pmcntenclr_el0", {56546, "pmcntenclr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmcntenclr_el0> */
	{"pmovsclr_el0", {56547, "pmovsclr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmovsclr_el0> */
	{"pmswinc_el0", {56548, "pmswinc_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmswinc_el0> */
	{"pmselr_el0", {56549, "pmselr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmselr_el0> */
	{"pmccntr_el0", {56552, "pmccntr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmccntr_el0> */
	{"pmxevtyper_el0", {56553, "pmxevtyper_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmxevtyper_el0> */
	{"pmxevcntr_el0", {56554, "pmxevcntr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmxevcntr_el0> */
	{"daifclr", {56557, "daifclr", 0, 8, 0}}, /* <reg: size 8, offset 0 in daifclr> */
	{"pmuserenr_el0", {56560, "pmuserenr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmuserenr_el0> */
	{"pmovsset_el0", {56563, "pmovsset_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmovsset_el0> */
	{"tpidr_el0", {56962, "tpidr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in tpidr_el0> */
	{"tpidrro_el0", {56963, "tpidrro_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in tpidrro_el0> */
	{"scxtnum_el0", {56967, "scxtnum_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in scxtnum_el0> */
	{"amcr_el0", {56976, "amcr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amcr_el0> */
	{"amuserenr_el0", {56979, "amuserenr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amuserenr_el0> */
	{"amcntenclr0_el0", {56980, "amcntenclr0_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amcntenclr0_el0> */
	{"amcntenset0_el0", {56981, "amcntenset0_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amcntenset0_el0> */
	{"amcntenclr1_el0", {56984, "amcntenclr1_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amcntenclr1_el0> */
	{"amcntenset1_el0", {56985, "amcntenset1_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amcntenset1_el0> */
	{"amevcntr00_el0", {56992, "amevcntr00_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr00_el0> */
	{"amevcntr01_el0", {56993, "amevcntr01_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr01_el0> */
	{"amevcntr02_el0", {56994, "amevcntr02_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr02_el0> */
	{"amevcntr03_el0", {56995, "amevcntr03_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr03_el0> */
	{"amevcntr10_el0", {57056, "amevcntr10_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr10_el0> */
	{"amevcntr11_el0", {57057, "amevcntr11_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr11_el0> */
	{"amevcntr12_el0", {57058, "amevcntr12_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr12_el0> */
	{"amevcntr13_el0", {57059, "amevcntr13_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr13_el0> */
	{"amevcntr14_el0", {57060, "amevcntr14_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr14_el0> */
	{"amevcntr15_el0", {57061, "amevcntr15_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr15_el0> */
	{"amevcntr16_el0", {57062, "amevcntr16_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr16_el0> */
	{"amevcntr17_el0", {57063, "amevcntr17_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr17_el0> */
	{"amevcntr18_el0", {57064, "amevcntr18_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr18_el0> */
	{"amevcntr19_el0", {57065, "amevcntr19_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr19_el0> */
	{"amevcntr110_el0", {57066, "amevcntr110_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr110_el0> */
	{"amevcntr111_el0", {57067, "amevcntr111_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr111_el0> */
	{"amevcntr112_el0", {57068, "amevcntr112_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr112_el0> */
	{"amevcntr113_el0", {57069, "amevcntr113_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr113_el0> */
	{"amevcntr114_el0", {57070, "amevcntr114_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr114_el0> */
	{"amevcntr115_el0", {57071, "amevcntr115_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevcntr115_el0> */
	{"amevtyper10_el0", {57072, "amevtyper10_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper10_el0> */
	{"amevtyper11_el0", {57073, "amevtyper11_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper11_el0> */
	{"amevtyper12_el0", {57074, "amevtyper12_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper12_el0> */
	{"amevtyper13_el0", {57075, "amevtyper13_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper13_el0> */
	{"amevtyper14_el0", {57076, "amevtyper14_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper14_el0> */
	{"amevtyper15_el0", {57077, "amevtyper15_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper15_el0> */
	{"amevtyper16_el0", {57078, "amevtyper16_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper16_el0> */
	{"amevtyper17_el0", {57079, "amevtyper17_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper17_el0> */
	{"amevtyper18_el0", {57080, "amevtyper18_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper18_el0> */
	{"amevtyper19_el0", {57081, "amevtyper19_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper19_el0> */
	{"amevtyper110_el0", {57082, "amevtyper110_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper110_el0> */
	{"amevtyper111_el0", {57083, "amevtyper111_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper111_el0> */
	{"amevtyper112_el0", {57084, "amevtyper112_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper112_el0> */
	{"amevtyper113_el0", {57085, "amevtyper113_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper113_el0> */
	{"amevtyper114_el0", {57086, "amevtyper114_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper114_el0> */
	{"amevtyper115_el0", {57087, "amevtyper115_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in amevtyper115_el0> */
	{"cntfrq_el0", {57088, "cntfrq_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntfrq_el0> */
	{"cntp_tval_el0", {57104, "cntp_tval_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_tval_el0> */
	{"cntp_ctl_el0", {57105, "cntp_ctl_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_ctl_el0> */
	{"cntp_cval_el0", {57106, "cntp_cval_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_cval_el0> */
	{"cntv_tval_el0", {57112, "cntv_tval_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_tval_el0> */
	{"cntv_ctl_el0", {57113, "cntv_ctl_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_ctl_el0> */
	{"cntv_cval_el0", {57114, "cntv_cval_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_cval_el0> */
	{"pmevcntr0_el0", {57152, "pmevcntr0_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr0_el0> */
	{"pmevcntr1_el0", {57153, "pmevcntr1_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr1_el0> */
	{"pmevcntr2_el0", {57154, "pmevcntr2_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr2_el0> */
	{"pmevcntr3_el0", {57155, "pmevcntr3_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr3_el0> */
	{"pmevcntr4_el0", {57156, "pmevcntr4_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr4_el0> */
	{"pmevcntr5_el0", {57157, "pmevcntr5_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr5_el0> */
	{"pmevcntr6_el0", {57158, "pmevcntr6_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr6_el0> */
	{"pmevcntr7_el0", {57159, "pmevcntr7_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr7_el0> */
	{"pmevcntr8_el0", {57160, "pmevcntr8_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr8_el0> */
	{"pmevcntr9_el0", {57161, "pmevcntr9_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr9_el0> */
	{"pmevcntr10_el0", {57162, "pmevcntr10_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr10_el0> */
	{"pmevcntr11_el0", {57163, "pmevcntr11_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr11_el0> */
	{"pmevcntr12_el0", {57164, "pmevcntr12_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr12_el0> */
	{"pmevcntr13_el0", {57165, "pmevcntr13_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr13_el0> */
	{"pmevcntr14_el0", {57166, "pmevcntr14_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr14_el0> */
	{"pmevcntr15_el0", {57167, "pmevcntr15_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr15_el0> */
	{"pmevcntr16_el0", {57168, "pmevcntr16_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr16_el0> */
	{"pmevcntr17_el0", {57169, "pmevcntr17_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr17_el0> */
	{"pmevcntr18_el0", {57170, "pmevcntr18_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr18_el0> */
	{"pmevcntr19_el0", {57171, "pmevcntr19_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr19_el0> */
	{"pmevcntr20_el0", {57172, "pmevcntr20_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr20_el0> */
	{"pmevcntr21_el0", {57173, "pmevcntr21_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr21_el0> */
	{"pmevcntr22_el0", {57174, "pmevcntr22_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr22_el0> */
	{"pmevcntr23_el0", {57175, "pmevcntr23_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr23_el0> */
	{"pmevcntr24_el0", {57176, "pmevcntr24_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr24_el0> */
	{"pmevcntr25_el0", {57177, "pmevcntr25_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr25_el0> */
	{"pmevcntr26_el0", {57178, "pmevcntr26_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr26_el0> */
	{"pmevcntr27_el0", {57179, "pmevcntr27_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr27_el0> */
	{"pmevcntr28_el0", {57180, "pmevcntr28_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr28_el0> */
	{"pmevcntr29_el0", {57181, "pmevcntr29_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr29_el0> */
	{"pmevcntr30_el0", {57182, "pmevcntr30_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevcntr30_el0> */
	{"pmevtyper0_el0", {57184, "pmevtyper0_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper0_el0> */
	{"pmevtyper1_el0", {57185, "pmevtyper1_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper1_el0> */
	{"pmevtyper2_el0", {57186, "pmevtyper2_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper2_el0> */
	{"pmevtyper3_el0", {57187, "pmevtyper3_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper3_el0> */
	{"pmevtyper4_el0", {57188, "pmevtyper4_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper4_el0> */
	{"pmevtyper5_el0", {57189, "pmevtyper5_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper5_el0> */
	{"pmevtyper6_el0", {57190, "pmevtyper6_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper6_el0> */
	{"pmevtyper7_el0", {57191, "pmevtyper7_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper7_el0> */
	{"pmevtyper8_el0", {57192, "pmevtyper8_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper8_el0> */
	{"pmevtyper9_el0", {57193, "pmevtyper9_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper9_el0> */
	{"pmevtyper10_el0", {57194, "pmevtyper10_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper10_el0> */
	{"pmevtyper11_el0", {57195, "pmevtyper11_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper11_el0> */
	{"pmevtyper12_el0", {57196, "pmevtyper12_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper12_el0> */
	{"pmevtyper13_el0", {57197, "pmevtyper13_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper13_el0> */
	{"pmevtyper14_el0", {57198, "pmevtyper14_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper14_el0> */
	{"pmevtyper15_el0", {57199, "pmevtyper15_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper15_el0> */
	{"pmevtyper16_el0", {57200, "pmevtyper16_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper16_el0> */
	{"pmevtyper17_el0", {57201, "pmevtyper17_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper17_el0> */
	{"pmevtyper18_el0", {57202, "pmevtyper18_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper18_el0> */
	{"pmevtyper19_el0", {57203, "pmevtyper19_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper19_el0> */
	{"pmevtyper20_el0", {57204, "pmevtyper20_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper20_el0> */
	{"pmevtyper21_el0", {57205, "pmevtyper21_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper21_el0> */
	{"pmevtyper22_el0", {57206, "pmevtyper22_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper22_el0> */
	{"pmevtyper23_el0", {57207, "pmevtyper23_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper23_el0> */
	{"pmevtyper24_el0", {57208, "pmevtyper24_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper24_el0> */
	{"pmevtyper25_el0", {57209, "pmevtyper25_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper25_el0> */
	{"pmevtyper26_el0", {57210, "pmevtyper26_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper26_el0> */
	{"pmevtyper27_el0", {57211, "pmevtyper27_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper27_el0> */
	{"pmevtyper28_el0", {57212, "pmevtyper28_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper28_el0> */
	{"pmevtyper29_el0", {57213, "pmevtyper29_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper29_el0> */
	{"pmevtyper30_el0", {57214, "pmevtyper30_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmevtyper30_el0> */
	{"pmccfiltr_el0", {57215, "pmccfiltr_el0", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmccfiltr_el0> */
	{"vpidr_el2", {57344, "vpidr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vpidr_el2> */
	{"vmpidr_el2", {57349, "vmpidr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vmpidr_el2> */
	{"sctlr_el2", {57472, "sctlr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in sctlr_el2> */
	{"actlr_el2", {57473, "actlr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in actlr_el2> */
	{"hcr_el2", {57480, "hcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in hcr_el2> */
	{"mdcr_el2", {57481, "mdcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mdcr_el2> */
	{"cptr_el2", {57482, "cptr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cptr_el2> */
	{"hstr_el2", {57483, "hstr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in hstr_el2> */
	{"hacr_el2", {57487, "hacr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in hacr_el2> */
	{"trfcr_el2", {57489, "trfcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in trfcr_el2> */
	{"sder32_el2", {57497, "sder32_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in sder32_el2> */
	{"ttbr0_el2", {57600, "ttbr0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr0_el2> */
	{"ttbr1_el2", {57601, "ttbr1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr1_el2> */
	{"tcr_el2", {57602, "tcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in tcr_el2> */
	{"vttbr_el2", {57608, "vttbr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vttbr_el2> */
	{"vtcr_el2", {57610, "vtcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vtcr_el2> */
	{"vncr_el2", {57616, "vncr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vncr_el2> */
	{"vsttbr_el2", {57648, "vsttbr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vsttbr_el2> */
	{"vstcr_el2", {57650, "vstcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vstcr_el2> */
	{"dacr32_el2", {57728, "dacr32_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in dacr32_el2> */
	{"spsr_el2", {57856, "spsr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_el2> */
	{"elr_el2", {57857, "elr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in elr_el2> */
	{"sp_el1", {57864, "sp_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in sp_el1> */
	{"spsr_irq", {57880, "spsr_irq", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_irq> */
	{"spsr_abt", {57881, "spsr_abt", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_abt> */
	{"spsr_und", {57882, "spsr_und", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_und> */
	{"spsr_fiq", {57883, "spsr_fiq", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_fiq> */
	{"ifsr32_el2", {57985, "ifsr32_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ifsr32_el2> */
	{"afsr0_el2", {57992, "afsr0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr0_el2> */
	{"afsr1_el2", {57993, "afsr1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr1_el2> */
	{"esr_el2", {58000, "esr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in esr_el2> */
	{"vsesr_el2", {58003, "vsesr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vsesr_el2> */
	{"fpexc32_el2", {58008, "fpexc32_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in fpexc32_el2> */
	{"tfsr_el2", {58032, "tfsr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in tfsr_el2> */
	{"far_el2", {58112, "far_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in far_el2> */
	{"hpfar_el2", {58116, "hpfar_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in hpfar_el2> */
	{"pmscr_el2", {58568, "pmscr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmscr_el2> */
	{"mair_el2", {58640, "mair_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mair_el2> */
	{"amair_el2", {58648, "amair_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in amair_el2> */
	{"mpamhcr_el2", {58656, "mpamhcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamhcr_el2> */
	{"mpamvpmv_el2", {58657, "mpamvpmv_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpmv_el2> */
	{"mpam2_el2", {58664, "mpam2_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpam2_el2> */
	{"mpamvpm0_el2", {58672, "mpamvpm0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm0_el2> */
	{"mpamvpm1_el2", {58673, "mpamvpm1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm1_el2> */
	{"mpamvpm2_el2", {58674, "mpamvpm2_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm2_el2> */
	{"mpamvpm3_el2", {58675, "mpamvpm3_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm3_el2> */
	{"mpamvpm4_el2", {58676, "mpamvpm4_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm4_el2> */
	{"mpamvpm5_el2", {58677, "mpamvpm5_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm5_el2> */
	{"mpamvpm6_el2", {58678, "mpamvpm6_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm6_el2> */
	{"mpamvpm7_el2", {58679, "mpamvpm7_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpamvpm7_el2> */
	{"vbar_el2", {58880, "vbar_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vbar_el2> */
	{"rmr_el2", {58882, "rmr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in rmr_el2> */
	{"vdisr_el2", {58889, "vdisr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in vdisr_el2> */
	{"ich_ap0r0_el2", {58944, "ich_ap0r0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap0r0_el2> */
	{"ich_ap0r1_el2", {58945, "ich_ap0r1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap0r1_el2> */
	{"ich_ap0r2_el2", {58946, "ich_ap0r2_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap0r2_el2> */
	{"ich_ap0r3_el2", {58947, "ich_ap0r3_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap0r3_el2> */
	{"ich_ap1r0_el2", {58952, "ich_ap1r0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap1r0_el2> */
	{"ich_ap1r1_el2", {58953, "ich_ap1r1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap1r1_el2> */
	{"ich_ap1r2_el2", {58954, "ich_ap1r2_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap1r2_el2> */
	{"ich_ap1r3_el2", {58955, "ich_ap1r3_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_ap1r3_el2> */
	{"ich_vseir_el2", {58956, "ich_vseir_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_vseir_el2> */
	{"icc_sre_el2", {58957, "icc_sre_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_sre_el2> */
	{"ich_hcr_el2", {58968, "ich_hcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_hcr_el2> */
	{"ich_misr_el2", {58970, "ich_misr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_misr_el2> */
	{"ich_vmcr_el2", {58975, "ich_vmcr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_vmcr_el2> */
	{"ich_lr0_el2", {58976, "ich_lr0_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr0_el2> */
	{"ich_lr1_el2", {58977, "ich_lr1_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr1_el2> */
	{"ich_lr2_el2", {58978, "ich_lr2_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr2_el2> */
	{"ich_lr3_el2", {58979, "ich_lr3_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr3_el2> */
	{"ich_lr4_el2", {58980, "ich_lr4_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr4_el2> */
	{"ich_lr5_el2", {58981, "ich_lr5_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr5_el2> */
	{"ich_lr6_el2", {58982, "ich_lr6_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr6_el2> */
	{"ich_lr7_el2", {58983, "ich_lr7_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr7_el2> */
	{"ich_lr8_el2", {58984, "ich_lr8_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr8_el2> */
	{"ich_lr9_el2", {58985, "ich_lr9_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr9_el2> */
	{"ich_lr10_el2", {58986, "ich_lr10_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr10_el2> */
	{"ich_lr11_el2", {58987, "ich_lr11_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr11_el2> */
	{"ich_lr12_el2", {58988, "ich_lr12_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr12_el2> */
	{"ich_lr13_el2", {58989, "ich_lr13_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr13_el2> */
	{"ich_lr14_el2", {58990, "ich_lr14_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr14_el2> */
	{"ich_lr15_el2", {58991, "ich_lr15_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in ich_lr15_el2> */
	{"contextidr_el2", {59009, "contextidr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in contextidr_el2> */
	{"tpidr_el2", {59010, "tpidr_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in tpidr_el2> */
	{"scxtnum_el2", {59015, "scxtnum_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in scxtnum_el2> */
	{"cntvoff_el2", {59139, "cntvoff_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntvoff_el2> */
	{"cnthctl_el2", {59144, "cnthctl_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthctl_el2> */
	{"cnthp_tval_el2", {59152, "cnthp_tval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthp_tval_el2> */
	{"cnthp_ctl_el2", {59153, "cnthp_ctl_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthp_ctl_el2> */
	{"cnthp_cval_el2", {59154, "cnthp_cval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthp_cval_el2> */
	{"cnthv_tval_el2", {59160, "cnthv_tval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthv_tval_el2> */
	{"cnthv_ctl_el2", {59161, "cnthv_ctl_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthv_ctl_el2> */
	{"cnthv_cval_el2", {59162, "cnthv_cval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthv_cval_el2> */
	{"cnthvs_tval_el2", {59168, "cnthvs_tval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthvs_tval_el2> */
	{"cnthvs_ctl_el2", {59169, "cnthvs_ctl_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthvs_ctl_el2> */
	{"cnthvs_cval_el2", {59170, "cnthvs_cval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthvs_cval_el2> */
	{"cnthps_tval_el2", {59176, "cnthps_tval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthps_tval_el2> */
	{"cnthps_ctl_el2", {59177, "cnthps_ctl_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthps_ctl_el2> */
	{"cnthps_cval_el2", {59178, "cnthps_cval_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in cnthps_cval_el2> */
	{"sctlr_el12", {59520, "sctlr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in sctlr_el12> */
	{"cpacr_el12", {59522, "cpacr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in cpacr_el12> */
	{"trfcr_el12", {59537, "trfcr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in trfcr_el12> */
	{"ttbr0_el12", {59648, "ttbr0_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr0_el12> */
	{"ttbr1_el12", {59649, "ttbr1_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr1_el12> */
	{"tcr_el12", {59650, "tcr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in tcr_el12> */
	{"spsr_el12", {59904, "spsr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_el12> */
	{"elr_el12", {59905, "elr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in elr_el12> */
	{"afsr0_el12", {60040, "afsr0_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr0_el12> */
	{"afsr1_el12", {60041, "afsr1_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr1_el12> */
	{"esr_el12", {60048, "esr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in esr_el12> */
	{"tfsr_el12", {60080, "tfsr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in tfsr_el12> */
	{"far_el12", {60160, "far_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in far_el12> */
	{"pmscr_el12", {60616, "pmscr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in pmscr_el12> */
	{"mair_el12", {60688, "mair_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in mair_el12> */
	{"amair_el12", {60696, "amair_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in amair_el12> */
	{"mpam1_el12", {60712, "mpam1_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpam1_el12> */
	{"vbar_el12", {60928, "vbar_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in vbar_el12> */
	{"contextidr_el12", {61057, "contextidr_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in contextidr_el12> */
	{"scxtnum_el12", {61063, "scxtnum_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in scxtnum_el12> */
	{"cntkctl_el12", {61192, "cntkctl_el12", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntkctl_el12> */
	{"cntp_tval_el02", {61200, "cntp_tval_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_tval_el02> */
	{"cntp_ctl_el02", {61201, "cntp_ctl_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_ctl_el02> */
	{"cntp_cval_el02", {61202, "cntp_cval_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntp_cval_el02> */
	{"cntv_tval_el02", {61208, "cntv_tval_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_tval_el02> */
	{"cntv_ctl_el02", {61209, "cntv_ctl_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_ctl_el02> */
	{"cntv_cval_el02", {61210, "cntv_cval_el02", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntv_cval_el02> */
	{"sctlr_el3", {61568, "sctlr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in sctlr_el3> */
	{"actlr_el3", {61569, "actlr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in actlr_el3> */
	{"scr_el3", {61576, "scr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in scr_el3> */
	{"sder32_el3", {61577, "sder32_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in sder32_el3> */
	{"cptr_el3", {61578, "cptr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in cptr_el3> */
	{"mdcr_el3", {61593, "mdcr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in mdcr_el3> */
	{"ttbr0_el3", {61696, "ttbr0_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in ttbr0_el3> */
	{"tcr_el3", {61698, "tcr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in tcr_el3> */
	{"spsr_el3", {61952, "spsr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in spsr_el3> */
	{"elr_el3", {61953, "elr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in elr_el3> */
	{"sp_el2", {61960, "sp_el2", 0, 8, 0}}, /* <reg: size 8, offset 0 in sp_el2> */
	{"afsr0_el3", {62088, "afsr0_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr0_el3> */
	{"afsr1_el3", {62089, "afsr1_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in afsr1_el3> */
	{"esr_el3", {62096, "esr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in esr_el3> */
	{"tfsr_el3", {62128, "tfsr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in tfsr_el3> */
	{"far_el3", {62208, "far_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in far_el3> */
	{"mair_el3", {62736, "mair_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in mair_el3> */
	{"amair_el3", {62744, "amair_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in amair_el3> */
	{"mpam3_el3", {62760, "mpam3_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in mpam3_el3> */
	{"vbar_el3", {62976, "vbar_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in vbar_el3> */
	{"rmr_el3", {62978, "rmr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in rmr_el3> */
	{"icc_ctlr_el3", {63076, "icc_ctlr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_ctlr_el3> */
	{"icc_sre_el3", {63077, "icc_sre_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_sre_el3> */
	{"icc_igrpen1_el3", {63079, "icc_igrpen1_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in icc_igrpen1_el3> */
	{"tpidr_el3", {63106, "tpidr_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in tpidr_el3> */
	{"scxtnum_el3", {63111, "scxtnum_el3", 0, 8, 0}}, /* <reg: size 8, offset 0 in scxtnum_el3> */
	{"cntps_tval_el1", {65296, "cntps_tval_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntps_tval_el1> */
	{"cntps_ctl_el1", {65297, "cntps_ctl_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntps_ctl_el1> */
	{"cntps_cval_el1", {65298, "cntps_cval_el1", 0, 8, 0}}, /* <reg: size 8, offset 0 in cntps_cval_el1> */
	{"unknown_catchall", {65300, "unknown_catchall", 0, 8, 0}}, /* <reg: size 8, offset 0 in unknown_catchall> */
	{"syscall_info", {65302, "syscall_info", 0, 4, 0}}, /* <reg: size 4, offset 0 in syscall_info> */
};

string stack_reg_name = "sp";
bool is_link_reg_arch = true;
string link_reg_name = "x30";
