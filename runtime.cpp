
#include <string>
#include <vector>
#include <map>
using namespace std;

#include <stdint.h>

#include "runtime.h"

#define DEBUG_RUNTIME_ALL
//#define DEBUG_RUNTIME_SETS
//#define DEBUG_RUNTIME_STACK

#define debug(...) while(0);
#define debug_set(...) while(0);
#define debug_stack(...) while(0);

#if defined(DEBUG_RUNTIME_ALL)
	#define debug printf
#endif

#if defined(DEBUG_RUNTIME_SETS) || defined(DEBUG_RUNTIME_ALL)
	#define debug_set printf
#endif

#if defined(DEBUG_RUNTIME_STACK) || defined(DEBUG_RUNTIME_ALL)
	#define debug_stack printf
#endif

/* the foo_il.c must export this, else we can't implement PUSH */
extern string stackRegName;
extern map<string,struct RegisterInfo> regInfos;

/* VM components */
uint8_t vm_mem[VM_MEM_SZ];
map<string,REGTYPE> vm_regs;
map<string,REGTYPE> vm_regs_temp;
map<string,int> vm_flags;

/*****************************************************************************/
/* local helpers */
/*****************************************************************************/

/* access core registers file, taking into account possible subregister
	relationships */
static REGTYPE reg_core_get_value(string regName)
{
	REGTYPE result;

	/* core registers must consider full-width vs. sub registers */
	RegisterInfo ri = regInfos[regName];
	/* full width */
	if(ri.full_width_reg == regName) {
		result = vm_regs[regName];
		//debug("%s(): %s is full-width, value=" FMT_REG "\n", __func__, regName.c_str(), result);
	}
	/* sub register */
	else {
		REGTYPE fwr = vm_regs[ri.full_width_reg];
		int shift = 8*ri.offset;
		REGTYPE mask = ((REGTYPE)1 << 8*(ri.size))-1;
		result = (fwr >> shift) & mask;
		//debug("%s(): %s is subreg, (" FMT_REG ">>%d) & " FMT_REG " == " FMT_REG "\n",
		//	__func__, regName.c_str(), fwr, shift, mask, result);
	}

	return result;
}

static REGTYPE reg_get_value(string regName)
{
	REGTYPE result;

	/* temp registers simply come from the temp regs file */
	if(regName.rfind("temp",0) == 0) {
		result = vm_regs_temp[regName];
	}
	/* core registers must consider full-width vs. sub registers */
	else {
		result = reg_core_get_value(regName);
	}

	return result;
}

/* access core registers file, taking into account possible subregister
	relationships */
static void reg_core_set_value(string regName, REGTYPE value)
{
	RegisterInfo ri = regInfos[regName];

	if(ri.full_width_reg == regName) {
		//debug("%s is a full-width reg, setting to " FMT_REG "\n",
		//	regName.c_str(), value);
		vm_regs[regName] = value;
	}
	/* sub register */
	else {
		int shift = 8*ri.offset;
		REGTYPE mask = (((REGTYPE)1 << 8*(ri.size))-1) << shift;

		REGTYPE tmp = vm_regs[ri.full_width_reg];
		tmp &= ~mask; /* clear bits in area */
		tmp |= (value << shift); /* bring in the value */
		vm_regs[ri.full_width_reg] = tmp;
		//debug("%s is subreg, doing (offset=%d shift=%d mask=" FMT_REG ") into %s = " FMT_REG "\n",
		//	regName.c_str(), ri.offset, shift, mask, ri.full_width_reg.c_str(), tmp);
	}
}

static void reg_set_value(string regName, REGTYPE value)
{
	/* temp registers simply come from the temp regs file */
	if(regName.rfind("temp", 0) == 0) {
		vm_regs_temp[regName] = value;
	}
	/* core registers must consider full-width vs. sub registers */
	else {
		reg_core_set_value(regName, value);
	}
}

/*****************************************************************************/
/* operations */
/*****************************************************************************/

/* LowLevelILOperation.LLIL_NOP: [] */
void NOP(void)
{
	return;
}

/* LowLevelILOperation.LLIL_SET_REG: [("dest", "reg"), ("src", "expr")] */
void SET_REG1(string dest, uint8_t src)
{
	reg_set_value(dest, src);
	debug_set("SET_REG1        %s = 0x%02X\n", dest.c_str(), src);
}

void SET_REG2(string dest, uint16_t src)
{
	reg_set_value(dest, src);
	debug_set("SET_REG2        %s = 0x%04X\n", dest.c_str(), src);
}

