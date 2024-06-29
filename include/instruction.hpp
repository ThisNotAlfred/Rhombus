#pragma once

#include <cstdint>
#include <string>
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
    i8,
    i9,
    i10,
    i11,
    i12,
    i13,
    i14,
    i15,
};

using MemoryCell = std::size_t;

struct NoOp {
    enum { NOP } instruction;
};

struct OneOp {
    enum {
        PRINT,
        SCAN,
    } instruction;

    Register dest;
};

struct MemOneOp {
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


struct TwoOp {
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

struct ImmTwoOp {
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

struct MemTwoOp {
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

struct DataTwoOp {
    enum {
        DB,
    } instruction;

    std::string data;
    std::size_t data_size;
};

using Instruction = std::variant<NoOp, OneOp, MemOneOp, TwoOp, ImmTwoOp, MemTwoOp, DataTwoOp>;
} // namespace Instructions