import re
import struct

import lldb

#------------------------------------------------------------------------------
# string formatting
#------------------------------------------------------------------------------

def get_hex_dump(data, addr=0, grouping=1, endian='little', color=False):
    data = ''.join(map(chr, data))
    result = ''
    while(data):
        ascii = ''
        buff16 = data[0:16]
        data = data[16:]
        if color:
            result += "\x1b[0;33m%08X\x1b[0m " % addr
        else:
            result += "%08X: " % addr
        i = 0
        while i < 16:
            if i+grouping <= len(buff16):
                f0 = { \
                    'big':    {1:'>B', 2:'>H', 4:'>I', 8:'>Q'}, \
                    'little': {1:'<B', 2:'<H', 4:'<I', 8:'<Q'} \
                }
                f1 = { \
                    1:'%02X ', 2:'%04X ', 4:'%08X ', 8:'%016X ' \
                }
                temp = struct.unpack(f0[endian][grouping], buff16[i:i+grouping])[0]
                if color and temp==0:
                    result += '\x1b[0;34m' + (f1[grouping] % temp) + '\x1b[0m'
                else:
                    result += f1[grouping] % temp
                for j in range(grouping):
                    char = buff16[i+j]

                    if(char >= ' ' and char <= '~'):
                        ascii += char
                    else:
                        if color and char=='\x00':
                            ascii += '\x1b[0;34m.\x1b[0m'
                        else:
                            ascii += '.'
            else:
                if grouping == 1:
                    result += ' '*3
                elif grouping == 2:
                    result += ' '*5
                elif grouping == 4:
                    result += ' '*9
                elif grouping == 8:
                    result += ' '*17
            i += grouping
        result += ' %s\n' % ascii
        addr += 16;

    return result

#------------------------------------------------------------------------------
# access VM mem, regs, etc.
#------------------------------------------------------------------------------

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

#------------------------------------------------------------------------------
# print junk
#------------------------------------------------------------------------------

def print_vm_stack():
    mem = get_vm_mem()
    #print(get_vm_map('vm_regs'))
    rsp = get_vm_map('vm_regs')['rsp']

    ptr = rsp - 32
    ptr = (ptr >> 4) << 4

    print(get_hex_dump(mem[ptr:], addr=ptr, grouping=4, endian='little', color=True))

def print_map_016X(foo):
    for (key, val) in foo.items():
        print('%s: %016X' % (key, val))

def print_map_1(foo):
    for (key, val) in foo.items():
        print('%s: %d' % (key, val))

def print_vm_regs():
    print_vm_map('vm_regs')

def print_vm_context():
    tmp = get_vm_map('vm_regs')
    if tmp:
        print('-regs------------')
        print_map_016X(tmp)

    tmp = get_vm_map('vm_flags')
    if tmp:
        print('-flags-----------')
        print_map_1(tmp)

    tmp = get_vm_map('vm_regs_temp')
    if tmp:
        print('-temp------------')
        print_map_016X(tmp)

    tmp = get_vm_map('vm_regs')
    if tmp:
        print('-regs------------')
        print_map_016X(tmp)

    print('-stack----------')
    print_vm_stack()

#------------------------------------------------------------------------------
# hookup with lldb
#------------------------------------------------------------------------------

def vm(debugger, command, result, internal_dict):
    import lldb
    print_vm_context()

# And the initialization code to add your commands
# install with command script import go.py
def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand('command script add -f lldb_x64.vm vm')
    print 'The "vm" python command has been installed and is ready for use.'
