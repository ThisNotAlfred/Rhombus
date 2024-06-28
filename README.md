# Rhombus
a minimal virtual machine inspired by arm amd riscv.

it's work in progress so please be patient. development might be slow.

## instructions

each instruction can be one of these forms:
| instruction | source argument | destination argument |
| ----------- | -------------- | --------------- |
| no register | - | - |
| one register mode | `register` | - |
| one register memory mode | `[memroy]` | - |
| two register mode | `source register` | `destination register` |
| two register immediate mode | `value` | `register` |
| two register memory mode | `register` | `[memory]` |

## register mode instructions

### control flow
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `mov` | two | copies data from source to destination |
| `cmpre` | two | compares source to destination. checks for equality |
| `cmprs` | two | compares source to destination. checks for source being smaller |
| `jmp` | one | jumps to determined **program** instruction |
| `jmpe` | one | jumps to determined **program** instruction if result of the last instruction was `zero = true` |
| `jmpb` | one | jumps to determined **program** instruction if result of the last instruction was `zero = false` and `negative = overflow` |
| `jmps` | one | jumps to determined **program** instruction if result of the last instruction was `negative != overflow` |

### arithmetic
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `add` | two | addition |
| `sub` | two | subtraction |
| `shr` | two | shift right |
| `shl` | two | shift left |
| `xor` | two | xor |
| `or` | two | or |
| `and` | two | and |

## immediate mode instructions

### control flow
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `mov_i` | two | copies data from source to destination |
| `cmpre_i` | two | compares source to destination. checks for equality |
| `cmprs_i` | two | compares source to destination. checks for source being smaller |

### arithmetic
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `add_i` | two | addition |
| `sub_i` | two | subtraction |
| `shr_i` | two | shift right |
| `shl_i` | two | shift left |
| `xor_i` | two | xor |
| `or_i` | two | or |
| `and_i` | two | and |


## memory mode instructions

### control flow
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `mov_m` | two | copies data from source to destination |
| `cmpre_m` | two | compares source to destination. checks for equality |
| `cmprs_m` | two | compares source to destination. checks for source being smaller |

### arithmetic
| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `add_m` | two | addition |
| `sub_m` | two | subtraction |
| `shr_m` | two | shift right |
| `shl_m` | two | shift left |
| `xor_m` | two | xor |
| `or_m` | two | or |
| `and_m` | two | and |

## input and output

| instruction | number of arguments | description |
| ----------- | ------------------- | ----------- |
| `print` | one | print register to IO |
| `print_m` | one | print memory to IO |
| `scan` | one | scan from IO to register |
| `scan_m` | one | scan from IO to memory |

## flags 

| flag | description |
| ---- | ----------- |
| `negative` | if result of the last operation was negative, set to `true` |
| `zero` | if result of the last operation was zero, set to `true` |
| `overflow` | if result of the last operation caused **signed overflow**, set to `true` |
| `carry` | if result of the last operation caused **unsigned overflow**, set to `true` |

## memory

the machine has 64KB of fixed-size memory that you have direct access. your program is **separate** and doesn't take anything from it.

## registers

> purposes are just convention and are not enforced.

| register | purpose |
| -------- | ------- |
| i0 | instruction pointer |
| i1 | return address |
| i2 | function argument |
| i3 | function argument |
| i4 | function argument |
| i5 | function argument |
| i6 | function argument |
| i7 | function argument |
| i8 | function argument |
| i9 | general purpose |
| i10 | general purpose |
| i11 | general purpose |
| i12 | general purpose |
| i13 | general purpose |
| i14 | general purpose |
| i15 | general purpose |

# Examples

## basic hello world

> don't program like this for Rhombus!

```asm
mov_i 72 , i9
mov_i 69 , i10
mov_i 76 , i11
mov_i 79 , i12
mov_i 32 , i13
mov_i 87 , i14
mov_i 82 , i15
mov_i 68 , i8

print i9
print i10
print i11
print i11
print i12
print i13
print i14
print i12
print i15
print i11
print i8
```
