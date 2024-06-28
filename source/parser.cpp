#include "parser.hpp"

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <utility>
#include <vector>

namespace
{
inline auto
get_register(std::string_view reg)
{
    if (reg == "i0") {
        return Instructions::Register::i0;
    }

    if (reg == "i1") {
        return Instructions::Register::i1;
    }

    if (reg == "i2") {
        return Instructions::Register::i2;
    }

    if (reg == "i3") {
        return Instructions::Register::i3;
    }

    if (reg == "i4") {
        return Instructions::Register::i4;
    }

    if (reg == "i5") {
        return Instructions::Register::i5;
    }

    if (reg == "i6") {
        return Instructions::Register::i6;
    }

    if (reg == "i7") {
        return Instructions::Register::i7;
    }

    if (reg == "i8") {
        return Instructions::Register::i8;
    }

    if (reg == "i9") {
        return Instructions::Register::i9;
    }

    if (reg == "i10") {
        return Instructions::Register::i10;
    }

    if (reg == "i11") {
        return Instructions::Register::i11;
    }

    if (reg == "i12") {
        return Instructions::Register::i12;
    }

    if (reg == "i13") {
        return Instructions::Register::i13;
    }

    if (reg == "i14") {
        return Instructions::Register::i14;
    }

    if (reg == "i15") {
        return Instructions::Register::i15;
    }

    std::print(stderr, "wrong register parameter {}\n", reg);
    std::exit(EXIT_FAILURE);
}

inline auto
parse_value(std::string& token)
{
    token.erase(token.begin());

    return static_cast<std::uint16_t>(std::stoi(token));
}

inline auto
parse_brackets(std::string& token)
{
    token.erase(token.begin());
    token.erase(token.end());

    return static_cast<std::uint16_t>(std::stoi(token));
}
}; // namespace

auto
Parser::parse() -> std::vector<Instructions::Instruction>
{
    std::vector<Instructions::Instruction> instructions = {};

    for (std::size_t i = 0; i < this->tokens.size();) {
        if (this->tokens[i] == "mov") {
            instructions.emplace_back(this->parse_mov(i));
            i += 3;
        }

        else if (this->tokens[i] == "add") {
            instructions.emplace_back(this->parse_add(i));
            i += 3;
        }

        else if (this->tokens[i] == "sub") {
            instructions.emplace_back(this->parse_sub(i));
            i += 3;
        }

        else if (this->tokens[i] == "shr") {
            instructions.emplace_back(this->parse_shr(i));
            i += 3;
        }

        else if (this->tokens[i] == "shl") {
            instructions.emplace_back(this->parse_shl(i));
            i += 3;
        }

        else if (this->tokens[i] == "xor") {
            instructions.emplace_back(this->parse_xor(i));
            i += 3;
        }

        else if (this->tokens[i] == "or") {
            instructions.emplace_back(this->parse_or(i));
            i += 3;
        }

        else if (this->tokens[i] == "and") {
            instructions.emplace_back(this->parse_and(i));
            i += 3;
        }

        else if (this->tokens[i] == "cmpe") {
            instructions.emplace_back(this->parse_cmpe(i));
            i += 3;
        }

        else if (this->tokens[i] == "cmps") {
            instructions.emplace_back(this->parse_cmps(i));
            i += 3;
        }

        else if (this->tokens[i] == "jmp") {
            instructions.emplace_back(this->parse_jmp(i));
            i += 2;
        }

        else if (this->tokens[i] == "jmpe") {
            instructions.emplace_back(this->parse_jmpe(i));
            i += 2;

        }

        else if (this->tokens[i] == "jmpb") {
            instructions.emplace_back(this->parse_jmpb(i));
            i += 2;
        }

        else if (this->tokens[i] == "jmps") {
            instructions.emplace_back(this->parse_jmps(i));
            i += 2;
        }

        else if (this->tokens[i] == "print") {
            instructions.emplace_back(this->parse_print(i));
            i += 2;
        }

        else if (this->tokens[i] == "scan") {
            instructions.emplace_back(this->parse_scan(i));
            i += 2;
        }

        else {
            std::print(stderr, "wrong parameter at token {}\n", this->tokens[i]);
            std::exit(EXIT_FAILURE);
        }
    }

    return instructions;
}

auto
Parser::parse_mov(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::MOV,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::MOV,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::MOV,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_add(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::ADD,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::ADD,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::ADD,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_sub(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::SUB,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::SUB,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::SUB,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_shr(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::SHR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::SHR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::SHR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_shl(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::SHL,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::SHL,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::SHL,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_xor(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::XOR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::XOR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::XOR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_or(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::OR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::OR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::OR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_and(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::AND,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::AND,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::AND,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_cmpe(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::CMPRE,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::CMPRE,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::CMPRE,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_cmps(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoRegister {
            Instructions::ImmTwoRegister::CMPRS,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoRegister {
            Instructions::MemTwoRegister::CMPRS,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoRegister {
        Instructions::TwoRegister::CMPRS,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_jmp(std::size_t index) -> Instructions::Instruction
{
    return Instructions::MemOneRegister {
        Instructions::MemOneRegister::JMP,
        parse_brackets(this->tokens[index + 1]),
    };
}

auto
Parser::parse_jmpe(std::size_t index) -> Instructions::Instruction
{
    return Instructions::MemOneRegister {
        Instructions::MemOneRegister::JMPE,
        parse_brackets(this->tokens[index + 1]),
    };
}

auto
Parser::parse_jmpb(std::size_t index) -> Instructions::Instruction
{
    return Instructions::MemOneRegister {
        Instructions::MemOneRegister::JMPB,
        parse_brackets(this->tokens[index + 1]),
    };
}

auto
Parser::parse_jmps(std::size_t index) -> Instructions::Instruction
{
    return Instructions::MemOneRegister {
        Instructions::MemOneRegister::JMPS,
        parse_brackets(this->tokens[index + 1]),
    };
}

auto
Parser::parse_print(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '[') {
        return Instructions::MemOneRegister {
            Instructions::MemOneRegister::PRINT,
            parse_brackets(this->tokens[index + 1]),
        };
    }

    return Instructions::OneRegister {
        Instructions::OneRegister::PRINT,
        get_register(this->tokens[index + 1]),
    };
}

auto
Parser::parse_scan(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '[') {
        return Instructions::MemOneRegister {
            Instructions::MemOneRegister::SCAN,
            parse_brackets(this->tokens[index + 1]),
        };
    }

    return Instructions::OneRegister {
        Instructions::OneRegister::SCAN,
        get_register(this->tokens[index + 1]),
    };
}