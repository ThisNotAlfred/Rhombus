#pragma once

#include <cstdint>
#include <variant>

namespace Instructions
{
enum Register {
    i0,
    i1,
    i2,
    i3,
    i4,
    i5,
    i6,
    i7,
};

using MemoryCell = std::size_t;

struct InstNoReg {
    enum { NOP } instruction;
};

struct InstOneReg {
    enum {
        PRINT,
        SCAN,
    } instruction;

    Register dest;
};

struct MemInstOneReg {
    enum {
        JMP,
        JMPE,
        JMPB,
        JMPS,
        PRINT,
        SCAN,
    } instruction;

    MemoryCell dest;
};

struct InstTwoReg {
    enum {
        MOV,
        SHR,
        SHL,
        ADD,
        SUB,
        XOR,
        OR,
        AND,
        CMPRE,
        CMPRS,
    } instruction;

    Register source;
    Register dest;
};

struct ImmInstTwoReg {
    enum {
        MOV,
        SHR,
        SHL,
        ADD,
        SUB,
        XOR,
        OR,
        AND,
        CMPRE,
        CMPRS,
    } instruction;

    std::uint16_t value;
    Register dest;
};

struct MemInstTwoReg {
    enum {
        MOV,
        SHR,
        SHL,
        ADD,
        SUB,
        XOR,
        OR,
        AND,
        CMPRE,
        CMPRS,
    } instruction;

    Register source;
    MemoryCell dest;
};

using Instruction =
    std::variant<InstNoReg, InstOneReg, MemInstOneReg, InstTwoReg, ImmInstTwoReg, MemInstTwoReg>;
} // namespace Instructions