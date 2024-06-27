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
| `jmpe` | one | jumps to determined **program** instruction if result of the last instruction was `ZeroFlag = true` |
| `jmpb` | one | jumps to determined **program** instruction if result of the last instruction was `ZeroFlag = false` and `NegativeFlag = OverflowFlag` |
| `jmps` | one | jumps to determined **program** instruction if result of the last instruction was `NegativeFlag != OverflowFlag` |

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

### flags 

| flag | description |
| ---- | ----------- |
| `NegativeFlag` | if result of the last operation was negative, set to `true` |
| `ZeroFlag` | if result of the last operation was zero, set to `true` |
| `OverflowFlag` | if result of the last operation caused **signed overflow**, set to `true` |
| `CarryFlag` | if result of the last operation caused **unsigned overflow**, set to `true` |

## memory

the machine has 128KB of fixed-size memory that you can access 64KB through direct access. your program is **separate** and doesn't take anything from it.

## registers

you have access to 8 of 16bit integer registers. you can access them through i0 to i15.
> purposes are just conventions and are not enforces.

| register | purpose |
| -------- | ------- |
| i0 | return address |
| i1 | function register |
| i2 | function register |
| i3 | function register |
| i4 | function register |
| i5 | genral purpose |
| i6 | general purpose |
| i7 | general purpose |
| i8 | general purpose |
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
