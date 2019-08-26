
#include <string>
#include <vector>
#include <map>
using namespace std;

#include <stdint.h>

#include "runtime.h"

#define debug(...) while(0);
//#define debug printf

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
		REGTYPE mask = (((REGTYPE)2 << 8*(ri.size))-1) << shift;

		REGTYPE tmp = vm_regs[ri.full_width_reg];
		tmp &= ~mask; /* clear bits in area */
		tmp |= (value << shift); /* bring in the value */
		vm_regs[ri.full_width_reg] = tmp;
		//debug("%s is half width, setting %s to " FMT_REG "\n",
		//	regName.c_str(), ri.full_width_reg.c_str(), value);
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
	debug("SET_REG1        %s = 0x%02X\n", dest.c_str(), src);
}

void SET_REG2(string dest, uint16_t src)
{
	reg_set_value(dest, src);
	debug("SET_REG2        %s = 0x%04X\n", dest.c_str(), src);
}

void SET_REG4(string dest, uint32_t src)
{
	reg_set_value(dest, src);
	debug("SET_REG4        %s = 0x%08X\n", dest.c_str(), src);
}

void SET_REG8(string dest, uint64_t src)
{
	reg_set_value(dest, src);
	debug("SET_REG8        %s = 0x%016llX\n", dest.c_str(), src);
}

/* LowLevelILOperation.LLIL_SET_REG_SPLIT: [("hi", "reg"), ("lo", "reg"), ("src", "expr")] */
void SET_REG_SPLIT(string hi, string lo, REGTYPE src_val)
{
	REGTYPE dst_val_hi = (REGTYPE) (src_val & REGMASKHIHALF) >> (REGWIDTH/2);
	REGTYPE dst_val_lo = (REGTYPE) (src_val & REGMASKLOHALF);
	reg_set_value(hi, dst_val_hi);
	reg_set_value(lo, dst_val_lo);
	debug("SET_REG_SPLIT   " FMT_REG " -> %s = " FMT_REG ", %s = " FMT_REG "\n",
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
	debug("SET_FLAG        %s = %d\n", left.c_str(), right);
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
	debug("PUSH            mem[" FMT_REG "] = " FMT_REG "\n", ea, src);
	*(REGTYPE *)(vm_mem + ea) = src;
}

/* LowLevelILOperation.LLIL_POP: [] */
REGTYPE POP(void)
{
	/* store on stack */
	REGTYPE ea = vm_regs[stackRegName];
	debug("POP             " FMT_REG " from mem[" FMT_REG "]\n", ea, ea);
	REGTYPE val = *(REGTYPE *)(vm_mem + ea);
	/* decrement stack pointer */
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
SREGTYPE SUB(SREGTYPE left, SREGTYPE right)
{
	SREGTYPE result = left - right;
	debug("SUB             " FMT_SREG " = " FMT_SREG " - " FMT_SREG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_SBB: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */

/* LowLevelILOperation.LLIL_AND: [("left", "expr"), ("right", "expr")] */
REGTYPE AND(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left & right;
	debug("AND             " FMT_REG " = " FMT_REG " & " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_OR: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_XOR: [("left", "expr"), ("right", "expr")] */
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
/* LowLevelILOperation.LLIL_RLC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
/* LowLevelILOperation.LLIL_ROR: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_RRC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
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
SREGTYPE DIVS_DP(SREGTYPE left, SREGTYPE right)
{
	SREGTYPE result = left/right;
	debug("DIVS_DP         " FMT_SREG " = " FMT_SREG " / " FMT_SREG "\n", result, left, right);
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
/* LowLevelILOperation.LLIL_NOT: [("src", "expr")] */
REGTYPE NOT(REGTYPE left)
{
	REGTYPE result = ~left;
	debug("NOT             " FMT_REG " = ~" FMT_REG "\n", result, left);
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
/* LowLevelILOperation.LLIL_LOW_PART: [("src", "expr")] */
/* LowLevelILOperation.LLIL_JUMP: [("dest", "expr")] */
void JUMP(REGTYPE dest)
{
	printf("ERROR: JUMP to " FMT_REG " is out of LLIL land, something went wrong in transpilation\n", dest);
	exit(-1);
}

/* LowLevelILOperation.LLIL_JUMP_TO: [("dest", "expr"), ("targets", "int_list")] */
/* LowLevelILOperation.LLIL_CALL: [("dest", "expr")] */
void CALL(REGTYPE dest)
{
	/* dummy push of return address */
	vm_regs[stackRegName] -= sizeof(REGTYPE);
	*(REGTYPE *)(vm_mem + vm_regs[stackRegName]) = (REGTYPE)(0xCA11BACC & REGMASK);
	debug("CALL            " FMT_REG "\n", dest);
}

/* LowLevelILOperation.LLIL_CALL_STACK_ADJUST: [("dest", "expr"), ("stack_adjustment", "int"), ("reg_stack_adjustments", "reg_stack_adjust")] */
/* LowLevelILOperation.LLIL_TAILCALL: [("dest", "expr")] */

void TAILCALL(REGTYPE dest)
{
	/* dummy push of return address */
	vm_regs[stackRegName] -= sizeof(REGTYPE);
	*(REGTYPE *)(vm_mem + vm_regs[stackRegName]) = (REGTYPE)(0xCA11BAC2 & REGMASK);
	debug("TAILCALL        " FMT_REG "\n", dest);
}

/* LowLevelILOperation.LLIL_RET: [("dest", "expr")] */
void RET(REGTYPE dest)
{
	/* IL semantics of RET are _not_ necessarily to pop and jump (but can be)
		an x86 style ret will be RET(POP())
		an arm style ret might be RET(REG("lr")) */
	debug("RET             " FMT_REG "\n", dest);
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
bool CMP_SLT4(int32_t left, int32_t right)
{
	bool result = left < right;
	debug("CMP_SLT         %d = %d < %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_ULT: [("left", "expr"), ("right", "expr")] */
bool CMP_ULT(REGTYPE left, REGTYPE right)
{
	bool result = left <= right;
	debug("CMP_ULT         %d = %d <= %d\n", result, left, right);
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

/* LowLevelILOperation.LLIL_CMP_SGT: [("left", "expr"), ("right", "expr")] */
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
/* LowLevelILOperation.LLIL_BOOL_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_ADD_OVERFLOW: [("left", "expr"), ("right", "expr")] */
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

#ifdef ARCH_ARM
void __aeabi_idivmod()
{
    SREGTYPE a = reg_get_value("r0");
    SREGTYPE b = reg_get_value("r1");
    SREGTYPE result = a % b;
    reg_set_value("r1", result);
	debug("__aeabi_idivmod() returns " FMT_SREG " = " FMT_SREG " %% " FMT_SREG "\n", result, a, b);
}
#endif
