import re
import struct

import lldb

def get_vm_map(name):
    result = {}

    var = lldb.target.FindFirstGlobalVariable(name)
    vstr = str(var)
    for m in re.finditer(r'\(first = "(.*?)", second = (.*?)\)', vstr):
        (var, val) = m.group(1, 2)
        result[var] = int(val, 10)

    return result

def get_vm_mem():
    mem = lldb.target.FindFirstGlobalVariable("vm_mem")
    mem = mem.GetData()._read_all_uint8()
    return mem

def print_vm_stack():
    mem = get_vm_mem()
    print(get_vm_map('vm_regs'))
    sp = get_vm_map('vm_regs')['SP']
    while sp < 2048:
        word = (mem[sp+1] << 8) | mem[sp]
        print('%04X: %04X' % (sp, word))
        sp += 2

def print_map_04X(foo):
    for (key, val) in foo.items():
        print('%s: %04X' % (key, val))

def print_map_1(foo):
    for (key, val) in foo.items():
        print('%s: %d' % (key, val))

def print_vm_regs():
    print_vm_map('vm_regs')

def print_vm_context():
    tmp = get_vm_map('vm_regs')
    if tmp:
        print('-regs------------')
        print_map_04X(tmp)

    tmp = get_vm_map('vm_flags')
    if tmp:
        print('-flags-----------')
        print_map_1(tmp)

    tmp = get_vm_map('vm_regs_temp')
    if tmp:
        print('-temp------------')
        print_map_04X(tmp)

    tmp = get_vm_map('vm_regs')
    if tmp:
        print('-regs------------')
        print_map_04X(tmp)

    print('-stack----------')
    print_vm_stack()

def vm(debugger, command, result, internal_dict):
    import lldb
    print_vm_context()

# And the initialization code to add your commands
# install with command script import go.py
def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand('command script add -f lldb_z80.vm vm')
    print 'The "vm" python command has been installed and is ready for use.'
