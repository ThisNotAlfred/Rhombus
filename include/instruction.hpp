#pragma once

#include <cstdint>
#include <variant>

enum Register {
    i1,
    i2,
    i3,
    i4,
    i5,
    i6,
    i7,
    i8,
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

struct ImmInstOneReg {
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

    std::uint16_t source;
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
    MemoryCell dest;
};

using Instruction = std::variant<InstNoReg, InstOneReg, ImmInstOneReg, InstTwoReg, ImmInstTwoReg>;
