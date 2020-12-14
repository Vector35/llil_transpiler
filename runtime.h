#define VM_MEM_SZ 2048

#ifdef ARCH_64BIT
	#define REGWIDTH 64
	#define REGTYPE uint64_t /* register type */
	#define SREGTYPE int64_t /* signed register type */
	#define REGTYPE_HALF uint32_t /* half register type */
	#define SREGTYPE_HALF int32_t
#endif

#ifdef ARCH_32BIT
	#define REGWIDTH 32
	#define REGTYPE uint32_t /* register type */
	#define SREGTYPE int32_t /* signed register type */
	#define REGTYPE_HALF uint16_t /* half register type */
	#define SREGTYPE_HALF int16_t
#endif

#ifdef ARCH_16BIT
	#define REGWIDTH 16
	#define REGTYPE uint16_t /* register type */
	#define SREGTYPE int32_t /* signed register type */
	#define REGTYPE_HALF uint8_t /* half register type */
	#define SREGTYPE_HALF int8_t
#endif
	
#define PREGTYPE (REGTYPE *) /* pointer to register type */
#define REGMASK (~0) /* eg: 0xFFFF */
#define REGMASKLOHALF (( (REGTYPE)1 << (REGWIDTH/2) )-1)	/* eg: 0x00FF */
#define REGMASKHIHALF (REGMASKLOHALF<<(REGWIDTH/2)) /* eg: 0xFF00 */
#define PREGTYPE_HALF (REGTYPE_HALF *)

#if REGWIDTH == 64
	#define FMT_REG "0x%llX"
	#define FMT_REG_HALF "0x%X"
	#define FMT_SREG "0x%llX"
#elif REGWIDTH == 32
	#define FMT_REG "0x%X"
	#define FMT_REG_HALF "0x%X"
	#define FMT_SREG "%d"
#elif REGWIDTH == 16
	#define FMT_REG "0x%04X"
	#define FMT_REG_HALF "0x%02X"
	#define FMT_SREG "%d"
#endif

struct RegisterInfo {
	int index; /* register index */
	string full_width_reg; /* index of full-width register */
	int offset; /* offset within full-width register */
	int size; /* in bytes */
	int extend; /* zero or sign */
};

/* LowLevelILOperation.LLIL_NOP: [] */
void NOP(void);

/* LowLevelILOperation.LLIL_SET_REG: [("dest", "reg"), ("src", "expr")] */
void SET_REG1(string dest, uint8_t src);
void SET_REG2(string dest, uint16_t src);
void SET_REG4(string dest, uint32_t src);
void SET_REG8(string dest, uint64_t src);

/* LowLevelILOperation.LLIL_SET_REG_SPLIT: [("hi", "reg"), ("lo", "reg"), ("src", "expr")] */
void SET_REG_SPLIT(string hi, string lo, REGTYPE src);

/* LowLevelILOperation.LLIL_SET_REG_STACK_REL: [("stack", "reg_stack"), ("dest", "expr"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_PUSH: [("stack", "reg_stack"), ("src", "expr")] */

/* LowLevelILOperation.LLIL_SET_FLAG: [("dest", "flag"), ("src", "expr")] */
void SET_FLAG(string left, bool right);

/* LowLevelILOperation.LLIL_LOAD: [("src", "expr")] */
uint8_t LOAD1(REGTYPE expr);
uint16_t LOAD2(REGTYPE expr);
uint32_t LOAD4(REGTYPE expr);
uint64_t LOAD8(REGTYPE expr);

/* LowLevelILOperation.LLIL_STORE: [("dest", "expr"), ("src", "expr")] */
void STORE1(REGTYPE dest, uint8_t src);
void STORE2(REGTYPE dest, uint16_t src);
void STORE4(REGTYPE dest, uint32_t src);
void STORE8(REGTYPE dest, uint64_t src);

/* LowLevelILOperation.LLIL_PUSH: [("src", "expr")] */
void PUSH(REGTYPE src);

/* LowLevelILOperation.LLIL_POP: [] */
REGTYPE POP(void);

