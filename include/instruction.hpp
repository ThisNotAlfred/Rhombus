#pragma once

#include <variant>

using Register = std::size_t;

struct InstNoReg {
    enum { NOP } instruction;
};

struct InstOneReg {
    enum {
        JMP,
        JMPE,
        JMPB,
        JMPS,
        PRINT,
        SCAN,
    } instruction;

    Register dest;
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

using Instruction = std::variant<InstNoReg, InstOneReg, InstTwoReg>;
