# Rhombus
a minimal virtual machine inspired by arm amd riscv.

it's work in progress so please be patient. development might be slow.

## instructions
| instruction | source argument | destination argument |
| ----------- | -------------- | --------------- |
| no register | - | - |
| one register mode | `register` | - |
| one register memory mode | `[memroy]` | - |
| two register mode | `source register` | `register` |
| two register immediate mode | `$value` | `register` |
| two register memory mode | `register` | `[memory]` |


### control flow
| instruction | description |
| ----------- | ----------- |
| `mov` | copies data from source to destination |
| `cmpe` | compares source to destination. checks for equality |
| `cmps` | compares source to destination. checks for source being smaller |
| `jmp` | jumps to **program** instruction |
| `jmpe` | jumps to **program** instruction if result of the last instruction was `zero = true` |
| `jmpb` | jumps to **program** instruction if result of the last instruction was `zero = false` and `negative = overflow` |
| `jmps` | jumps to **program** instruction if result of the last instruction was `negative != overflow` |

### arithmetic
| instruction | description |
| ----------- | ----------- |
| `add` | addition |
| `sub` | subtraction |
| `shr` | shift right |
| `shl` | shift left |
| `xor` | xor |
| `or` | or |
| `and` | and |

## input and output
| instruction | description |
| ----------- | ----------- |
| `print` | print register to IO |
| `scan` | scan from IO to register |

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
; HELLO WORLD
mov $72, i9
mov $69, i10
mov $76, i11
mov $79, i12
mov $32, i13
mov $87, i14
mov $82, i15
mov $68, i8

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
