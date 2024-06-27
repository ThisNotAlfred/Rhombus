# Rhombus
a minimal virtual machine inspired by arm amd riscv.

it's work in progress so please be patient. development might be slow.

## instructions

each instruction can be one of these forms:
| instruction | first argument | second argument |
| ----------- | -------------- | --------------- |
| no argument | - | - |
| one argument memory mode | `[memroy cell]` | - |
| one argument register mode | `register` | - |
| two register mode | `source register` | `destination register` |
| two register immediate mode | `value` | `register` |
| two register memory mode | `register` | `[memory cell]` |

### list of instructions

| instruction | mode | description |
| ----------- | ---- | ----------- |
| `mov` | two register | copying data from source to dest |
| `mov_i` | two register immedaite | copying data from value to register |
| `mov_m` | two reigster memory | copying data from register to memory cell |
| `add` | two register | adding data to destination by source register |
| `add_i` | two register immediate | adding value to register |
| `add_m` | two register memory | adding register to determined memory cell |
| `sub` | two register | subtracting source from destination |
| `sub_i` | two register immediate | subtracting value from register |
| `sub_m` | two register memory | subtracting register from memory cell |
| `shr` | two register | shifting right destination by source |
| `shr_i` | two register immediate | shifting right register by value |
| `shr_m` | two register mempry | shfifiting right memory cell by register |
| `shl` | two register | shifting left destination by source |
| `shl_i` | two register immediate | shifting left register by value |
| `shl_m` | two register mempry | shfifiting left memory cell by register |
| `xor` | two register | xor-ing destination by source |
| `xor_i` | two register immedaite | xor-ing register by value |
| `xor_m` | two register memory | xor-ing memory cell by register |
| `or` | two register | or-ing destination by source |
| `or_i` | two register immedaite | or-ing register by value |
| `or_m` | two register memory | or-ing memory cell by register |
| `and` | two register | and-ing destination by source |
| `and_i` | two register immedaite | and-ing register by value |
| `and_m` | two register memory | and-ing memory cell by register |
| `cmpre` | two register | compareing source to destination for equality |
| `cmpre_i` | two register immediate | compareing register to value for equality |
| `cmpre_m` | two register memory | compareing register to memory cell for equality |
| `cmprs` | two register | compareing source to destination for source being smaller |
| `cmprs_i` | two register immediate | compareing register to value for register being smaller |
| `cmprs_m` | two register memory | compareing register to memory cell for register being smaller |
| `jmp` | one register memory | jumping to determined **program** instruction unconditionally |
| `jmpe` | one register memory | jumping to determined **program** instruction if result of the last instruction was `ZeroFlag = true` |
| `jmpb` | one register memory | jumping to determined **program** instruction if result of the last instruction was `ZeroFlag = false` and `NegativeFlag = OverflowFlag` |
| `jmps` | one register memory | jumping to determined **program** instruction if result of the last instruction was `NegativeFlag != OverflowFlag` |
| `scan` | one register | scan data from io to register |
| `scan_m` | one register memory | scan data from io to memory cell |
| `print` | one register | print data to io from register |
| `print_m` | one register memory | print data to io from memory cell |
| `nop` | no operation |

### list of flags 

| flag | description |
| ---- | ----------- |
| `NegativeFlag` | if result of the last operation was negative, set to `true` |
| `ZeroFlag` | if result of the last operation was zero, set to `true` |
| `OverflowFlag` | if result of the last operation caused **signed overflow**, set to `true` |
| `CarryFlag` | if result of the last operation caused **unsigned overflow**, set to `true` |

## memory

the machine has 128KB of fixed-size memory that you can access. your program is **separate** and doesn't take anything from it.

## registers

you have access to 8 of 16bit integer registers. you can access them through i0 to i7.

# Examples

## basic hello world

```asm
mov_i 72 , i0
mov_i 69 , i1
mov_i 76 , i2
mov_i 79 , i3
mov_i 32 , i4
mov_i 87 , i5
mov_i 82 , i6
mov_i 68 , i7

print i0
print i1
print i2
print i2
print i3
print i4
print i5
print i3
print i6
print i2
print i7
```
