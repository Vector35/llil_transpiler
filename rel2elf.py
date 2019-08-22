#!/usr/bin/env python
#
# convert SDCC .rel files to 32-bit ELF relocatable
#
# resulting file is simple:
#
# ------------------------
# ELF header
# ------------------------
# .text section
# .shstrtab section
# .strtab section
# .symtab section
# ------------------------
# NULL elf32_shdr
# .text elf32_shdr
# .shstrtab elf32_shdr
# .symtab elf32_shdr
# .strtab elf32_shdr
# ------------------------

import os
import re
import sys
from struct import pack

#------------------------------------------------------------------------------
# ELF helpers
#------------------------------------------------------------------------------

(PF_X, PF_W, PF_R) = (1,2,4)
(SHT_NULL, SHT_PROGBITS, SHT_STRTAB) = (0,1,3)

sz_ehdr = 0x34
sz_shdr = 0x28

def align(fp, to=4, pad=b'\x00'):
    while fp.tell() % to:
        fp.write(pad)

#------------------------------------------------------------------------------
# read .rel file
#------------------------------------------------------------------------------
fpath = sys.argv[1]
assert fpath.endswith('.rel')

code_area = None
rel_syms = []

with open(fpath) as fp:
    for line in fp.readlines():
        # AREA line -> create a section
        match = re.match(r'A _CODE size (.*) flags (.*) addr (.*)', line)
        if match:
            (size, flags, addr) = (int(x, 16) for x in match.group(1, 2, 3))
            assert flags == 0
            assert addr == 0
            print('detected _CODE area [%04X, %04X)' % (addr, addr + size))
            code_area = [b'\x00'] * size
            continue
    
        # WRITE line -> write bytes to section
        match = re.match(r'^T (.. ..) (.*)', line)
        if match:
            (addr, data) = match.group(1, 2)
            # eg: "04 00" -> 0x0004
            addr = int(addr[3:5] + addr[0:2], 16)
            # eg: "AA BB CC DD" -> b'\xAA\xBB\xCC\xDD'
            print('writing %04X: %s' % (addr, data))
            for (offset, byte) in enumerate(data.split(' ')):
                code_area[addr + offset] = pack('B', int(byte,16))
            continue 
    
        # SYMBOL line -> store
        match = re.match(r'^S (.+) Def(.*)', line)
        if match:
            (name, addr) = match.group(1, 2)
            if not name in ['.__.ABS.', '.  .ABS']:
                addr = int(addr, 16)
                print('saving symbol %s @ %X' % (name, addr))
                rel_syms.append((name, addr))
                continue

assert code_area
assert rel_syms

#------------------------------------------------------------------------------
# write ELF
#------------------------------------------------------------------------------

# process symbols, build string table
rel_syms = sorted(rel_syms, key=lambda name_addr: name_addr[1])
func2size = {}
func2stroffs = {}
strtab  = b'\x00'
for i in range(len(rel_syms)):
    (name, addr) = rel_syms[i]

    if i == len(rel_syms)-1:
        func2size[name] = len(code_area) - addr
    else:
        func2size[name] = rel_syms[i+1][1] - addr

    func2stroffs[name] = len(strtab)
    strtab = strtab + name.encode('utf-8') + b'\x00'

    print('%04X: %s size %X' % (addr, name, func2size[name]))

fpath = fpath + '.elf'
print('writing %s' % fpath)
fp = open(fpath, 'wb')

# elf32_hdr (placeholder, we'll come back to fill in offsets)
print('elf32_hdr @ %X' % fp.tell())
fp.write(b'\x00' * sz_ehdr)

# .text section contents
o_text = fp.tell()
print('placing .text @ %X' % o_text)
for byte in code_area:
    fp.write(byte)
sz_text = fp.tell() - o_text

# .shstrtab section contents
scn_shstrtab = b'\x00.text\x00.shstrtab\x00.symtab\x00.strtab\x00'
align(fp)
o_shstrtab = fp.tell()
print('placing .shstrtab @ %X' % o_shstrtab)
fp.write(scn_shstrtab)
sz_shstrtab = fp.tell() - o_shstrtab

