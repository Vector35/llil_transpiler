
#include <string>
#include <vector>
#include <map>
#include <cmath> // for isnan()
using namespace std;

#include <stdint.h>

#include "runtime.h"

#ifndef assert
#define assert(cond) if(!(cond)) __builtin_debugtrap();
#endif

#define DEBUG_RUNTIME_ALL
#define DEBUG_RUNTIME_SETS
#define DEBUG_RUNTIME_STACK

#define debug printf

#if defined(DEBUG_RUNTIME_SETS) || defined(DEBUG_RUNTIME_ALL)
	#define debug_set printf
#else
	#define debug_set(...) while(0);
#endif

#if defined(DEBUG_RUNTIME_STACK) || defined(DEBUG_RUNTIME_ALL)
	#define debug_stack printf
#else
	#define debug_stack(...) while(0);
#endif

/* the foo_il.c must export this, else we can't implement PUSH */
extern string stack_reg_name;
extern bool is_link_reg_arch;
extern string link_reg_name;
extern map<string,struct RegisterInfo> reg_infos;

/* VM components */
uint8_t vm_mem[VM_MEM_SZ];
map<string, type_val> vm_regs;
map<string, int> vm_flags;

// this is needed because some architecture return values in different locations
// depending on the type of the data, eg: arm ... TODO

/*****************************************************************************/
/* type_val and helpers */
/*****************************************************************************/

type_val tv_init(enum TV_TYPE type) { type_val tv; tv.type = type; memset(tv.data, 0, sizeof(tv.data)); return tv; };
type_val tv_new_uint8(uint8_t val) { type_val tv = tv_init(TV_TYPE_UINT8); *(uint8_t *)(tv.data) = val; return tv; }
type_val tv_new_uint16(uint16_t val) { type_val tv = tv_init(TV_TYPE_UINT16); *(uint16_t *)(tv.data) = val; return tv; }
type_val tv_new_uint32(uint32_t val) { type_val tv = tv_init(TV_TYPE_UINT32); *(uint32_t *)(tv.data) = val; return tv; }
type_val tv_new_uint64(uint64_t val) { type_val tv = tv_init(TV_TYPE_UINT64); *(uint64_t *)(tv.data) = val; return tv; }
type_val tv_new_float32(float val) { type_val tv = tv_init(TV_TYPE_FLOAT32); *(float *)(tv.data) = val; return tv; }
type_val tv_new_float64(double val) { type_val tv = tv_init(TV_TYPE_FLOAT64); *(double *)(tv.data) = val; return tv; }
type_val tv_new_none() { type_val tv = tv_init(TV_TYPE_NONE); memset(tv.data, 0, sizeof(tv.data));  return tv; }

uint8_t tv_get_uint8(type_val tv) { return *(uint8_t *)(tv.data); }
uint16_t tv_get_uint16(type_val tv) { return *(uint16_t *)(tv.data); }
uint32_t tv_get_uint32(type_val tv) { return *(uint32_t *)(tv.data); }
uint64_t tv_get_uint64(type_val tv) { return *(uint64_t *)(tv.data); }
float tv_get_float32(type_val tv) { return *(float *)(tv.data); }
double tv_get_float64(type_val tv) { return *(double *)(tv.data); }

void tv_set_uint8(type_val tv, uint8_t val) { tv.type = TV_TYPE_UINT8; *(uint8_t *)(tv.data) = val; }
void tv_set_uint16(type_val tv, uint16_t val) { tv.type = TV_TYPE_UINT16; *(uint16_t *)(tv.data) = val; }
void tv_set_uint32(type_val tv, uint32_t val) { tv.type = TV_TYPE_UINT32; *(uint32_t *)(tv.data) = val; }
void tv_set_uint64(type_val tv, uint64_t val) { tv.type = TV_TYPE_UINT64; *(uint64_t *)(tv.data) = val; }

void tv_to_str(type_val tv, char *str, int buflen)
{
	switch(tv.type) {
		case TV_TYPE_UINT8:
			snprintf(str, buflen, "0x%02X", tv_get_uint8(tv));
			break;
		case TV_TYPE_UINT16:
			snprintf(str, buflen, "0x%04X", tv_get_uint16(tv));
			break;
		case TV_TYPE_UINT32:
			snprintf(str, buflen, "0x%08X", tv_get_uint32(tv));
			break;
		case TV_TYPE_UINT64:
			snprintf(str, buflen, "0x%016llX", tv_get_uint64(tv));
			break;
		case TV_TYPE_FLOAT32:
			snprintf(str, buflen, "%f", tv_get_float32(tv));
			break;
		default:
			str[0] = '\0';
	}
}

int tv_cmp(type_val a, type_val b)
{
	return memcmp(a.data, b.data, sizeof(a.data));
}

/*****************************************************************************/
/* register setting/getting */
/*****************************************************************************/

bool is_temp_reg(string reg_name)
{
	return reg_name.rfind("temp", 0) == 0;
}

