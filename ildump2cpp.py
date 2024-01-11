#!/usr/bin/env python

import os
import re
import sys
import struct
from subprocess import Popen, PIPE

import binaryninja
from binaryninja import core
from binaryninja import binaryview
from binaryninja import lowlevelil

from binaryninja.enums import LowLevelILOperation

arch = None
bv = None
init_mem_lines = []
current_llil = None

def shellout(cmd):
    process = Popen(cmd, stdout=PIPE, stderr=PIPE)
    (stdout, stderr) = process.communicate()
    stdout = stdout.decode("utf-8")
    stderr = stderr.decode("utf-8")
    process.wait()
    return (stdout, stderr)

# return size of il in bits
def get_il_size(il):
    if isinstance(il, lowlevelil.ILRegister):
        if il.name.startswith('temp'):
            return 8
        else:
            return il.info.size
    elif isinstance(il, lowlevelil.ILFlag):
        return 0
    elif type(il) == int:
        return 0
    elif type(il) == float:
        return 0
    else:
        return il.size

def get_il_size_token(il, prefix=''):
    sz = get_il_size(il)
    if not sz: return ''
    if il.operation.name in ['LLIL_FLOAT_CONV', 'LLIL_FADD', 'LLIL_FSUB', 'LLIL_FMUL', 'LLIL_FDIV']:
        return prefix + {2: 'H', 4:'S', 8:'D', 16:'T'}[il.size]
    else:
        return prefix + {1:'B', 2:'W', 4:'D', 8:'Q', 10:'T', 16:'O'}[il.size]

def traverse_IL(il, depth=0):
    # il pass thru here will probably be:
    # LowLevelILInstruction
    # LowLevelILRegister
    # LowLevelILFlag

    global bv
    global init_mem_lines
    semi = True

    if isinstance(il, lowlevelil.LowLevelILInstruction):
        opname = il.operation.name
        if opname.startswith('LLIL_'):
            opname = opname[5:]

        if opname in ['CALL', 'TAILCALL']:
            print('%s(' % opname, end='')
            traverse_IL(il.operands[0], depth+1)
            print(', ', end='')

            handled = False
            oper = il.operands[0]
            addr = None
            if oper.operation == LowLevelILOperation.LLIL_EXTERN_PTR:
                addr = oper.operands[0]
            elif oper.operation == LowLevelILOperation.LLIL_CONST_PTR:
                addr = oper.constant

            if addr != None:
                #print('// got addr: 0x%X\n' % addr)
                sym = bv.get_symbol_at(addr)

                if sym and sym.full_name:
                    #print('// %s    sym.full_name: %s' % (str(il), sym.full_name))
                    #print('\tSET_REG("r0", MODU(REG("r0"), REG("r1")))', end='')
                    func_name = sym.full_name.split('(',1)[0]
                    print('%s, "%s"' % (func_name, func_name), end='')
                    handled = True
                else:
                    func_name = 'sub_%X' % addr
                    print('sub_%X, "%s"' % (addr, func_name), end='')
                    handled = True

            if not handled:
                raise Exception('unable to handle CALL: %s and %s' % (str(il), str(il.operands[0].operation)))

            print(')', end='')

        elif opname == 'CONST':
            val = il.operands[0]
            if val < 16:
                #print('/* CONST */ %d' % val, end='')
                print('%d' % val, end='')
            else:
                #print('/* CONST */ 0x%X' % val, end='')
                print('0x%X' % val, end='')

        elif opname == 'CONST_PTR':
            # is it a jump table? rip it
            sym = bv.get_symbol_at(il.operands[0])
            dvar = bv.get_data_var_at(il.operands[0])
            if sym and sym.name.startswith('jump_table_') and dvar:
                strdv = str(dvar.type)
                m = re.match(r'^uint32_t ?\[(.+)\]$', strdv)
                if not m:
                    raise Exception('dunno how to parse type from: -%s-' % strdv)
                amt = m.group(1)
                if amt.startswith('0x'):
                    amt = int(amt, 16)
                else:
                    amt = int(amt)
                init_mem_lines.append('/* %s */' % str(sym))
                for i in range(amt):
                    addr = sym.address + 4*i
                    value = struct.unpack('<I', bv.read(addr, 4))[0]
                    line = '*(uint32_t *)(vm_mem + 0x%X) = 0x%X;' % (addr, value)
                    init_mem_lines.append(line)

            #print('/* CONST_PTR */ 0x%X' % (il.operands[0]), end='')
            print('0x%X' % (il.operands[0]), end='')

        elif opname == 'GOTO':
            print('goto loc_%d' % il.operands[0], end='')

        elif opname == 'IF':
            print('if(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(')')
            print('\t\tgoto loc_%d;' % il.operands[1])
            print('\telse')
            print('\t\tgoto loc_%d;' % il.operands[2], end='')
            semi = False

        elif opname == 'JUMP':
            print('if(JUMP(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(') == RETURN_TRUE) return', end='')

        elif opname == 'JUMP_TO':
            print('switch(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(')', end='')
            print('\t{')
            for (val, target_il) in il.operands[1].items():
                print('\t\t// val=%s target_il=%s' % (str(val), str(target_il)))
                target_native = current_llil[target_il].address
                print('\t\tcase 0x%X: goto loc_%d;' % (target_native, target_il))
            print('\t\tdefault: printf("switch fucked\\n"); __builtin_debugtrap();')
            print('\t}', end='')
            semi = False

        elif opname == 'RET':
            print('RET(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(');\n\treturn', end='')

        else:
            size_token = get_il_size_token(il, '_')
            if opname in ['DIVS_DP', 'MODS_DP']:
                size_token = ''

            extra_size_clue = ''
            if opname in ['SX']:
                extra_size_clue = get_il_size_token(il.operands[0], '_').lower()

            print(f'{opname}{size_token}{extra_size_clue}(', end='')

            for (i,o) in enumerate(il.operands):
                traverse_IL(o, depth+1)
                if i < len(il.operands)-1:
                    print(', ', end='')

            print(')', end='')

    elif isinstance(il, lowlevelil.ILRegister):
        print('"%s"'%il, end='')

    elif isinstance(il, lowlevelil.ILFlag):
        print('"%s"'%il, end='')

    else:
        print(str(il), end='')
        #print(str(il)+('[%s]'%type(il)), end='')

    if depth==0 and semi:
        print(';', end='')

