# Rhombus
a stack-less PDP-11-ish virtual machine inspired by ARM and RISCV. 

## instructions
| instruction type | arg | arg |
| ----------- | -------------- | --------------- |
| no argument | - | - |
| label | `@label` | - |
| register | `register` | - |
| memory | `[memroy]` | - |
| register-register | `register` | `register` |
| value-register | `$value` | `register` |
| register-memory | `register` | `[memory]` |


### control flow
| instruction | description |
| ----------- | ----------- |
| `mov src, dest` | copies data from source to destination |
| `cmpe src, dest` | compares source to destination. checks for equality |
| `cmps src, dest` | compares source to destination. checks for source being smaller |
| `jmp dest` | jumps to **program** instruction |
| `jmpe dest` | jumps to **program** instruction if result of the last instruction was `zero = true` |
| `jmpb dest` | jumps to **program** instruction if result of the last instruction was `zero = false` and `negative = overflow` |
| `jmps dest` | jumps to **program** instruction if result of the last instruction was `negative != overflow` |

### arithmetic
| instruction | description |
| ----------- | ----------- |
| `add src, dest` | addition |
| `sub src, dest` | subtraction |
| `shr src, dest` | shift right |
| `shl src, dest` | shift left |
| `xor src, dest` | xor |
| `or src, dest` | or |
| `and src, dest` | and |

## input and output
| instruction | description |
| ----------- | ----------- |
| `print src` | print register to IO |
| `scan dest` | scan from IO to register |

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
| `i0` | instruction pointer |
| `i1` | return address |
| `i2` | function argument |
| `i3` | function argument |
| `i4` | function argument |
| `i5` | function argument |
| `i6` | function argument |
| `i7` | function argument |
| `i8` | function argument |
| `i9` | general purpose |
| `i10` | general purpose |
| `i11` | general purpose |
| `i12` | general purpose |
| `i13` | general purpose |
| `i14` | general purpose |
| `i15` | general purpose |

# Examples

## basic repeater
```asm
; examples/repeater.rhom
@BEGINNING
    scan i9
    print i9
    jmp @BEGINNING
```