// return the register's ENTIRE type_val (possibly a larger parent register)
//
type_val reg_get_type_val(string reg_name)
{
	type_val result;

	/* temp registers simply come from the temp regs file */
	if(is_temp_reg(reg_name))
		result = vm_regs[reg_name];
	else
	{
		/* otherwise we need to resolve sub-register relationships */
		RegisterInfo reg_info = reg_infos[reg_name];

		/* full width */
		if(reg_info.full_width_reg == reg_name)
			result = vm_regs[reg_name];
		/* sub register */
		else
			result = vm_regs[reg_info.full_width_reg];

		/* returned registers retain type indicating their size */
		switch(reg_info.size)
		{
			case 1: result.type = TV_TYPE_UINT8;
			case 2: result.type = TV_TYPE_UINT16;
			case 4: result.type = TV_TYPE_UINT32;
			case 8: result.type = TV_TYPE_UINT64;
			case 16: result.type = TV_TYPE_UINT128;
		}
	}

	return result;
}

// set the register's type_val (possibly in a parent register)
void reg_set_type_val(string reg_name, type_val tv)
{
	//printf("setting %s to ", reg_name.c_str());
	//for(int i=0; i<16; i++)
	//	printf("%02X ", tv.data[i]&0xFF);
	//printf("\n");

	if(is_temp_reg(reg_name)) {
		vm_regs[reg_name] = tv;
		return;
	}

	RegisterInfo reg_info = reg_infos[reg_name];

	if(reg_info.full_width_reg == reg_name) {
		vm_regs[reg_name] = tv;
		return;
	}

	vm_regs[reg_info.full_width_reg] = tv;
}

// return the register's offset into type_val.data of its parent register
// eg:
//    rax is offset 0 into rax, return 0
//    eax is offset 0 into rax, return 1
//     ah is offset 1 into rax, return 1
int reg_get_type_val_offset(string reg_name)
{
	if(is_temp_reg(reg_name))
		return 0;

	RegisterInfo reg_info = reg_infos[reg_name];

	assert((reg_info.full_width_reg != reg_name) || reg_info.offset==0);

	return reg_info.offset;
}

/* internal register getters */

float reg_get_float32_nocheck(string name)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(float *)(tv.data + offset);
}

uint8_t reg_get_uint8(string name)
{
	//assert(is_temp_reg(name) || reg_infos[name].size == 1);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(uint8_t *)(tv.data + offset);
}

uint16_t reg_get_uint16(string name)
{
	//assert(is_temp_reg(name) || reg_infos[name].size == 2);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(uint16_t *)(tv.data + offset);
}

uint32_t reg_get_uint32(string name)
{
	//assert(is_temp_reg(name) || reg_infos[name].size == 4);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(uint32_t *)(tv.data + offset);
}

uint64_t reg_get_uint64(string name)
{
	//assert(is_temp_reg(name) || reg_infos[name].size == 8);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(uint64_t *)(tv.data + offset);
}

__uint128_t reg_get_uint128(string name)
{
	//assert(is_temp_reg(name) || reg_infos[name].size == 16);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	return *(__uint128_t *)(tv.data + offset);
}

float reg_get_float32(string name)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 4);
	return reg_get_float32_nocheck(name);
}

/* internal register setters */

