# Rhombus
a minimal virtual machine inspired by arm amd riscv.

it's work in progress so please be patient. development might be slow.

## instructions

each instruction can be one of these forms:
| instruction | first register | second register |
| ----------- | -------------- | --------------- |
| no register | - | - |
| one register | `[memroy cell]` | - |
| two register | `value` | `[memory cell]` |

### list of instructions

| instruction | description | example |
| ----------- | ----------- | ------- |
| `mov` | moving data to determined memory cell | `mov 12 , [256]` |
| `add` | adding data to determined memory cell | `add 13 , [54]` |
| `sub` | subtracting data from determined memory cell | `sub 14 , [124]` |
| `shr` | shifting right data at determined memory cell by value | `shr 15 , [1]` |
| `shl` | shifting left data at determined memory cell by value | `shl 16 , [45]` |
| `xor` | xor-ing data at determined memory cell by value | `xor 17 , [34]` |
| `or` | or-ing data to determined memory cell by value | `or 18 , [5]` |
| `and` | and-ing data to determined memory cell by value | `and 1 , [1]` |
| `cmpre` | compareing data to determined memory cell for equality | `cmpre 23, [23]` |
| `cmprs` | comparing data to detemined memory cell for **value** being smaller | `cmprs 23, [45]` |
| `jmp` | jumping to determined **program** cell unconditionally | `jmp [0]` |
| `jmpe` | jumping to determined **program** cell if result of the last instruction was `ZeroFlag = true` | `jmpe [132]` |
| `jmpb` | jumping to determined **program** cell if result of the last instruction was `ZeroFlag = false` and `NegativeFlag = OverflowFlag` | `jmpb [124]` |
| `jmps` | jumping to determined **program** cell if result of the last instruction was `NegativeFlag != OverflowFlag` | `jmps [234]` |
| `scan` | scan data from io to determined memory cell | `scan [122]` |
| `print` | print data to io from determined memory cell | `print [112]` |
| `nop` | no operation | `nop` |

### list of flags 

| flag | description |
| ---- | ----------- |
| `NegativeFlag` | if result of the last operation was negative, set to `true` |
| `ZeroFlag` | if result of the last operation was zero, set to `true` |
| `OverflowFlag` | if result of the last operation caused **signed overflow**, set to `true` |
| `CarryFlag` | if result of the last operation caused **unsigned overflow**, set to `true` |

## memory

the machine has 128KB of fixed-size memory that you can access. your **appends** to this amount and doesn't take anything from it.