/* LowLevelILOperation.LLIL_REG: [("src", "reg")] */
REGTYPE REG(string src);

/* LowLevelILOperation.LLIL_REG_SPLIT: [("hi", "reg"), ("lo", "reg")] */
REGTYPE REG_SPLIT(string hi, string lo);

/* LowLevelILOperation.LLIL_REG_STACK_REL: [("stack", "reg_stack"), ("src", "expr")] */
/* LowLevelILOperation.LLIL_REG_STACK_POP: [("stack", "reg_stack")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_REG: [("dest", "reg")] */
/* LowLevelILOperation.LLIL_REG_STACK_FREE_REL: [("stack", "reg_stack"), ("dest", "expr")] */
/* LowLevelILOperation.LLIL_CONST: [("constant", "int")] */
/* LowLevelILOperation.LLIL_CONST_PTR: [("constant", "int")] */
/* LowLevelILOperation.LLIL_EXTERN_PTR: [("constant", "int"), ("offset", "int")] */
SREGTYPE EXTERN_PTR(SREGTYPE constant, SREGTYPE offset);

/* LowLevelILOperation.LLIL_FLOAT_CONST: [("constant", "float")] */
/* LowLevelILOperation.LLIL_FLAG: [("src", "flag")] */
bool FLAG(string src);

/* LowLevelILOperation.LLIL_FLAG_BIT: [("src", "flag"), ("bit", "int")] */
/* LowLevelILOperation.LLIL_ADD: [("left", "expr"), ("right", "expr")] */
uint8_t ADD1(uint8_t left, uint8_t right);
uint16_t ADD2(uint16_t left, uint16_t right);
uint32_t ADD4(uint32_t left, uint32_t right);
uint64_t ADD8(uint64_t left, uint64_t right);

/* LowLevelILOperation.LLIL_ADC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
SREGTYPE ADC(SREGTYPE left, SREGTYPE right, bool carry);

/* LowLevelILOperation.LLIL_SUB: [("left", "expr"), ("right", "expr")] */
uint8_t SUB1(uint8_t a, uint8_t b);
uint16_t SUB2(uint16_t a, uint16_t b);
uint32_t SUB4(uint32_t a, uint32_t b);
uint64_t SUB8(uint64_t a, uint64_t b);

