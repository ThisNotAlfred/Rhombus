# Rhombus
a minimal virtual machine inspired by brainf**k and riscv32. 


it's work in progress so please be patient. development might be slow.


## instructions
each instruction can be one of these forms:
| instruction | first register | second register |
| ----------- | -------------- | --------------- |
| no register | - | - |
| one register | `[memroy cell]` | - |
| two register | `value` | `[memory cell]` |

### list of instructions
> all the instructions must be lower case at the moment due to skkill issues and C++.

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
| `cmpr` | comparing data to determined memory cell | `cpmr 0 , [11]` |
| `jmpe` | jumping to determined memory cell if result of `cmpr` is equal to `0` | `jmpe [132]` |
| `jmpb` | jumping to determined memory cell if result of `cmpr` is bigger than `0` | `jmpb [124]` |
| `jmps` | jumping to determined memory cell if result of `cmpr` is smaller than `0` | `jmps [234]` |
| `scan` | scan data from io to determined memory cell | `scan [122]` |
| `print` | print data to io from determined memory cell | `print [112]` |
| `nop` | no operation | `nop` |
