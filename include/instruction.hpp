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

using Pointer = std::size_t;

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

    Pointer dest;
};

struct IndexOneOp {
    enum {
        JMP,
        JMPE,
        JMPB,
        JMPS,
        PRINT,
    } instruction;

    Register index_register;
    Pointer beginning_of_data;
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
        CMPE,
        CMPS,
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
        CMPE,
        CMPS,
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
        CMPE,
        CMPS,
    } instruction;

    Register source;
    Pointer dest;
};

struct IndexTwoOp {
    enum {
        MOV,
        SHR,
        SHL,
        ADD,
        SUB,
        XOR,
        OR,
        AND,
        CMPE,
        CMPS,
    } instruction;

    Register index_register;
    Pointer beginning_of_data;
    Register dest;
};

struct DataTwoOp {
    enum {
        DB,
    } instruction;

    std::string data;
    std::size_t data_size;
};

using Instruction = std::variant<NoOp, OneOp, MemOneOp, IndexOneOp, TwoOp, ImmTwoOp, MemTwoOp,
                                 IndexTwoOp, DataTwoOp>;
} // namespace Instructions