void SET_REG4(string dest, uint32_t src)
{
	reg_set_value(dest, src);
	debug_set("SET_REG4        %s = 0x%08X\n", dest.c_str(), src);
}

void SET_REG8(string dest, uint64_t src)
{
	reg_set_value(dest, src);
	debug_set("SET_REG8        %s = 0x%016llX\n", dest.c_str(), src);
}

/* LowLevelILOperation.LLIL_SET_REG_SPLIT: [("hi", "reg"), ("lo", "reg"), ("src", "expr")] */
void SET_REG_SPLIT(string hi, string lo, REGTYPE src_val)
{
	REGTYPE dst_val_hi = (REGTYPE) (src_val & REGMASKHIHALF) >> (REGWIDTH/2);
	REGTYPE dst_val_lo = (REGTYPE) (src_val & REGMASKLOHALF);
	reg_set_value(hi, dst_val_hi);
	reg_set_value(lo, dst_val_lo);
	debug_set("SET_REG_SPLIT   " FMT_REG " -> %s = " FMT_REG ", %s = " FMT_REG "\n",
		src_val, hi.c_str(), dst_val_hi, lo.c_str(), dst_val_lo);
}

/* LowLevelILOperation.LLIL_REG_SPLIT: [("hi", "reg"), ("lo", "reg")] */
/* better called "join" */
REGTYPE REG_SPLIT(string hi, string lo)
{
	REGTYPE src_hi = reg_get_value(hi);
	REGTYPE src_lo = reg_get_value(lo);
	REGTYPE result = (src_hi << (REGWIDTH/2)) | (src_lo & REGMASKLOHALF);

	debug("REG_SPLIT       " FMT_REG " join " FMT_REG " -> " FMT_REG "\n",
		src_hi, src_lo, result);

	return result;
}

/* LowLevelILOperation.LLIL_SET_REG_STACK_REL: [("stack", "reg_stack"), ("dest", "expr"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_PUSH: [("stack", "reg_stack"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_SET_FLAG: [("dest", "flag"), ("src", "expr")] */
void SET_FLAG(string left, bool right)
{
	vm_flags[left] = right;
	debug_set("SET_FLAG        %s = %d\n", left.c_str(), right);
}