void reg_set_uint8_nocheck(string name, uint8_t val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(uint8_t *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_uint16_nocheck(string name, uint16_t val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(uint16_t *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_uint32_nocheck(string name, uint32_t val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(uint32_t *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_uint64_nocheck(string name, uint64_t val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(uint64_t *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_uint128_nocheck(string name, __uint128_t val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(__uint128_t *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_uint8(string name, uint8_t val)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 1);
	reg_set_uint8_nocheck(name, val);
}

void reg_set_uint16(string name, uint16_t val)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 2);
	reg_set_uint16_nocheck(name, val);
}

void reg_set_uint32(string name, uint32_t val)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 4);
	reg_set_uint32_nocheck(name, val);
}

void reg_set_uint64(string name, uint64_t val)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 8);
	reg_set_uint64_nocheck(name, val);
}

void reg_set_uint128(string name, __uint128_t val)
{
	assert(is_temp_reg(name) || reg_infos[name].size == 16);
	reg_set_uint128_nocheck(name, val);
}

void reg_set_float32(string name, float val)
{
	// do not force size check: often the low-bits of a floating point register
	// are reserved for smaller float types, eg: 128-bit xmm0 can have low 32
	// bits for a normal single precision float

	//assert(is_temp_reg(name) || reg_infos[name].size == 32);
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(float *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

void reg_set_float64(string name, double val)
{
	type_val tv = reg_get_type_val(name);
	int offset = reg_get_type_val_offset(name);
	*(double *)(tv.data + offset) = val;
	reg_set_type_val(name, tv);
}

/*****************************************************************************/
/* operations */
/*****************************************************************************/

/* LowLevelILOperation.LLIL_NOP: [] */
void NOP(void)
{
	return;
}

/* LowLevelILOperation.LLIL_REG: [("src", "reg")] */

/* get an 8-bit register, or the 8-bit low bits of a register */
uint8_t REG_B(string name)
{
	uint8_t result = reg_get_uint8(name);
	debug("REG_B           0x%02X (value of %s)\n", result, name.c_str());
	return result;
}

/* get a 16-bit register, or the 16-bit low bits of a register */
uint16_t REG_W(string name)
{
	uint16_t result = reg_get_uint16(name);
	debug("REG_W           0x%04X (value of %s)\n", result, name.c_str());
	return result;
}

/* get a 32-bit register, or the 32-bit low bits of a register */
uint32_t REG_D(string name)
{
	uint32_t result = reg_get_uint32(name);
	float result_f = *(float *)&result;
	debug("REG_D           0x%08X (as float: %f) (value of %s)\n", result, result_f, name.c_str());
	return result;
}

/* get a 64-bit register, or the 64-bit low bits of a register */
uint64_t REG_Q(string name)
{
	uint64_t result = reg_get_uint64(name);
	debug("REG_Q           0x%016llX (value of %s)\n", (uint64_t)result, name.c_str());
	return result;
}

/* get a 128-bit register */
__uint128_t REG_O(string name)
{
	__uint128_t result = reg_get_uint128(name);
	debug("REG_O           0x%016llX%016llX (value of %s)\n", (uint64_t)(result>>64), (uint64_t)result, name.c_str());
	return result;
}

/* LowLevelILOperation.LLIL_SET_REG: [("dest", "reg"), ("src", "expr")] */
void SET_REG_B(string reg_name, uint8_t value)
{
	reg_set_uint8_nocheck(reg_name, value);
	debug_set("SET_REG_B       %s = 0x%02X\n", reg_name.c_str(), value);
}

void SET_REG_W(string reg_name, uint16_t value)
{
	reg_set_uint16_nocheck(reg_name, value);
	debug_set("SET_REG_W       %s = 0x%04X\n", reg_name.c_str(), value);
}

void SET_REG_D(string reg_name, uint32_t value)
{
	reg_set_uint32_nocheck(reg_name, value);
	debug_set("SET_REG_D       %s = 0x%08X\n", reg_name.c_str(), value);
}

void SET_REG_Q(string reg_name, uint64_t value)
{
	reg_set_uint64_nocheck(reg_name, value);
	debug_set("SET_REG_Q       %s = 0x%016llX\n", reg_name.c_str(), value);
}

void SET_REG_O(string reg_name, __uint128_t value)
{
	reg_set_uint128_nocheck(reg_name, value);
	debug_set("SET_REG_O       %s = 0x%016llX%016llX\n", reg_name.c_str(), (uint64_t)(value>>64), (uint64_t)value);
}

/* LowLevelILOperation.LLIL_SET_REG_SPLIT: [("hi", "reg"), ("lo", "reg"), ("src", "expr")] */

/* split a 64-bit value into two 32-bit registers, eg:
 * edx:eax = 0xDEADBEEF:0xCAFEBABE = 0xDEADBEEFCAFEBABE */
void SET_REG_SPLIT_D(string reg_hi, string reg_lo, uint64_t src_val)
{
	uint32_t dst_val_hi = (src_val >> 32) & 0xFFFFFFFF;
	uint32_t dst_val_lo = src_val & 0xFFFFFFFF;
	reg_set_uint32(reg_hi, dst_val_hi);
	reg_set_uint32(reg_lo, dst_val_lo);
	debug_set("SET_REG_SPLIT_D   %s:%s = 0x%08X:0x%08X = 0x%016llX\n",
		reg_hi.c_str(), reg_lo.c_str(), dst_val_hi, dst_val_lo, src_val);
}

/* LowLevelILOperation.LLIL_REG_SPLIT: [("hi", "reg"), ("lo", "reg")] */

/* join two 32-bit values into a 64-bit value */
uint64_t REG_SPLIT_D(string reg_hi, string reg_lo)
{
	uint32_t src_hi = reg_get_uint32(reg_hi);
	uint32_t src_lo = reg_get_uint32(reg_lo);
	uint64_t result = ((uint64_t)src_hi << 32) | src_lo;
	debug("REG_SPLIT_D     0x%016llX = 0x%08X:0x%08X = %s:%s\n", result, src_hi, src_lo, reg_hi.c_str(), reg_lo.c_str());
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
uint8_t LOAD_B(REGTYPE expr)
{
	uint8_t result = vm_mem[expr];
	debug("LOAD_B          0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint16_t LOAD_W(REGTYPE expr)
{
	uint16_t result = *(uint16_t *)(vm_mem + expr);
	debug("LOAD_W          0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint32_t LOAD_D(REGTYPE expr)
{
	uint32_t result = *(uint32_t *)(vm_mem + expr);
	debug("LOAD_D          0x%X = mem[" FMT_REG "]\n", result, expr);
	return result;
}

uint64_t LOAD_Q(REGTYPE expr)
{
	uint64_t result = *(uint64_t *)(vm_mem + expr);
	debug("LOAD_Q          0x%llX = mem[" FMT_REG "]\n", result, expr);
	return result;
}

__uint128_t LOAD_O(REGTYPE expr)
{
	__uint128_t result = *(__uint128_t *)(vm_mem + expr);
	debug("LOAD_O         0x%llX%08llX = mem[" FMT_REG "]\n", (uint64_t)(result>>64), (uint64_t)result, expr);
	return result;
}

/* LowLevelILOperation.LLIL_STORE: [("dest", "expr"), ("src", "expr")] */
void STORE_B(REGTYPE dest, uint8_t src)
{
	debug("STORE_B         byte[" FMT_REG "] = 0x%02X\n", dest, src);
	*(uint8_t *)(vm_mem + dest) = src;
}

void STORE_W(REGTYPE dest, uint16_t src)
{
	debug("STORE_W         word[" FMT_REG "] = 0x%04X\n", dest, src);
	*(uint16_t *)(vm_mem + dest) = src;
}

void STORE_D(REGTYPE dest, uint32_t src)
{
	debug("STORE_D         dword[" FMT_REG "] = 0x%08X\n", dest, src);
	*(uint32_t *)(vm_mem + dest) = src;
}

void STORE_Q(REGTYPE dest, uint64_t src)
{
	debug("STORE_Q         qword[" FMT_REG "] = 0x%016llX\n", dest, src);
	*(uint64_t *)(vm_mem + dest) = src;
}

/* LowLevelILOperation.LLIL_PUSH: [("src", "expr")] */
void PUSH_Q(REGTYPE src)
{
	/* decrement stack pointer */
	REG_SET_ADDR(stack_reg_name, REG_GET_ADDR(stack_reg_name) - sizeof(REGTYPE));
	/* store on stack */
	ADDRTYPE ea = REG_GET_ADDR(stack_reg_name);
	debug_stack("PUSH_Q          mem[" FMT_REG "] = " FMT_REG "\n", ea, src);
	*(REGTYPE *)(vm_mem + ea) = src;
}

/* LowLevelILOperation.LLIL_POP: [] */
REGTYPE POP_Q(void)
{
	/* retrieve from stack */
	ADDRTYPE ea = REG_GET_ADDR(stack_reg_name);
	REGTYPE val = *(ADDRTYPE *)(vm_mem + ea);
	debug_stack("POP_Q           " FMT_ADDR " = mem[" FMT_ADDR "]\n", val, ea);
	/* increment stack pointer */
	REG_SET_ADDR(stack_reg_name, REG_GET_ADDR(stack_reg_name) + sizeof(REGTYPE));
	return val;
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
uint32_t FLOAT_CONST_D(float input)
{
	uint32_t result = *(uint32_t *)&input;
	debug("FLOAT_CONST_D   0x%08X (%f)\n", result, input);
	return result;
}

/* LowLevelILOperation.LLIL_FLAG: [("src", "flag")] */
bool FLAG(string src)
{
	bool result = vm_flags[src];
	debug("FLAG            %d = vm_flags[%s]\n", result, src.c_str());
	return result;
}

/* LowLevelILOperation.LLIL_FLAG_BIT: [("src", "flag"), ("bit", "int")] */

/* LowLevelILOperation.LLIL_ADD: [("left", "expr"), ("right", "expr")] */
uint8_t ADD_B(uint8_t left, uint8_t right)
{
	uint8_t result = left + right;
	debug("ADD_B           0x%02X = 0x%02X + 0x%02X\n", result & 0xFF, left & 0xFF, right & 0xFF);
	return result;
}

uint16_t ADD_W(uint16_t left, uint16_t right)
{
	uint16_t result = left + right;
	debug("ADD_W           0x%04X = 0x%04X + 0x%04X\n", result & 0xFFFF, left & 0xFFFF, right & 0xFFFF);
	return result;
}

uint32_t ADD_D(uint32_t left, uint32_t right)
{
	uint32_t result = left + right;
	debug("ADD_D           0x%08X = 0x%08X + 0x%08X\n", result, left, right);
	return result;
}

uint64_t ADD_Q(uint64_t left, uint64_t right)
{
	uint64_t result = left + right;
	debug("ADD_Q           0x%016llX = 0x%016llX + 0x%016llX\n", result, left, right);
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
uint8_t SUB_B(uint8_t a, uint8_t b)
{
	uint8_t result = a - b;
	debug("SUB_B           0x%02X = 0x%02X - 0x%02X\n", result, a, b);
	return result;
}

uint16_t SUB_W(uint16_t a, uint16_t b)
{
	uint16_t result = a - b;
	debug("SUB_W           0x%04X = 0x%04X - 0x%04X\n", result, a, b);
	return result;
}

uint32_t SUB_D(uint32_t a, uint32_t b)
{
	uint32_t result = a - b;
	debug("SUB_D           0x%08X = 0x%08X - 0x%08X\n", result, a, b);
	return result;
}

uint64_t SUB_Q(uint64_t a, uint64_t b)
{
	uint64_t result = a - b;
	debug("SUB_Q           0x%016llX = 0x%016llX - 0x%016llX\n", result, a, b);
	return result;
}

/* LowLevelILOperation.LLIL_SBB: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t SBB_B(uint8_t a, uint8_t b, uint8_t c)
{
	uint8_t result = a - b - c;
	debug("SBB1            0x%02X = 0x%02X - 0x%02X - %d\n", result, a, b, c);
	return result;
}

uint16_t SBB_W(uint16_t a, uint16_t b, uint16_t c)
{
	uint16_t result = a - b - c;
	debug("SBB2            0x%04X = 0x%04X - 0x%04X - %d\n", result, a, b, c);
	return result;
}

uint32_t SBB_D(uint32_t a, uint32_t b, uint32_t c)
{
	uint32_t result = a - b - c;
	debug("SBB4            0x%08X = 0x%08X - 0x%08X - %d\n", result, a, b, c);
	return result;
}

uint64_t SBB64(uint64_t a, uint64_t b, uint64_t c)
{
	uint64_t result = a - b - c;
	debug("SBB8            0x%016llX = 0x%016llX - 0x%016llX - %lld\n", result, a, b, c);
	return result;
}

/* LowLevelILOperation.LLIL_AND: [("left", "expr"), ("right", "expr")] */
uint32_t AND_D(uint32_t left, uint32_t right)
{
	uint32_t result = left & right;
	debug("AND_D           0x%08X = 0x%08X & 0x%08X\n", result, left, right);
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
uint64_t LSL_Q(uint64_t left, uint64_t right)
{
	uint64_t result = left << right;
	debug("LSL_Q           " FMT_REG " = " FMT_REG " << " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_LSR: [("left", "expr"), ("right", "expr")] */
REGTYPE LSR(REGTYPE left, REGTYPE right)
{
	REGTYPE result = left >> right;
	debug("LSR             " FMT_REG " = " FMT_REG " << " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_ASR: [("left", "expr"), ("right", "expr")] */
int32_t ASR_D(int32_t left, uint32_t right)
{
	int32_t result = left >> right;
	debug("ASR_D           0x%08X = 0x%08X >> 0x%08X\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_ROL: [("left", "expr"), ("right", "expr")] */
uint8_t ROL_B(uint8_t value, uint8_t amt)
{
	amt = amt % 8;
	uint8_t result = (value << amt) | (value >> (8-amt));
	debug("ROL1            0x%02X = ROL(0x%02X, %d)\n", result, value, amt);
	return result;
}

uint16_t ROL_W(uint16_t value, uint16_t amt)
{
	amt = amt % 16;
	uint16_t result = (value << amt) | (value >> (16-amt));
	debug("ROL2            0x%04X = ROL(0x%04X, %d)\n", result, value, amt);
	return result;
}

uint32_t ROL_D(uint32_t value, uint32_t amt)
{
	amt = amt % 32;
	uint32_t result = (value << amt) | (value >> (8-amt));
	debug("ROL4            0x%08X = ROL(0x%08X, %d)\n", result, value, amt);
	return result;
}

uint64_t ROL64(uint64_t value, uint64_t amt)
{
	amt = amt % 64;
	uint64_t result = (value << amt) | (value >> (8-amt));
	debug("ROL8            0x%08llX = ROL(0x%016llX, %lld)\n", result, value, amt);
	return result;
}

/* LowLevelILOperation.LLIL_RLC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RLC_B(uint8_t value, uint8_t amt, bool carry)
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
uint8_t ROR_B(uint8_t value, uint8_t amt)
{
	amt = amt % 8;
	uint8_t result = (value >> amt) | (value << (8-amt));
	debug("ROR1(0x%02X, %d) returns 0x%02X\n", value, amt, result);
	return result;
}

uint16_t ROR_W(uint16_t value, uint16_t amt)
{
	amt = amt % 16;
	uint16_t result = (value >> amt) | (value << (16-amt));
	debug("ROR16(0x%04X, %d) returns 0x%04X\n", value, amt, result);
	return result;
}

uint32_t ROR_D(uint32_t value, uint32_t amt)
{
	amt = amt % 32;
	uint32_t result = (value >> amt) | (value << (8-amt));
	debug("ROR32(0x%08X, %d) returns 0x%08X\n", value, amt, result);
	return result;
}

uint64_t ROR64(uint64_t value, uint64_t amt)
{
	amt = amt % 64;
	uint64_t result = (value >> amt) | (value << (8-amt));
	debug("ROR64(0x%016llX, %lld) returns 0x%016llX\n", value, amt, result);
	return result;
}

/* LowLevelILOperation.LLIL_RRC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RRC_B(uint8_t value, uint8_t amt, bool carry)
{
	uint8_t result = value;

	if(amt) {
		amt = amt % 8;
		// normal carry
		uint8_t a = value >> amt;
		uint8_t b = value << (8-amt+1);
		uint8_t c = value << (8-amt);
		result = a | b | c;
	}

	debug("RRC8            0x%X = 0x%X >>> %d and carry = %d\n", result, value, amt, carry);
	return result;
}

int32_t MUL_D(int32_t left, int32_t right)
{
	int32_t result = left * right;
	debug("MUL_D           0x%08X = 0x%08X & 0x%08X\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_MULU_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_MULS_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVU: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVU_DP: [("left", "expr"), ("right", "expr")] */

/* LowLevelILOperation.LLIL_DIVS: [("left", "expr"), ("right", "expr")] */
uint32_t DIVS_D(uint32_t left, uint32_t right)
{
	int32_t ai = *(int32_t *)&left;
	int32_t bi = *(int32_t *)&right;
	int32_t ci = ai / bi;
	uint32_t result = *(uint32_t *)&ci;
	debug("DIVS_D          0x%08X (%d) = 0x%08X (%d) / 0x%08X (%d)\n", result, ci, left, ai, right, bi);
	return result;
}

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
uint8_t NEG_B(uint8_t src)
{
    uint8_t result = (src ^ 0xFF) + 1;
	debug("NEG8            0x%02X = neg(0x%02X)\n", result, src);
    return result;
}

uint16_t NEG_W(uint16_t src)
{
    uint16_t result = (src ^ 0xFFFF) + 1;
	debug("NEG16            0x%04X = neg(0x%04X)\n", result, src);
    return result;
}

uint32_t NEG_D(uint32_t src)
{
    uint32_t result = (src ^ 0xFFFFFFFF) + 1;
	debug("NEG32            0x%08X = neg(0x%08X)\n", result, src);
    return result;
}

uint64_t NEG64(uint64_t src)
{
    uint64_t result = (src ^ 0xFFFFFFFFFFFFFFFF) + 1;
	debug("NEG64            0x%016llX = neg(0x%016llX)\n", result, src);
    return result;
}

/* LowLevelILOperation.LLIL_NOT: [("src", "expr")] */
uint8_t NOT0(uint8_t left)
{
	/* size 0 is special case which means treat as bool
		nonzero -> zero
		zero -> 1
	*/
	uint8_t result = !!(left);
	debug("NOT0            0x%02X = 0x%02X ^ 1\n", result, left);
	return result;
}

uint8_t NOT_B(uint8_t left)
{
	uint8_t result = ~left;
	debug("NOT8            0x%02X = ~0x%02X\n", result, left);
	return result;
}

uint16_t NOT_W(uint16_t left)
{
	uint16_t result = ~left;
	debug("NOT16           0x%04X = ~0x%04X\n", result, left);
	return result;
}

uint32_t NOT_D(uint32_t left)
{
	uint32_t result = ~left;
	debug("NOT32           0x%08X = ~0x%08X\n", result, left);
	return result;
}

uint64_t NOT64(uint64_t left)
{
	uint64_t result = ~left;
	debug("NOT64           0x%016llX = ~0x%016llX\n", result, left);
	return result;
}

/* LowLevelILOperation.LLIL_SX: [("src", "expr")] */

/* sign extend a byte to a word */
int16_t SX_W_b(int8_t src)
{
	uint16_t result = (src & 0x80) ? 0xFF00 | src : src;
	debug("SX_W            0x%02X -> 0x%04X\n", src, result);
	return result;
}

/* sign extend a byte to a double word */
int32_t SX_D_b(int8_t src)
{
	uint32_t result = (src & 0x80) ? 0xFFFFFF00 | src : src;
	debug("SX_D            0x%02X -> 0x%08X\n", src, result);
	return result;
}

/* sign extend a word to a double word */
int32_t SX_D_w(int16_t src)
{
	int32_t result = (src & 0x8000) ? 0xFFFF0000 | src : src;
	debug("SX_D            0x%04X -> 0x%08X\n", src, result);
	return result;
}

/* sign extend a byte to a quad word */
int64_t SX_Q_b(int8_t src)
{
	int64_t result = (src & 0x80) ? 0xFFFFFFFFFFFFFF00 | src : src;
	debug("SX_Q            %02X -> 0x%016llX\n", src, result);
	return result;
}

/* sign extend a word to a quad word */
int64_t SX_Q_w(int16_t src)
{
	int64_t result = (src & 0x8000) ? 0xFFFFFFFFFFFF0000 | src : src;
	debug("SX_Q            %04X -> 0x%016llX\n", src, result);
	return result;
}

/* sign extend a double word to a quad word */
int64_t SX_Q_d(int32_t src)
{
	int64_t result = (src & 0x80000000) ? 0xFFFFFFFF00000000 | src : src;
	debug("SX_Q            %08X -> 0x%016llX\n", src, result);
	return result;
}

/* LowLevelILOperation.LLIL_TRAP: [("vector", "int")] */
void TRAP(int32_t src)
{
	debug("TRAP            0n%d, 0x%X", src, src);
}

/* LowLevelILOperation.LLIL_ZX: [("src", "expr")] */
uint32_t ZX_D(uint32_t src)
{
	uint32_t result = src;
	debug("ZX_D            0x%08X -> 0x%08X\n", src, result);
	return result;
}

uint64_t ZX_Q(uint64_t src)
{
	uint64_t result = src;
	debug("ZX_Q            0x%016llX -> 0x%016llX\n", src, result);
	return result;
}

__uint128_t ZX_O(__uint128_t src)
{
	__uint128_t result = src;
	debug("ZX_O            0x%016llX%016llX -> 0x%016llX%016llX\n", (uint64_t)(src>>64), (uint64_t)src, (uint64_t)(result>>64), (uint64_t)result);
	return result;
}

/* LowLevelILOperation.LLIL_LOW_PART: [("src", "expr")] */
uint8_t LOW_PART_B(REGTYPE left)
{
	uint8_t result = left & 0xFF;
	debug("LOW_PART_B       " FMT_REG " -> 0x%02X\n", left, result);
	return result;
}

uint16_t LOW_PART_W(REGTYPE left)
{
	uint16_t result = left & 0xFFFF;
	debug("LOW_PART_W      " FMT_REG " -> 0x%04X\n", left, result);
	return result;
}

uint32_t LOW_PART_D(REGTYPE left)
{
	uint32_t result = left & 0xFFFFFFFF;
	debug("LOW_PART_D      " FMT_REG " -> 0x%08X\n", left, result);
	return result;
}

uint64_t LOW_PART_Q(REGTYPE left)
{
	uint64_t result = left & 0xFFFFFFFFFFFFFFFF;
	debug("LOW_PART_Q      " FMT_REG " -> 0x%016llX\n", left, result);
	return result;
}

/* LowLevelILOperation.LLIL_JUMP: [("dest", "expr")] */
RETURN_ACTION JUMP(REGTYPE dest)
{
	if(dest == RETURN_ADDRESS_CANARY)
		return RETURN_TRUE;

	printf("ERROR: JUMP to " FMT_REG " is out of LLIL land, something went wrong in transpilation\n", dest);
	exit(-1);
	return RETURN_FALSE;
}

/* LowLevelILOperation.LLIL_JUMP_TO: [("dest", "expr"), ("targets", "int_list")] */
/* LowLevelILOperation.LLIL_CALL: [("dest", "expr")] */
void CALL(REGTYPE dest, void (*pfunc)(void), const char *func_name)
{
	if(is_link_reg_arch) {
		/* this is a link register style of architecture, so set the LR */
		REG_SET_ADDR(link_reg_name, RETURN_ADDRESS_CANARY);
		debug_set("SET             %s = " FMT_REG "\n", link_reg_name.c_str(), RETURN_ADDRESS_CANARY);
	}
	else {
		/* this is a push-the-return-address style of architecture
			so push a dummy return address */
		REG_SET_ADDR(stack_reg_name, REG_GET_ADDR(stack_reg_name) - sizeof(ADDRTYPE));

		*(ADDRTYPE *)(vm_mem + REG_GET_ADDR(stack_reg_name)) = RETURN_ADDRESS_CANARY;

		debug_stack("CALL            " FMT_REG "   mem[" FMT_REG "] = " FMT_REG " %s()\n",
			dest, REG_GET_ADDR(stack_reg_name), RETURN_ADDRESS_CANARY, func_name);
	}

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
	// vm_regs[stack_reg_name] += sizeof(REGTYPE);
	debug_stack("RET             " FMT_REG "\n", dest);
}

/* LowLevelILOperation.LLIL_NORET: [] */
/* LowLevelILOperation.LLIL_IF: [("condition", "expr"), ("true", "int"), ("false", "int")] */
/* LowLevelILOperation.LLIL_GOTO: [("dest", "int")] */
/* LowLevelILOperation.LLIL_FLAG_COND: [("condition", "cond"), ("semantic_class", "sem_class")] */
/* LowLevelILOperation.LLIL_FLAG_GROUP: [("semantic_group", "sem_group")] */
/* LowLevelILOperation.LLIL_CMP_E: [("left", "expr"), ("right", "expr")] */
bool CMP_E_D(uint32_t left, uint32_t right)
{
	bool result = left == right;
	debug("CMP_E_D         %d = (0x%08X == 0x%08X)\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_NE: [("left", "expr"), ("right", "expr")] */
bool CMP_NE_D(uint32_t left, uint32_t right)
{
	bool result = left != right;
	debug("CMP_NE_D        %d = (0x%08X != 0x%08X)\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SLT: [("left", "expr"), ("right", "expr")] */
bool CMP_SLT_B(int8_t left, int8_t right)
{
	bool result = left < right;
	debug("CMP_SLT8        %d = (%d < %d)\n", result, left, right);
	return result;
}

bool CMP_SLT_W(int16_t left, int16_t right)
{
	bool result = left < right;
	debug("CMP_SLT16       %d = (%d < %d)\n", result, left, right);
	return result;
}

bool CMP_SLT_D(int32_t left, int32_t right)
{
	bool result = left < right;
	debug("CMP_SLT32       %d = (%d < %d)\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_ULT: [("left", "expr"), ("right", "expr")] */
bool CMP_ULT(REGTYPE left, REGTYPE right)
{
	bool result = left < right;
	debug("CMP_ULT         %d = " FMT_REG " < " FMT_REG "\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_SLE: [("left", "expr"), ("right", "expr")] */
bool CMP_SLE_B(int8_t left, int8_t right)
{
	bool result = left <= right;
	debug("CMP_SLE_B       %d = %d <= %d\n", result, left, right);
	return result;
}

bool CMP_SLE_W(int16_t left, int16_t right)
{
	bool result = left <= right;
	debug("CMP_SLE_W        %d = %d <= %d\n", result, left, right);
	return result;
}

bool CMP_SLE_D(int32_t left, int32_t right)
{
	bool result = left <= right;
	debug("CMP_SLE_D        %d = %d <= %d\n", result, left, right);
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
bool CMP_SGE_B(int8_t left, int8_t right)
{
	bool result = left >= right;
	debug("CMP_SGE_B       %d = %d >= %d\n", result, left, right);
	return result;
}

bool CMP_SGE_W(int16_t left, int16_t right)
{
	bool result = left >= right;
	debug("CMP_SGE_W       %d = %d >= %d\n", result, left, right);
	return result;
}

bool CMP_SGE_D(int32_t left, int32_t right)
{
	bool result = left >= right;
	debug("CMP_SGE_D       %d = %d >= %d\n", result, left, right);
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
bool CMP_SGT_B(int8_t left, int8_t right)
{
	bool result = left > right;
	debug("CMP_SGT_B       %d = %d > %d\n", result, left, right);
	return result;
}

bool CMP_SGT_W(int16_t left, int16_t right)
{
	bool result = left > right;
	debug("CMP_SGT_W       %d = %d > %d\n", result, left, right);
	return result;
}

bool CMP_SGT_D(int32_t left, int32_t right)
{
	bool result = left > right;
	debug("CMP_SGT_D       %d = %d > %d\n", result, left, right);
	return result;
}

/* LowLevelILOperation.LLIL_CMP_UGT: [("left", "expr"), ("right", "expr")] */
bool CMP_UGT_Q(uint64_t left, uint64_t right)
{
	bool result = left > right;
	debug("CMP_UGT_Q       %d = " FMT_REG " > " FMT_REG "\n", result, left, right);
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
bool ADD_OVERFLOW_B(uint8_t a, uint8_t b)
{
	bool result = a >= 256 - b;
	debug("ADD_OVERFLOW_B  %d (when %d + %d)\n", result, a, b);
	return result;
}

bool ADD_OVERFLOW_W(uint16_t a, uint16_t b)
{
	bool result = a >= 65536 - b;
	debug("ADD_OVERFLOW_W   %d (when %d + %d)\n", result, a, b);
	return result;
}

bool ADD_OVERFLOW_D(uint32_t a, uint32_t b)
{
	bool result = a >= 4294967296 - b;
	debug("ADD_OVERFLOW_D   %d (when %d + %d)\n", result, a, b);
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

/* floating point add, single precision */
uint32_t FADD_S(uint32_t a, uint32_t b)
{
	float af = *(float *)&a;
	float bf = *(float *)&b;
	float cf = af + bf;
	debug("FADD_S          %f = %f + %f\n", cf, af, bf);
	return *(uint32_t *)&cf;
}

/* floating point add, double precision */
uint64_t FADD_D(uint64_t a, uint64_t b)
{
	double af = *(double *)&a;
	double bf = *(double *)&b;
	double cf = af + bf;
	debug("FADD_D          %f = %f + %f\n", cf, af, bf);
	return *(uint64_t *)&cf;
}

/* LowLevelILOperation.LLIL_FSUB: [("left", "expr"), ("right", "expr")] */

/* floating point subtract, single precision */
uint32_t FSUB_S(uint32_t a, uint32_t b)
{
	float af = *(float *)&a;
	float bf = *(float *)&b;
	float cf = af - bf;
	debug("FSUB_S          %f = %f - %f\n", cf, af, bf);
	return *(uint32_t *)&cf;
}

/* LowLevelILOperation.LLIL_FMUL: [("left", "expr"), ("right", "expr")] */

/* floating point multiplication, single precision */
uint32_t FMUL_S(uint32_t a, uint32_t b)
{
	float af = *(float *)&a;
	float bf = *(float *)&b;
	float cf = af * bf;
	debug("FMUL_D          %f = %f * %f\n", cf, af, bf);
	return *(uint32_t *)&cf;
}

/* floating point multiplication, double precision */
uint64_t FMUL_D(uint64_t a, uint64_t b)
{
	double af = *(double *)&a;
	double bf = *(double *)&b;
	double cf = af * bf;
	debug("FMUL_Q          %f = %f * %f\n", cf, af, bf);
	return *(uint64_t *)&cf;
}

/* LowLevelILOperation.LLIL_FDIV: [("left", "expr"), ("right", "expr")] */
uint32_t FDIV_S(uint32_t a, uint32_t b)
{
	float af = *(float *)&a;
	float bf = *(float *)&b;
	float cf = af / bf;
	debug("FDIV_S          %f = %f / %f\n", cf, af, bf);
	return *(uint32_t *)&cf;
}

uint64_t FDIV_D(uint64_t a, uint64_t b)
{
	double af = *(double *)&a;
	double bf = *(double *)&b;
	double cf = af / bf;
	debug("FDIV_D          %f = %f / %f\n", cf, af, bf);
	return *(uint64_t *)&cf;
}

/* LowLevelILOperation.LLIL_FSQRT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FNEG: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FABS: [("src", "expr")] */
/* LowLevelILOperation.LLIL_FLOAT_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_INT_TO_FLOAT: [("src", "expr")] */

/* LowLevelILOperation.LLIL_FLOAT_CONV: [("src", "expr")] */

/* convert a double precision float to single precision */
uint32_t FLOAT_CONV_S(uint64_t input)
{
	double input_f = *(double *)&input;
	float output_f = input_f;
	uint32_t output = *(uint32_t *)&output_f;
	debug("FLOAT_CONV_S    0x%08X (%f) = 0x%016llX (%f)\n", output, output_f, input, input_f);
	return output;
}

/* convert a single precision float to double precision */
uint32_t FLOAT_CONV_D(uint64_t input)
{
	double input_f = *(double *)&input;
	float output_f = input_f;
	uint32_t output = *(uint32_t *)&output_f;
	debug("FLOAT_CONV_D    0x%08X (%f) = 0x%016llX (%f)\n", output, output_f, input, input_f);
	return output;
}

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

bool FCMP_E_D(double left, double right)
{
	bool result = left == right;
	debug("FCMP_E32_D      %d = %f == %f\n", result, left, right);
	return result;
}

bool FCMP_NE_D(double left, double right)
{
	bool result = left != right;
	debug("FCMP_NE32_D     %d = %f != %f\n", result, left, right);
	return result;
}

bool FCMP_GE_D(double left, double right)
{
	bool result = left >= right;
	debug("FCMP_GE32_D     %d = %f >= %f\n", result, left, right);
	return result;
}

bool FCMP_LE_D(double left, double right)
{
	bool result = left <= right;
	debug("FCMP_GE32_D     %d = %f <= %f\n", result, left, right);
	return result;
}

bool FCMP_UO_D(double left, double right)
{
	bool result = !(isnan(left) || isnan(right));
	debug("FCMP_UO32_D     %d = %f <= %f\n", result, left, right);
	return result;
}

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
    SREGTYPE a = reg_get_uint32("r0");
    SREGTYPE b = reg_get_uint32("r1");
    SREGTYPE result = a / b;
    REG_SET_ADDR("r0", result);
	debug("__aeabi_idiv() returns " FMT_SREG " = " FMT_SREG " / " FMT_SREG "\n", result, a, b);
}

void __aeabi_idivmod()
{
    SREGTYPE a = reg_get_uint32("r0");
    SREGTYPE b = reg_get_uint32("r1");
    SREGTYPE q = a / b;
    SREGTYPE r = a % b;
    REG_SET_ADDR("r0", q);
    REG_SET_ADDR("r1", r);
	debug("__aeabi_idivmod() returns q=" FMT_SREG " r=" FMT_SREG " " FMT_SREG " %% " FMT_SREG "\n",
		q, r, a, b);
}
#endif