# .symtab section contents
align(fp)
o_symtab = fp.tell()
print('placing .symtab @ %X' % o_symtab)
for (name, addr) in rel_syms:
    st_name = func2stroffs[name]
    st_value = addr
    st_size = func2size[name]
    st_info = 0x12 # bind:1(GLOBAL) type:2(FUNC)
    st_other = 0
    st_shndx = 0x1 # section header index: 0'th: NULL 1'th: .text
    Elf32_Sym = pack('<IIIBBH', st_name, st_value, st_size, st_info, st_other, st_shndx)
    fp.write(Elf32_Sym)
sz_symtab = fp.tell() - o_symtab

# .strtab section contents
align(fp)
o_strtab = fp.tell()
print('placing .strtab @ %X' % o_strtab)
fp.write(strtab)
sz_strtab = fp.tell() - o_strtab

# null section header (index 0)
align(fp)
o_shdr_null = fp.tell()
print('placing shdr NULL @ %X' % o_shdr_null)
fp.write(b'\x00' * sz_shdr)

# .text section header (index 1)
o_shdr_text = fp.tell()
print('placing shdr .text @ %X' % fp.tell())
sh_name = scn_shstrtab.index(b'.text')
sh_type = 1 # SHT_PROGBITS
sh_flags = 6 # ALLOC|EXECINSTR
sh_addr = 0
sh_offset = o_text
sh_size = sz_text
sh_link = 0
sh_info = 0
sh_addralign = 4
sh_entsize = 0
tmp = pack('<IIIIIIIIII', \
  sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, \
  sh_addralign, sh_entsize)
fp.write(tmp)

# .shstrtab section header (index 2)
o_shdr_shstrtab = fp.tell()
print('placing shdr .shstrtab @ %X' % fp.tell())
sh_name = scn_shstrtab.index(b'.shstrtab')
sh_type = 3 #SHT_STRTAB
sh_flags = 0
sh_addr = 0
sh_offset = o_shstrtab
sh_size = sz_shstrtab
sh_link = 0
sh_info = 0
sh_addralign = 1
sh_entsize = 0
tmp = pack('<IIIIIIIIII', \
  sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, \
  sh_addralign, sh_entsize)
fp.write(tmp)

# .symtab section header (index 3)
o_shdr_symtab = fp.tell()
print('placing shdr .symtab @ %X' % fp.tell())
sh_name = scn_shstrtab.index(b'.symtab')
sh_type = 2 #SHT_SYMTAB
sh_flags = 0
sh_addr = 0
sh_offset = o_symtab
sh_size = sz_symtab
sh_link = 4 # link to scn #4 (find strings in .strtab)
sh_info = 0
sh_addralign = 4
sh_entsize = 0
tmp = pack('<IIIIIIIIII', \
  sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, \
  sh_addralign, sh_entsize)
fp.write(tmp)

# .strtab section header (index 4)
o_shdr_strtab = fp.tell()
print('placing shdr .strtab @ %X' % fp.tell())
sh_name = scn_shstrtab.index(b'.strtab')
sh_type = 3 #SHT_STRTAB
sh_flags = 0
sh_addr = 0
sh_offset = o_strtab
sh_size = sz_strtab
sh_link = 0
sh_info = 0
sh_addralign = 1
sh_entsize = 0
tmp = pack('<IIIIIIIIII', \
  sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, \
  sh_addralign, sh_entsize)
fp.write(tmp)

# seek back, write real elf header
hdr = b'\x7FELF'
hdr += b'\x01' # e_ident[EI_CLASS] 32-bit
hdr += b'\x01' # e_ident[EI_DATA] LSB (little-end)
hdr += b'\x01\x00\x00' # version, osabi, abiversion
hdr += b'\x00'*7
assert len(hdr) == 16
hdr += pack('<H', 1)           # e_type = ET_REL
hdr += pack('<H', 220)         # e_machine = EM_Z80
hdr += pack('<I', 1)           # e_version = EV_CURRENT
hdr += pack('<I', 0)           # e_entry
hdr += pack('<I', 0)           # e_phoff
hdr += pack('<I', o_shdr_null) # e_shoff
hdr += pack('<I', 0)           # e_flags
hdr += pack('<H', sz_ehdr)     # e_ehsize
hdr += pack('<H', 0)           # e_phentsize
hdr += pack('<H', 0)           # e_phnum
hdr += pack('<H', sz_shdr)     # e_shentsize
hdr += pack('<H', 5)           # e_shnum
hdr += pack('<H', 2)           # e_shstrndx = index of .shstrtab
assert len(hdr) == sz_ehdr
fp.seek(0, os.SEEK_SET)
fp.write(hdr)

# done!
fp.close()

