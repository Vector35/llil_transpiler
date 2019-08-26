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
    #print('stdout: -%s-' % stdout)
    #print('stderr: -%s-' % stderr)
    process.wait()
    return (stdout, stderr)

def traverse_IL(il, depth=0):
    global bv
    global init_mem_lines
    semi = True

    sz2stdint = ['error']*9
    sz2stdint[1] = 'uint8_t'
    sz2stdint[2] = 'uint16_t'
    sz2stdint[4] = 'uint32_t'
    sz2stdint[8] = 'uint64_t'

    if isinstance(il, lowlevelil.LowLevelILInstruction):
        opname = il.operation.name
        if opname.startswith('LLIL_'):
            opname = opname[5:]

        traverse = True
        if il.operation == LowLevelILOperation.LLIL_UNIMPL:
            print('UNIMPL()', end='')
        elif il.operation == LowLevelILOperation.LLIL_GOTO:
            print('goto loc_%d' % il.operands[0], end='')
        elif il.operation == LowLevelILOperation.LLIL_LOAD:
            print('LOAD%d(' % il.size, end='')
            traverse_IL(il.operands[0], depth+1)
            print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_STORE:
            print('STORE%d(' % il.size, end='')
            traverse_IL(il.operands[0], depth+1)
            print(',', end='')
            traverse_IL(il.operands[1], depth+1)
            print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_SET_REG:
            print('SET_REG%d(' % il.size, end='')
            traverse_IL(il.operands[0], depth+1)
            print(',', end='')
            traverse_IL(il.operands[1], depth+1)
            print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_ADD:
            print('ADD%d(' % il.size, end='')
            traverse_IL(il.operands[0], depth+1)
            print(',', end='')
            traverse_IL(il.operands[1], depth+1)
            print(')', end='')
        elif opname.startswith('CMP_S'):
            print('%s%d(' % (opname, il.size), end='')
            traverse_IL(il.operands[0], depth+1)
            print(',', end='')
            traverse_IL(il.operands[1], depth+1)
            print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_RET:
            print('RET(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(');\n\treturn', end='')
        elif il.operation == LowLevelILOperation.LLIL_CONST:
            #print('(%s)%d' % (sz2stdint[il.size], il.operands[0]), end='')
            print('%d' % (il.operands[0]), end='')
        elif il.operation == LowLevelILOperation.LLIL_CONST_PTR:
            # is it a jump table? rip it
            sym = bv.get_symbol_at(il.operands[0])
            dvar = bv.get_data_var_at(il.operands[0])
            if sym and sym.name.startswith('jump_table_') and dvar:
                strdv = str(dvar.type)
                if not strdv.startswith('uint32_t '):
                    raise Exception('dunno how to parse type from: %s' % strdv)
                m = re.match(r'uint32_t \[(\d+)\]', strdv)
                amt = int(m.group(1))
                init_mem_lines.append('// %s' % str(sym))
                for i in range(amt):
                    addr = sym.address + 4*i
                    value = struct.unpack('<I', bv.read(addr, 4))[0]
                    line = '*(uint32_t *)(vm_mem + 0x%X) = 0x%X;' % (addr, value)
                    init_mem_lines.append(line)

            # TODO: this could be a pointer, eg "uin8_t *"
            #print('(%s)0x%X' % (sz2stdint[il.size], il.operands[0]), end='')
            print('0x%X' % (il.operands[0]), end='')
        elif il.operation == LowLevelILOperation.LLIL_IF:
            print('if(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(')')
            print('\t\tgoto loc_%d;' % il.operands[1])
            print('\telse')
            print('\t\tgoto loc_%d;' % il.operands[2], end='')
            semi = False
        elif il.operation == LowLevelILOperation.LLIL_SET_FLAG:
            print('SET_FLAG("%s", ' % il.operands[0], end='')
            traverse_IL(il.operands[1], depth+1)
            print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_FLAG:
            print('FLAG("%s")' % il.operands[0], end='')
        elif il.operation == LowLevelILOperation.LLIL_JUMP:
            if arch == 'arm' and \
              il.operands[0].operation == LowLevelILOperation.LLIL_REG and \
              il.operands[0].src.name == 'lr':
                  print('// %s' % str(il))
                  print('\treturn', end='')
            elif arch == 'arm' and \
              il.operands[0].operation == LowLevelILOperation.LLIL_POP:
                  print('// %s' % str(il))
                  print('\treturn', end='')
            else:
                print('JUMP(', end='')
                traverse_IL(il.operands[0], depth+1)
                print(')', end='')
        elif il.operation == LowLevelILOperation.LLIL_CALL:
            print('CALL(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(');')

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
                    print('// %s    sym.full_name: %s' % (str(il), sym.full_name))
                    #print('\tSET_REG("r0", MODU(REG("r0"), REG("r1")))', end='')
                    noparens = sym.full_name.split('(',1)[0]
                    print('\t%s()' % noparens, end='')
                    handled = True
                else:
                    print('\tsub_%X()' % addr, end='')
                    handled = True

            if not handled:
                raise Exception('unable to handle CALL: %s and %s' % (str(il), str(il.operands[0].operation)))

        elif il.operation == LowLevelILOperation.LLIL_JUMP_TO:
            print('// %s' % str(il))
            print('\tswitch(', end='')
            traverse_IL(il.operands[0], depth+1)
            print(')')
            print('\t{')
            for (val, target_il) in enumerate(il.operands[1]):
                target_native = current_llil[target_il].address
                print('\t\tcase 0x%X: goto loc_%d;' % (target_native, target_il))
            print('\t\tdefault: printf("switch fucked\\n"); while(1);')
            print('\t}', end='')
            semi = False
        else:
            #print('%s((%s)' % (opname, sz2stdint[il.size]), end='')
            print('%s(' % (opname), end='')

            for (i,o) in enumerate(il.operands):
                traverse_IL(o, depth+1)
                if i < len(il.operands)-1:
                    print(', ', end='')

            print(')', end='')
    elif isinstance(il, lowlevelil.ILRegister):
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
    # arg1: path to object file from which to extract IL
    if sys.argv[1:]:
        fpath = sys.argv[1]
    else:
        usage()

    # arg2: architecture 'x64', 'arm'
    arch = ''
    if sys.argv[2:]:
        arch = sys.argv[2]

    print('// %s' % shellout(['file', fpath])[0])

    bv = binaryninja.BinaryViewType.get_view_of_file(fpath)
    bv.update_analysis_and_wait()

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
        func_name = re.match(r'^.* (.*)\(.*\)$', prototype).group(1)
        print('void %s(void);' % func_name)
    print('')

    # loop over binaryninja.function.Function
    for func in bv.functions:
        #print('// function %s()' % func.name)
        prototype = ''.join(map(lambda x: x.text, func.type_tokens))
        funcName = re.match(r'^.* (.*)\(.*\)$', prototype).group(1)

        print('/* %s */' % prototype)
        print('void %s(void)' % funcName)
        print('{')

        il_addr = 0
        for block in func.low_level_il:
            print('\tloc_%d:' % block.start)

            # loop over binaryninja.basicblock.BasicBlock
            for insn in block:
                print('\t', end='')
                current_llil = func.low_level_il
                traverse_IL(insn)
                il_addr += 1
                print('')

            print('')

        print('}')
        print('')

    #
    print('void initialize_memory()')
    print('{')
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
    print('map<string,struct RegisterInfo> regInfos = {')
    for (regName,regInfo) in bv.arch.regs.items():
        print('\t{"%s", {%d, "%s", %d, %d, %d}}, /* %s */' % \
            (regName, int(regInfo.index), regInfo.full_width_reg, regInfo.offset, regInfo.size, regInfo.extend, repr(regInfo))
        )
    print('};')
    print('')

    # emit stack register name
    print('string stackRegName = "%s";' % bv.arch.stack_pointer)

