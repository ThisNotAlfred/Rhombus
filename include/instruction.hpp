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

struct NoRegister {
    enum { NOP } instruction;
};

struct OneRegister {
    enum {
        PRINT,
        SCAN,
    } instruction;

    Register dest;
};

struct MemOneRegister {
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

struct TwoRegister {
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

struct ImmTwoRegister {
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

struct MemTwoRegister {
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

using Instruction = std::variant<NoRegister, OneRegister, MemOneRegister, TwoRegister,
                                 ImmTwoRegister, MemTwoRegister>;
} // namespace Instructions