def usage():
    print('usage: %s <filepath> [<arch>]' % sys.argv[0])
    print('')
    print('examples:')
    print('    %s tests.o' % sys.argv[0])
    print('    %s tests.o arm' % sys.argv[0])
    print('    %s tests.elf z80' % sys.argv[0])
    print('')
    sys.exit(-1)

if __name__ == '__main__':
    binaryninja._init_plugins()

    # arg1: path to object file from which to extract IL
    if sys.argv[1:]:
        fpath = sys.argv[1]
    else:
        usage()

    # arg2: architecture 'x64', 'arm', 'a64'
    arch = ''
    if sys.argv[2:]:
        arch = sys.argv[2]

    print('// %s' % shellout(['file', fpath])[0])

    bv = binaryninja.BinaryViewType.get_view_of_file(fpath)
    bv.update_analysis_and_wait()

    assert bv.end < (16*1024) # VM_MEM_SZ

    print('#include <stdint.h>')
    print('')
    print('#include <string>')
    print('#include <vector>')
    print('#include <map>')
    print('using namespace std;')
    print('')
    print('#include "runtime.h"')
    print('')
    print('extern uint8_t vm_mem[VM_MEM_SZ];')
    print('')

    # function prototypes
    for func in bv.functions:
        prototype = ''.join(map(lambda x: x.text, func.type_tokens))
        m = re.match(r'^.* (.*)\(.*\)', prototype)
        if not m:
            print('malformed function prototype: %s' % prototype)
        func_name = m.group(1)
        print('void %s(void);' % func_name)
    print('')

    # loop over binaryninja.function.Function
    for func in bv.functions:
        #print('// function %s()' % func.name)
        prototype = ''.join(map(lambda x: x.text, func.type_tokens))
        funcName = re.match(r'^.* (.*)\(.*\)', prototype).group(1)

        print('/* %s */' % prototype)
        print('void %s(void)' % funcName)
        print('{')

        blocks = list(func.low_level_il.basic_blocks)
        for block in blocks:
            print('\tloc_%d:' % block.start)

            # loop over binaryninja.basicblock.BasicBlock
            for insn in block:
                current_llil = func.low_level_il
                #print('\truntime_comment("%s\\n");' % str(insn))
                print('\t// %s' % str(insn))
                print('\t', end='')
                traverse_IL(insn)
                print('')

            # newline to separate blocks
            if block != blocks[-1]:
                print('')

        print('}')
        print('')

    #
#    print('const char *bv_image =')
#    tmp = bv.read(bv.start, bv.end)
#    while tmp:
#        chunk_sz = min(16, len(tmp))
#        print('\t"' + ''.join(['\\x%02x'%b for b in tmp[0:chunk_sz]]) + '"')
#        tmp = tmp[chunk_sz:]
#    print(';')

    print('void initialize_memory()')
    print('{')
    print('\tmemset(vm_mem, 0, VM_MEM_SZ);')
#    print('\tmemcpy(vm_mem+0x%X, bv_image, %d);' % (bv.start, bv.end-bv.start))
    print('\t' + '\n\t'.join(init_mem_lines))
    print('}\n')

    # what other stuff would a runtime need to execute the IL?

    # see architecture.py
#        self.__dict__["name"] = core.BNGetArchitectureName(self.handle)
#        self.__dict__["endianness"] = Endianness(core.BNGetArchitectureEndianness(self.handle))
#        self.__dict__["address_size"] = core.BNGetArchitectureAddressSize(self.handle)
#        self.__dict__["default_int_size"] = core.BNGetArchitectureDefaultIntegerSize(self.handle)
#        self.__dict__["instr_alignment"] = core.BNGetArchitectureInstructionAlignment(self.handle)
#        self.__dict__["max_instr_length"] = core.BNGetArchitectureMaxInstructionLength(self.handle)
#        self.__dict__["opcode_display_length"] = core.BNGetArchitectureOpcodeDisplayLength(self.handle)
#        self.__dict__["stack_pointer"] = core.BNGetArchi

    # emit register info (so runtime can know that (for example) writes to eax affect rax)
    # see definition of RegisterInfo in il_runtime.h
    print('map<string,struct RegisterInfo> reg_infos = {')
    for (regName,regInfo) in bv.arch.regs.items():
        print('\t{"%s", {%d, "%s", %d, %d, %d}}, /* %s */' % \
            (regName, int(regInfo.index), regInfo.full_width_reg, regInfo.offset, regInfo.size, regInfo.extend, repr(regInfo))
        )
    print('};')
    print('')

    # emit stack register name
    print('string stack_reg_name = "%s";' % bv.arch.stack_pointer)
    # emit whether architecture uses a link register
    if bv.arch.link_reg:
        print('bool is_link_reg_arch = true;')
        print('string link_reg_name = "%s";' % bv.arch.link_reg)
    else:
        print('bool is_link_reg_arch = false;')
        print('string link_reg_name = "(error)";')