/* LowLevelILOperation.LLIL_SBB: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t SBB1(uint8_t a, uint8_t b, uint8_t c);
uint16_t SBB2(uint16_t a, uint16_t b, uint16_t c);
uint32_t SBB4(uint32_t a, uint32_t b, uint32_t c);
uint64_t SBB8(uint64_t a, uint64_t b, uint64_t c);

/* LowLevelILOperation.LLIL_AND: [("left", "expr"), ("right", "expr")] */
REGTYPE AND(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_OR: [("left", "expr"), ("right", "expr")] */
REGTYPE OR(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_XOR: [("left", "expr"), ("right", "expr")] */
REGTYPE XOR(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_LSL: [("left", "expr"), ("right", "expr")] */
REGTYPE LSL(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_LSR: [("left", "expr"), ("right", "expr")] */
REGTYPE LSR(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_ASR: [("left", "expr"), ("right", "expr")] */
SREGTYPE ASR(SREGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_ROL: [("left", "expr"), ("right", "expr")] */
uint8_t ROL1(uint8_t value, uint8_t amt);
uint16_t ROL2(uint16_t value, uint16_t amt);
uint32_t ROL4(uint32_t value, uint32_t amt);
uint64_t ROL8(uint64_t value, uint64_t amt);

/* LowLevelILOperation.LLIL_RLC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RLC1(uint8_t value, uint8_t amt, bool carry);

/* LowLevelILOperation.LLIL_ROR: [("left", "expr"), ("right", "expr")] */
uint8_t ROR1(uint8_t value, uint8_t amt);
uint16_t ROR2(uint16_t value, uint16_t amt);
uint32_t ROR4(uint32_t value, uint32_t amt);
uint64_t ROR8(uint64_t value, uint64_t amt);

/* LowLevelILOperation.LLIL_RRC: [("left", "expr"), ("right", "expr"), ("carry", "expr")] */
uint8_t RRC1(uint8_t value, uint8_t amt, bool carry);

SREGTYPE MUL(SREGTYPE left, SREGTYPE right);

/* LowLevelILOperation.LLIL_MULU_DP: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_MULS_DP: [("left", "expr"), ("right", "expr")] */

/* LowLevelILOperation.LLIL_DIVU: [("left", "expr"), ("right", "expr")] */
/* LowLevelILOperation.LLIL_DIVU_DP: [("left", "expr"), ("right", "expr")] */

/* LowLevelILOperation.LLIL_DIVS: [("left", "expr"), ("right", "expr")] */
SREGTYPE DIVS(SREGTYPE left, SREGTYPE_HALF right);

/* LowLevelILOperation.LLIL_DIVS_DP: [("left", "expr"), ("right", "expr")] */
SREGTYPE DIVS_DP(SREGTYPE left, SREGTYPE_HALF right);

/* LowLevelILOperation.LLIL_MODU: [("left", "expr"), ("right", "expr")] */
REGTYPE MODU(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_MODU_DP: [("left", "expr"), ("right", "expr")] */
REGTYPE MODU_DP(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_MODS: [("left", "expr"), ("right", "expr")] */
SREGTYPE MODS(SREGTYPE left, SREGTYPE right);

/* LowLevelILOperation.LLIL_MODS_DP: [("left", "expr"), ("right", "expr")] */
SREGTYPE MODS_DP(SREGTYPE left, SREGTYPE right);

/* LowLevelILOperation.LLIL_NEG: [("src", "expr")] */
uint8_t NEG1(uint8_t src);
uint16_t NEG2(uint16_t src);
uint32_t NEG4(uint32_t src);
uint64_t NEG8(uint64_t src);

/* LowLevelILOperation.LLIL_NOT: [("src", "expr")] */
uint8_t NOT0(uint8_t left);
uint8_t NOT1(uint8_t left);
uint16_t NOT2(uint16_t left);
uint32_t NOT4(uint32_t left);
uint64_t NOT8(uint64_t left);

/* LowLevelILOperation.LLIL_SX: [("src", "expr")] */
SREGTYPE SX1(int8_t src);
SREGTYPE SX2(int16_t src);
SREGTYPE SX4(int32_t src);

/* LowLevelILOperation.LLIL_ZX: [("src", "expr")] */
uint32_t ZX4(uint32_t src);
uint64_t ZX8(uint64_t src);

/* LowLevelILOperation.LLIL_LOW_PART: [("src", "expr")] */
uint8_t LOW_PART1(REGTYPE left);
uint16_t LOW_PART2(REGTYPE left);
uint32_t LOW_PART4(REGTYPE left);

/* LowLevelILOperation.LLIL_JUMP: [("dest", "expr")] */
void JUMP(REGTYPE dest);

/* LowLevelILOperation.LLIL_JUMP_TO: [("dest", "expr"), ("targets", "int_list")] */
/* LowLevelILOperation.LLIL_CALL: [("dest", "expr")] */
void CALL(REGTYPE dest, void (*)(void), const char *func_name);

/* LowLevelILOperation.LLIL_CALL_STACK_ADJUST: [("dest", "expr"), ("stack_adjustment", "int"), ("reg_stack_adjustments", "reg_stack_adjust")] */

/* LowLevelILOperation.LLIL_TAILCALL: [("dest", "expr")] */
void TAILCALL(REGTYPE dest, void (*)(void), const char *func_name);

/* LowLevelILOperation.LLIL_RET: [("dest", "expr")] */
void RET(REGTYPE dest);

/* LowLevelILOperation.LLIL_NORET: [] */
/* LowLevelILOperation.LLIL_IF: [("condition", "expr"), ("true", "int"), ("false", "int")] */
/* LowLevelILOperation.LLIL_GOTO: [("dest", "int")] */
/* LowLevelILOperation.LLIL_FLAG_COND: [("condition", "cond"), ("semantic_class", "sem_class")] */
/* LowLevelILOperation.LLIL_FLAG_GROUP: [("semantic_group", "sem_group")] */
/* LowLevelILOperation.LLIL_CMP_E: [("left", "expr"), ("right", "expr")] */
bool CMP_E(REGTYPE left, REGTYPE right);
/* LowLevelILOperation.LLIL_CMP_NE: [("left", "expr"), ("right", "expr")] */
bool CMP_NE(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_CMP_SLT: [("left", "expr"), ("right", "expr")] */
bool CMP_SLT1(int8_t left, int8_t right);
bool CMP_SLT2(int16_t left, int16_t right);
bool CMP_SLT4(int32_t left, int32_t right);

/* LowLevelILOperation.LLIL_CMP_ULT: [("left", "expr"), ("right", "expr")] */
bool CMP_ULT(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_CMP_SLE: [("left", "expr"), ("right", "expr")] */
bool CMP_SLE1(int8_t left, int8_t right);
bool CMP_SLE2(int16_t left, int16_t right);
bool CMP_SLE4(int32_t left, int32_t right);

/* LowLevelILOperation.LLIL_CMP_ULE: [("left", "expr"), ("right", "expr")] */
bool CMP_ULE(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_CMP_SGE: [("left", "expr"), ("right", "expr")] */
bool CMP_SGE1(int8_t left, int8_t right);
bool CMP_SGE2(int16_t left, int16_t right);
bool CMP_SGE4(int32_t left, int32_t right);

/* LowLevelILOperation.LLIL_CMP_UGE: [("left", "expr"), ("right", "expr")] */
bool CMP_UGE(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_CMP_SGT: [("left", "expr"), ("right", "expr")] */
bool CMP_SGT1(int8_t left, int8_t right);
bool CMP_SGT2(int16_t left, int16_t right);
bool CMP_SGT4(int32_t left, int32_t right);

/* LowLevelILOperation.LLIL_CMP_UGT: [("left", "expr"), ("right", "expr")] */
bool CMP_UGT(REGTYPE left, REGTYPE right);

/* LowLevelILOperation.LLIL_TEST_BIT: [("left", "expr"), ("right", "expr")] */
bool TEST_BIT(REGTYPE value, REGTYPE mask);

/* LowLevelILOperation.LLIL_BOOL_TO_INT: [("src", "expr")] */
/* LowLevelILOperation.LLIL_ADD_OVERFLOW: [("left", "expr"), ("right", "expr")] */
bool ADD_OVERFLOW1(uint8_t a, uint8_t b);
bool ADD_OVERFLOW2(uint16_t a, uint16_t b);
bool ADD_OVERFLOW4(uint32_t a, uint32_t b);

/* LowLevelILOperation.LLIL_SYSCALL: [] */
/* LowLevelILOperation.LLIL_INTRINSIC: [("output", "reg_or_flag_list"), ("intrinsic", "intrinsic"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_INTRINSIC_SSA: [("output", "reg_or_flag_ssa_list"), ("intrinsic", "intrinsic"), ("param", "expr")] */
/* LowLevelILOperation.LLIL_BP: [] */
/* LowLevelILOperation.LLIL_TRAP: [("vector", "int")] */
/* LowLevelILOperation.LLIL_UNDEF: [] */

/* LowLevelILOperation.LLIL_UNIMPL: [] */
REGTYPE UNIMPL(void);
REGTYPE UNIMPL(REGTYPE);

/* LowLevelILOperation.LLIL_UNIMPL_MEM: [("src", "expr")] */

/* LowLevelILOperation.LLIL_FADD: [("left", "expr"), ("right", "expr")] */
float FADD(float a, float b);

/* LowLevelILOperation.LLIL_FSUB: [("left", "expr"), ("right", "expr")] */
float FSUB(float a, float b);

/* LowLevelILOperation.LLIL_FMUL: [("left", "expr"), ("right", "expr")] */
float FMUL(float a, float b);

/* LowLevelILOperation.LLIL_FDIV: [("left", "expr"), ("right", "expr")] */
float FDIV(float a, float b);

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

void runtime_comment(const char *msg);

#ifdef ARCH_ARM
void __aeabi_idiv();
void __aeabi_idivmod();
#endif