/* LowLevelILOperation.LLIL_LOAD: [("src", "expr")] */
uint8_t LOAD1(REGTYPE expr)
{
	uint8_t result = vm_mem[expr];
	debug("LOAD1           0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint16_t LOAD2(REGTYPE expr)
{
	uint16_t result = *(uint16_t *)(vm_mem + expr);
	debug("LOAD2           0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint32_t LOAD4(REGTYPE expr)
{
	uint32_t result = *(uint32_t *)(vm_mem + expr);
	debug("LOAD4           0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint64_t LOAD8(REGTYPE expr)
{
	uint64_t result = *(uint64_t *)(vm_mem + expr);
	debug("LOAD8           0x%llX = mem[" FMT_REG "]\n", result, expr);
	return result;
}

/* LowLevelILOperation.LLIL_STORE: [("dest", "expr"), ("src", "expr")] */
void STORE1(REGTYPE dest, uint8_t src)
{
	debug("STORE1          byte[" FMT_REG "] = 0x%02X\n", dest, src);
	*(uint8_t *)(vm_mem + dest) = src;
}

void STORE2(REGTYPE dest, uint16_t src)
{
	debug("STORE2          word[" FMT_REG "] = 0x%04X\n", dest, src);
	*(uint16_t *)(vm_mem + dest) = src;
}

void STORE4(REGTYPE dest, uint32_t src)
{
	debug("STORE4          dword[" FMT_REG "] = 0x%08X\n", dest, src);
	*(uint32_t *)(vm_mem + dest) = src;
}

void STORE8(REGTYPE dest, uint64_t src)
{
	debug("STORE8          qword[" FMT_REG "] = 0x%016llX\n", dest, src);
	*(uint64_t *)(vm_mem + dest) = src;
}

/* LowLevelILOperation.LLIL_PUSH: [("src", "expr")] */
void PUSH(REGTYPE src)
{
	/* decrement stack pointer */
	vm_regs[stackRegName] -= sizeof(REGTYPE);
	/* store on stack */
	REGTYPE ea = vm_regs[stackRegName];
	debug_stack("PUSH            mem[" FMT_REG "] = " FMT_REG "\n", ea, src);
	*(REGTYPE *)(vm_mem + ea) = src;
}

/* LowLevelILOperation.LLIL_POP: [] */
REGTYPE POP(void)
{
	/* retrieve from stack */
	REGTYPE ea = vm_regs[stackRegName];
	REGTYPE val = *(REGTYPE *)(vm_mem + ea);
	debug_stack("POP             " FMT_REG " = mem[" FMT_REG "]\n", val, ea);
	/* increment stack pointer */
	vm_regs[stackRegName] += sizeof(REGTYPE);
	return val;
}

/* LowLevelILOperation.LLIL_REG: [("src", "reg")] */
REGTYPE REG(string src)
{
	REGTYPE result = reg_get_value(src);
	debug("REG             " FMT_REG " = %s\n", result, src.c_str());
	return result;
}

/* LowLevelILOperation.LLIL_REG_STACK_REL: [("stack", "reg_stack"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_POP: [("stack", "reg_stack")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_REG: [("dest", "reg")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_REL: [("stack", "reg_stack"), ("dest", "expr")] */
/* LowLevelILOperation.LLIL_CONST: [("constant", "int")] */
/* LowLevelILOperation.LLIL_CONST_PTR: [("constant", "int")] */
/* LowLevelILOperation.LLIL_EXTERN_PTR: [("constant", "int"), ("offset", "int")] */
SREGTYPE EXTERN_PTR(SREGTYPE constant, SREGTYPE offset)
{
	return constant + offset;
}

/* LowLevelILOperation.LLIL_FLOAT_CONST: [("constant", "float")] */
/* LowLevelILOperation.LLIL_FLAG: [("src", "flag")] */
bool FLAG(string src)
{
	bool result = vm_flags[src];
	debug("FLAG            " "%d = vm_flags[%s]\n", result, src.c_str());
	return result;
}

/* LowLevelILOperation.LLIL_FLAG_BIT: [("src", "flag"), ("bit", "int")] */

/* LowLevelILOperation.LLIL_ADD: [("left", "expr"), ("right", "expr")] */
uint8_t ADD1(uint8_t left, uint8_t right)
{
	uint8_t result = left + right;
	debug("ADD1            0x%02X = 0x%02X + 0x%02X\n", result & 0xFF, left & 0xFF, right & 0xFF);
	return result;
}

uint16_t ADD2(uint16_t left, uint16_t right)
{
	uint16_t result = left + right;
	debug("ADD2            0x%04X = 0x%04X + 0x%04X\n", result & 0xFFFF, left & 0xFFFF, right & 0xFFFF);
	return result;
}

uint32_t ADD4(uint32_t left, uint32_t right)
{
	uint32_t result = left + right;
	debug("ADD4            0x%08X = 0x%08X + 0x%08X\n", result, left, right);
	return result;
}

uint64_t ADD8(uint64_t left, uint64_t right)
{
	uint64_t result = left + right;
	debug("ADD8            0x%016llX = 0x%016llX + 0x%016llX\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_ADC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
SREGTYPE ADC(SREGTYPE left, SREGTYPE right, bool carry)
{
	SREGTYPE result = left + right + carry;
	debug("ADC             " FMT_REG " = " FMT_REG " + " FMT_REG " + %d\n", result, left, right, carry);
	return result;
}

/* LowLevelILOperation.LLIL_SUB: [("left", "expr"), ("right", "expr")] */
uint8_t SUB1(uint8_t a, uint8_t b)
{
	uint8_t result = a - b;
	debug("SUB1            0x%02X = 0x%02X - 0x%02X\n", result, a, b);
	return result;
}

uint16_t SUB2(uint16_t a, uint16_t b)
{
	uint16_t result = a - b;
	debug("SUB2            0x%04X = 0x%04X - 0x%04X\n", result, a, b);
	return result;
}

uint32_t SUB4(uint32_t a, uint32_t b)
{
	uint32_t result = a - b;
	debug("SUB4            0x%08X = 0x%08X - 0x%08X\n", result, a, b);
	return result;
}

uint64_t SUB8(uint64_t a, uint64_t b)
{
	uint64_t result = a - b;
	debug("SUB8            0x%016llX = 0x%016llX - 0x%016llX\n", result, a, b);
	return result;
}

/* LowLevelILOperation.LLIL_SBB: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t SBB1(uint8_t a, uint8_t b, uint8_t c)
{
	uint8_t result = a - b - c;
	debug("SBB1            0x%02X = 0x%02X - 0x%02X - %d\n", result, a, b, c);
	return result;
}

uint16_t SBB2(uint16_t a, uint16_t b, uint16_t c)
{
	uint16_t result = a - b - c;
	debug("SBB2            0x%04X = 0x%04X - 0x%04X - %d\n", result, a, b, c);
	return result;
}

uint32_t SBB4(uint32_t a, uint32_t b, uint32_t c)
{
	uint32_t result = a - b - c;
	debug("SBB4            0x%08X = 0x%08X - 0x%08X - %d\n", result, a, b, c);
	return result;
}

uint64_t SBB8(uint64_t a, uint64_t b, uint64_t c)
{
	uint64_t result = a - b - c;
	debug("SBB8            0x%016llX = 0x%016llX - 0x%016llX - %lld\n", result, a, b, c);
	return result;
}

/* LowLevelILOperation.LLIL_AND: [("left", "expr"), ("right", "expr")] */
REGTYPE AND(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left & right;
	debug("AND             " FMT_REG " = " FMT_REG " & " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_OR: [("left", "expr"), ("right", "expr")] */
REGTYPE OR(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left | right;
	debug("OR              " FMT_REG " = " FMT_REG " | " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_XOR: [("left", "expr"), ("right", "expr")] */
REGTYPE XOR(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left ^ right;
	debug("XOR             " FMT_REG " = " FMT_REG " ^ " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_LSL: [("left", "expr"), ("right", "expr")] */
REGTYPE LSL(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left << right;
	debug("LSL             " FMT_REG " = " FMT_REG " << " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_LSR: [("left", "expr"), ("right", "expr")] */

/* LowLevelILOperation.LLIL_ASR: [("left", "expr"), ("right", "expr")] */
SREGTYPE ASR(SREGTYPE left, REGTYPE right)
{
	/* recall: ARITHMETIC shift preseves sign bit - hope the compiler generates correct code :) */
	SREGTYPE result = left >> right;
	debug("ASR             " FMT_REG " = " FMT_REG " >> " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_ROL: [("left", "expr"), ("right", "expr")] */
uint8_t ROL1(uint8_t value, uint8_t amt)
{
	amt = amt % 8;
	uint8_t result = (value << amt) | (value >> (8-amt));
	debug("ROL1(0x%02X, %d) returns 0x%02X\n", value, amt, result);
	return result;
}

uint16_t ROL2(uint16_t value, uint16_t amt)
{
	amt = amt % 16;
	uint16_t result = (value << amt) | (value >> (16-amt));
	debug("ROL2(0x%04X, %d) returns 0x%04X\n", value, amt, result);
	return result;
}

uint32_t ROL4(uint32_t value, uint32_t amt)
{
	amt = amt % 32;
	uint32_t result = (value << amt) | (value >> (8-amt));
	debug("ROL4(0x%08X, %d) returns 0x%08X\n", value, amt, result);
	return result;
}

uint64_t ROL8(uint64_t value, uint64_t amt)
{
	amt = amt % 64;
	uint64_t result = (value << amt) | (value >> (8-amt));
	debug("ROL8(0x%016llX, %lld) returns 0x%08llX\n", value, amt, result);
	return result;
}

/* LowLevelILOperation.LLIL_RLC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RLC1(uint8_t value, uint8_t amt, bool carry)
{
	uint8_t result = value;

	if(amt) {
		amt = amt % 8;
		// normal carry
		uint8_t a = (value << amt);
		uint8_t b = (value >> (8-amt));
		// insert c
		b = (b >> 1) | (carry << (amt-1));
		//
		result = a | b;
	}

	debug("RLC1            0x%X = 0x%X <<< %d and carry = %d\n", result, value, amt, carry);
	return result;
}

/* LowLevelILOperation.LLIL_ROR: [("left", "expr"), ("right", "expr")] */
uint8_t ROR1(uint8_t value, uint8_t amt)
{
	amt = amt % 8;
	uint8_t result = (value >> amt) | (value << (8-amt));
	debug("ROR1(0x%02X, %d) returns 0x%02X\n", value, amt, result);
	return result;
}

uint16_t ROR2(uint16_t value, uint16_t amt)
{
	amt = amt % 16;
	uint16_t result = (value >> amt) | (value << (16-amt));
	debug("ROR2(0x%04X, %d) returns 0x%04X\n", value, amt, result);
	return result;
}

uint32_t ROR4(uint32_t value, uint32_t amt)
{
	amt = amt % 32;
	uint32_t result = (value >> amt) | (value << (8-amt));
	debug("ROR4(0x%08X, %d) returns 0x%08X\n", value, amt, result);
	return result;
}

uint64_t ROR8(uint64_t value, uint64_t amt)
{
	amt = amt % 64;
	uint64_t result = (value >> amt) | (value << (8-amt));
	debug("ROR8(0x%016llX, %lld) returns 0x%016llX\n", value, amt, result);
	return result;
}

/* LowLevelILOperation.LLIL_RRC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RRC1(uint8_t value, uint8_t amt, bool carry)
{
	uint8_t result = value;

	if(amt) {
		amt = amt % 8;
		// normal carry
		uint8_t a = (value >> amt);
		uint8_t b = (value << (8-amt));
		// insert c
		b = (b << 1) | (carry >> (amt-1));
		//
		result = a | b;
	}

	debug("RRC1            0x%X = 0x%X >>> %d and carry = %d\n", result, value, amt, carry);
	return result;
}

SREGTYPE MUL(SREGTYPE left, SREGTYPE right)
{
	SREGTYPE result = left * right;
	debug("MUL             " FMT_REG " = " FMT_REG " * " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MULU_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_MULS_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVU: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVU_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVS: [("left", "expr"), ("right", "expr")] */

/* LowLevelILOperation.LLIL_DIVS_DP: [("left", "expr"), ("right", "expr")] */
// TODO: figure out "DP"
SREGTYPE DIVS_DP(SREGTYPE left, SREGTYPE_HALF right)
{
	SREGTYPE result = left / right;
	debug("DIVS_DP         " FMT_SREG " = " FMT_SREG " / " FMT_REG_HALF "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MODU: [("left", "expr"), ("right", "expr")] */
REGTYPE MODU(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left % right;
	debug("MODU            " FMT_REG " = " FMT_REG " %% " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MODU_DP: [("left", "expr"), ("right", "expr")] */
// TODO: figure out what DP's supposed to do different
REGTYPE MODU_DP(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left % right;
	debug("MODU_DP         " FMT_REG " = " FMT_REG " %% " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MODS: [("left", "expr"), ("right", "expr")] */
SREGTYPE MODS(SREGTYPE left, SREGTYPE right)
{
	SREGTYPE result = left % right;
	debug("MODS            " FMT_SREG " = " FMT_SREG " %% " FMT_SREG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MODS_DP: [("left", "expr"), ("right", "expr")] */
// TODO: figure out what DP's supposed to do different
SREGTYPE MODS_DP(SREGTYPE left, SREGTYPE right)
{
	SREGTYPE result = left % right;
	debug("MODS_DP         " FMT_SREG " = " FMT_SREG " %% " FMT_SREG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_NEG: [("src", "expr")] */
uint8_t NEG1(uint8_t src)
{
    uint8_t result = (src ^ 0xFF) + 1;
	debug("NEG              0x%02X = neg(0x%02X)\n", result, src);
    return result;
}

uint16_t NEG2(uint16_t src)
{
    uint16_t result = (src ^ 0xFFFF) + 1;
	debug("NEG              0x%04X = neg(0x%04X)\n", result, src);
    return result;
}

uint32_t NEG4(uint32_t src)
{
    uint32_t result = (src ^ 0xFFFFFFFF) + 1;
	debug("NEG              0x%08X = neg(0x%08X)\n", result, src);
    return result;
}

uint64_t NEG8(uint64_t src)
{
    uint64_t result = (src ^ 0xFFFFFFFFFFFFFFFF) + 1;
	debug("NEG              0x%016llX = neg(0x%016llX)\n", result, src);
    return result;
}

/* LowLevelILOperation.LLIL_NOT: [("src", "expr")] */
uint8_t NOT0(uint8_t left)
{
	/* size 0 is special case which means treat as bool
		nonzero -> zero
		zero -> 1
	*/
	uint8_t result = left ^ 1;
	debug("NOT0            0x%02X = 0x%02X ^ 1\n", result, left);
	return result;
}

uint8_t NOT1(uint8_t left)
{
	uint8_t result = ~left;
	debug("NOT1            0x%02X = ~0x%02X\n", result, left);
	return result;
}

uint16_t NOT2(uint16_t left)
{
	uint16_t result = ~left;
	debug("NOT2            0x%04X = ~0x%04X\n", result, left);
	return result;
}

uint32_t NOT4(uint32_t left)
{
	uint32_t result = ~left;
	debug("NOT4            0x%08X = ~0x%08X\n", result, left);
	return result;
}

uint64_t NOT8(uint64_t left)
{
	uint64_t result = ~left;
	debug("NOT8            0x%016llX = ~0x%016llX\n", result, left);
	return result;
}

/* LowLevelILOperation.LLIL_SX: [("src", "expr")] */
SREGTYPE SX(SREGTYPE_HALF src)
{
	SREGTYPE result = src;
	debug("SX              " FMT_REG_HALF " -> " FMT_REG "\n", src, result);
	return (SREGTYPE)src;
}

/* LowLevelILOperation.LLIL_ZX: [("src", "expr")] */
uint32_t ZX4(uint8_t src)
{
	uint8_t result = src;
	debug("ZX4             0x%02X -> 0x%08X\n", src & 0xFF, result);
	return (SREGTYPE)src;
}

/* LowLevelILOperation.LLIL_LOW_PART: [("src", "expr")] */
uint8_t LOW_PART1(REGTYPE left)
{
	uint8_t result = left & 0xFF;
	debug("LOW_PART1       " FMT_REG " -> 0x%02X\n", left, result);
	return result;
}

uint16_t LOW_PART2(REGTYPE left)
{
	uint8_t result = left & 0xFFFF;
	debug("LOW_PART2       " FMT_REG " -> 0x%04X\n", left, result);
	return result;
}

/* LowLevelILOperation.LLIL_JUMP: [("dest", "expr")] */
void JUMP(REGTYPE dest)
{
	printf("ERROR: JUMP to " FMT_REG " is out of LLIL land, something went wrong in transpilation\n", dest);
	exit(-1);
}

/* LowLevelILOperation.LLIL_JUMP_TO: [("dest", "expr"), ("targets", "int_list")] */
/* LowLevelILOperation.LLIL_CALL: [("dest", "expr")] */
void CALL(REGTYPE dest, void (*pfunc)(void), const char *func_name)
{
	#define RUNTIME_CALLER_ADDR_DUMMY 0xAAAAAAAA
	/* dummy push of return address */
	vm_regs[stackRegName] -= sizeof(REGTYPE);
	*(REGTYPE *)(vm_mem + vm_regs[stackRegName]) = (REGTYPE)(RUNTIME_CALLER_ADDR_DUMMY & REGMASK);
	debug_stack("CALL            " FMT_REG "   mem[" FMT_REG "] = " FMT_REG " %s()\n",
		dest, vm_regs[stackRegName], RUNTIME_CALLER_ADDR_DUMMY, func_name);

	return pfunc();
}

/* LowLevelILOperation.LLIL_CALL_STACK_ADJUST: [("dest", "expr"), ("stack_adjustment", "int"), ("reg_stack_adjustments", "reg_stack_adjust")] */
/* LowLevelILOperation.LLIL_TAILCALL: [("dest", "expr")] */

void TAILCALL(REGTYPE dest, void (*pfunc)(void), const char *func_name)
{
	/* dummy push of return address */
	debug_stack("TAILCALL        " FMT_REG " %s()\n", dest, func_name);

	return pfunc();
}

/* LowLevelILOperation.LLIL_RET: [("dest", "expr")] */
void RET(REGTYPE dest)
{
	/* IL semantics of RET are _not_ necessarily to pop and jump (but can be)
		an x86 style ret will be RET(POP())
		an arm style ret might be RET(REG("lr")) */

	// DO NOT:
	// vm_regs[stackRegName] += sizeof(REGTYPE);
	debug_stack("RET             " FMT_REG "\n", dest);
}

/* LowLevelILOperation.LLIL_NORET: [] */
/* LowLevelILOperation.LLIL_IF: [("condition", "expr"), ("true", "int"), ("false", "int")] */
/* LowLevelILOperation.LLIL_GOTO: [("dest", "int")] */
/* LowLevelILOperation.LLIL_FLAG_COND: [("condition", "cond"), ("semantic_class", "sem_class")] */
/* LowLevelILOperation.LLIL_FLAG_GROUP: [("semantic_group", "sem_group")] */
/* LowLevelILOperation.LLIL_CMP_E: [("left", "expr"), ("right", "expr")] */
bool CMP_E(REGTYPE left, REGTYPE right)
{
	bool result = left == right;
	debug("CMP_E           %d = " FMT_REG " == " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_NE: [("left", "expr"), ("right", "expr")] */
bool CMP_NE(REGTYPE left, REGTYPE right)
{
	bool result = left != right;
	debug("CMP_NE          %d = " FMT_REG " != " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SLT: [("left", "expr"), ("right", "expr")] */
bool CMP_SLT1(int8_t left, int8_t right)
{
	bool result = left < right;
	debug("CMP_SLT1        %d = %d < %d\n", result, left, right);
	return result;
}

bool CMP_SLT2(int16_t left, int16_t right)
{
	bool result = left < right;
	debug("CMP_SLT2        %d = %d < %d\n", result, left, right);
	return result;
}

bool CMP_SLT4(int32_t left, int32_t right)
{
	bool result = left < right;
	debug("CMP_SLT4        %d = %d < %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_ULT: [("left", "expr"), ("right", "expr")] */
bool CMP_ULT(REGTYPE left, REGTYPE right)
{
	bool result = left < right;
	debug("CMP_ULT         %d = %d < %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SLE: [("left", "expr"), ("right", "expr")] */
bool CMP_SLE4(int32_t left, int32_t right)
{
	bool result = left <= right;
	debug("CMP_SLE         %d = %d <= %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_ULE: [("left", "expr"), ("right", "expr")] */
bool CMP_ULE(REGTYPE left, REGTYPE right)
{
	bool result = left <= right;
	debug("CMP_ULE         %d = " FMT_REG " <= " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SGE: [("left", "expr"), ("right", "expr")] */
bool CMP_SGE4(int32_t left, int32_t right)
{
	bool result = left >= right;
	debug("CMP_SGE         %d = %d >= %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_UGE: [("left", "expr"), ("right", "expr")] */
bool CMP_UGE(REGTYPE left, REGTYPE right)
{
	bool result = left >= right;
	debug("CMP_UGE         %d = " FMT_REG " >= " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SGT: [("left", "expr"), ("right", "expr")] */
bool CMP_SGT2(int16_t left, int16_t right)
{
	bool result = left > right;
	debug("CMP_SGT         %d = %d > %d\n", result, left, right);
	return result;
}

bool CMP_SGT4(int32_t left, int32_t right)
{
	bool result = left > right;
	debug("CMP_SGT         %d = %d > %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_UGT: [("left", "expr"), ("right", "expr")] */
bool CMP_UGT(REGTYPE left, REGTYPE right)
{
	bool result = left > right;
	debug("CMP_UGT         %d = " FMT_REG " > " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_TEST_BIT: [("left", "expr"), ("right", "expr")] */
bool TEST_BIT(REGTYPE value, REGTYPE mask)
{
	bool result = !!(value & mask);
	debug("TEST_BIT        %d = bool(" FMT_REG " & " FMT_REG ")\n", result, value, mask);
	return result;
}

/* LowLevelILOperation.LLIL_BOOL_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_ADD_OVERFLOW: [("left", "expr"), ("right", "expr")] */
bool ADD_OVERFLOW1(uint8_t a, uint8_t b)
{
	bool result = a >= 256 - b;
	debug("ADD_OVERFLOW1   %d (when %d + %d)\n", result, a, b);
	return result;
}

bool ADD_OVERFLOW2(uint16_t a, uint16_t b)
{
	bool result = a >= 65536 - b;
	debug("ADD_OVERFLOW2   %d (when %d + %d)\n", result, a, b);
	return result;
}

bool ADD_OVERFLOW4(uint32_t a, uint32_t b)
{
	bool result = a >= 4294967296 - b;
	debug("ADD_OVERFLOW4   %d (when %d + %d)\n", result, a, b);
	return result;
}

/* LowLevelILOperation.LLIL_SYSCALL: [] */
/* LowLevelILOperation.LLIL_INTRINSIC: [("output", "reg_or_flag_list"), ("intrinsic", "intrinsic"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_INTRINSIC_SSA: [("output", "reg_or_flag_ssa_list"), ("intrinsic", "intrinsic"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_BP: [] */
/* LowLevelILOperation.LLIL_TRAP: [("vector", "int")] */
/* LowLevelILOperation.LLIL_UNDEF: [] */

/* LowLevelILOperation.LLIL_UNIMPL: [] */
REGTYPE UNIMPL()
{
	debug("UNIMPL");
	printf("UNIMPLEMENTED!\n");
	exit(-1);
	return 0;
}

REGTYPE UNIMPL(REGTYPE)
{
	debug("UNIMPL");
	return 0;
}

/* LowLevelILOperation.LLIL_UNIMPL_MEM: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FADD: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FSUB: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FMUL: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FDIV: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FSQRT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FNEG: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FABS: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FLOAT_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_INT_TO_FLOAT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FLOAT_CONV: [("src", "expr")] */
/* LowLevelILOperation.LLIL_ROUND_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FLOOR: [("src", "expr")] */
/* LowLevelILOperation.LLIL_CEIL: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FTRUNC: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_E: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_NE: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_LT: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_LE: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_GE: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_GT: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_O: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_FCMP_UO: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_SET_REG_SSA: [("dest", "reg_ssa"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_SET_REG_SSA_PARTIAL: [("full_reg", "reg_ssa"), ("dest", "reg"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_SET_REG_SPLIT_SSA: [("hi", "expr"), ("lo", "expr"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_SET_REG_STACK_REL_SSA: [("stack", "expr"), ("dest", "expr"), ("top", "expr"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_SET_REG_STACK_ABS_SSA: [("stack", "expr"), ("dest", "reg"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_SPLIT_DEST_SSA: [("dest", "reg_ssa")] */
/* LowLevelILOperation.LLIL_REG_STACK_DEST_SSA: [("src", "reg_stack_ssa_dest_and_src")] */
/* LowLevelILOperation.LLIL_REG_SSA: [("src", "reg_ssa")] */
/* LowLevelILOperation.LLIL_REG_SSA_PARTIAL: [("full_reg", "reg_ssa"), ("src", "reg")] */
/* LowLevelILOperation.LLIL_REG_SPLIT_SSA: [("hi", "reg_ssa"), ("lo", "reg_ssa")] */
/* LowLevelILOperation.LLIL_REG_STACK_REL_SSA: [("stack", "reg_stack_ssa"), ("src", "expr"), ("top", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_ABS_SSA: [("stack", "reg_stack_ssa"), ("src", "reg")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_REL_SSA: [("stack", "expr"), ("dest", "expr"), ("top", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_ABS_SSA: [("stack", "expr"), ("dest", "reg")] */
/* LowLevelILOperation.LLIL_SET_FLAG_SSA: [("dest", "flag_ssa"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_FLAG_SSA: [("src", "flag_ssa")] */
/* LowLevelILOperation.LLIL_FLAG_BIT_SSA: [("src", "flag_ssa"), ("bit", "int")] */
/* LowLevelILOperation.LLIL_CALL_SSA: [("output", "expr"), ("dest", "expr"), ("stack", "expr"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_SYSCALL_SSA: [("output", "expr"), ("stack", "expr"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_TAILCALL_SSA: [("output", "expr"), ("dest", "expr"), ("stack", "expr"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_CALL_OUTPUT_SSA: [("dest_memory", "int"), ("dest", "reg_ssa_list")] */
/* LowLevelILOperation.LLIL_CALL_STACK_SSA: [("src", "reg_ssa"), ("src_memory", "int")] */
/* LowLevelILOperation.LLIL_CALL_PARAM: [("src", "expr_list")] */
/* LowLevelILOperation.LLIL_LOAD_SSA: [("src", "expr"), ("src_memory", "int")] */
/* LowLevelILOperation.LLIL_STORE_SSA: [("dest", "expr"), ("dest_memory", "int"), ("src_memory", "int"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_PHI: [("dest", "reg_ssa"), ("src", "reg_ssa_list")] */
/* LowLevelILOperation.LLIL_REG_STACK_PHI: [("dest", "reg_stack_ssa"), ("src", "reg_stack_ssa_list")] */
/* LowLevelILOperation.LLIL_FLAG_PHI: [("dest", "flag_ssa"), ("src", "flag_ssa_list")] */
/* LowLevelILOperation.LLIL_MEM_PHI: [("dest_memory", "int"), ("src_memory", "int_list")] */

void runtime_comment(const char *msg)
{
	#if defined(DEBUG_RUNTIME_ALL) || defined(DEBUG_RUNTIME_SETS)
	//printf("\x1B[36m%s\x1B[0m", msg);
	printf("\n%s", msg);
	printf("----------------\n");
	#endif
}

#ifdef ARCH_ARM
void __aeabi_idiv()
{
    SREGTYPE a = reg_get_value("r0");
    SREGTYPE b = reg_get_value("r1");
    SREGTYPE result = a / b;
    reg_set_value("r0", result);
	debug("__aeabi_idiv() returns " FMT_SREG " = " FMT_SREG " / " FMT_SREG "\n", result, a, b);
}

void __aeabi_idivmod()
{
    SREGTYPE a = reg_get_value("r0");
    SREGTYPE b = reg_get_value("r1");
    SREGTYPE result = a % b;
    reg_set_value("r0", result);
	debug("__aeabi_idivmod() returns " FMT_SREG " = " FMT_SREG " %% " FMT_SREG "\n", result, a, b);
}
#endif
