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

    std::print(stderr, "wrong register parameter\n");
    std::exit(EXIT_FAILURE);
}
}; // namespace

auto
Parser::two_mem(std::size_t index) -> Instructions::Instruction
{
    auto mem = std::stoul(this->tokens[index + 2]);

    if (tokens[index] == "mov_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::MOV,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "add_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::ADD,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "sub_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::SUB,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "xor_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::XOR,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "or_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::OR,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "and_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::AND,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "shr_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::SHR,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "shl_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::SHL,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "cmpre_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::CMPRE,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    if (tokens[index] == "cmprs_m") {
        return Instructions::Instruction {
            Instructions::MemTwoRegister {Instructions::MemTwoRegister::CMPRS,
                                          get_register(tokens[index + 1]), mem}
        };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    exit(EXIT_FAILURE);
}

auto
Parser::imm_two_reg(std::size_t index) -> Instructions::Instruction
{
    auto value = static_cast<std::uint16_t>(std::stoul(this->tokens[index + 1]));

    if (tokens[index] == "mov_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::MOV, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "add_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::ADD, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "sub_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::SUB, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "xor_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::XOR, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "or_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::OR, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "and_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::AND, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "shr_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::SHR, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "shl_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::SHL, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "cmpre_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::CMPRE, value,
                                          get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "cmprs_i") {
        return Instructions::Instruction {
            Instructions::ImmTwoRegister {Instructions::ImmTwoRegister::CMPRS, value,
                                          get_register(tokens[index + 2])}
        };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    exit(EXIT_FAILURE);
}

auto
Parser::two_reg(std::size_t index) -> Instructions::Instruction
{
    if (tokens[index] == "mov") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::MOV,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "add") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::ADD,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "sub") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::SUB,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "xor") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::XOR,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "or") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::OR,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "and") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::AND,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "shr") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::SHR,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "shl") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::SHL,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "cmpre") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::CMPRE,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    if (tokens[index] == "cmprs") {
        return Instructions::Instruction {
            Instructions::TwoRegister {Instructions::TwoRegister::CMPRS,
                                       get_register(tokens[index + 1]),
                                       get_register(tokens[index + 2])}
        };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    exit(EXIT_FAILURE);
}

auto
Parser::one_mem(std::size_t index) -> Instructions::Instruction
{
    auto first_mem = std::stoul(this->tokens[index + 1]);

    if (tokens[index] == "jmp") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::JMP, first_mem}
        };
    }

    if (tokens[index] == "jmpe") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::JMPE, first_mem}
        };
    }

    if (tokens[index] == "jmps") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::JMPS, first_mem}
        };
    }

    if (tokens[index] == "jmpb") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::JMPB, first_mem}
        };
    }

    if (tokens[index] == "scan_m") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::SCAN, first_mem}
        };
    }

    if (tokens[index] == "print_m") {
        return Instructions::Instruction {
            Instructions::MemOneRegister {Instructions::MemOneRegister::PRINT, first_mem}
        };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    std::exit(EXIT_FAILURE);
}

auto
Parser::one_reg(std::size_t index) -> Instructions::Instruction
{
    if (tokens[index] == "scan") {
        return Instructions::Instruction {
            Instructions::OneRegister {Instructions::OneRegister::SCAN,
                                       get_register(tokens[index + 1])}
        };
    }

    if (tokens[index] == "print") {
        return Instructions::Instruction {
            Instructions::OneRegister {Instructions::OneRegister::PRINT,
                                       get_register(tokens[index + 1])}
        };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    std::exit(EXIT_FAILURE);
}

auto
Parser::no_reg(std::size_t index) -> Instructions::Instruction
{
    if (tokens[index] == "nop") {
        return Instructions::Instruction { Instructions::NoRegister {} };
    }

    std::print(stderr, "error in parsing at character {}. go figure rest of it. bye!\n", index);
    std::exit(EXIT_FAILURE);
}

auto
Parser::parse() -> std::vector<Instructions::Instruction>
{
    std::vector<Instructions::Instruction> instructions = {};

    for (uint i = 0; i < this->tokens.size(); ++i) {

        if (this->tokens[i] == "mov_m" || this->tokens[i] == "shr_m" ||
            this->tokens[i] == "add_m" || this->tokens[i] == "sub_m" ||
            this->tokens[i] == "xor_m" || this->tokens[i] == "or_m" || this->tokens[i] == "and_m" ||
            this->tokens[i] == "cmpre_m" || this->tokens[i] == "cmprs_m") {
            instructions.emplace_back(this->two_mem(i));
            i += 2;
        }

        else if (this->tokens[i] == "mov_i" || this->tokens[i] == "shr_i" ||
                 this->tokens[i] == "add_i" || this->tokens[i] == "sub_i" ||
                 this->tokens[i] == "xor_i" || this->tokens[i] == "or_i" ||
                 this->tokens[i] == "and_i" || this->tokens[i] == "cmpre_i" ||
                 this->tokens[i] == "cmprs_i") {
            instructions.emplace_back(this->imm_two_reg(i));
            i += 2;
        }

        else if (this->tokens[i] == "mov" || this->tokens[i] == "shr" || this->tokens[i] == "add" ||
                 this->tokens[i] == "sub" || this->tokens[i] == "xor" || this->tokens[i] == "or" ||
                 this->tokens[i] == "and" || this->tokens[i] == "cmpre" ||
                 this->tokens[i] == "cmprs") {
            instructions.emplace_back(this->two_reg(i));
            i += 2;
        }

        else if (this->tokens[i] == "jmp" || this->tokens[i] == "jmpe" ||
                 this->tokens[i] == "jmpb" || this->tokens[i] == "jmps" ||
                 this->tokens[i] == "print_m" || this->tokens[i] == "scan_m") {
            instructions.emplace_back(this->one_mem(i));
            i += 1;
        }

        else if (this->tokens[i] == "print" || this->tokens[i] == "scan") {
            instructions.emplace_back(this->one_reg(i));
            i += 1;
        }

        else if (this->tokens[i] == "nop") {
            instructions.emplace_back(this->no_reg(i));
        }

        else {
            std::unreachable();
        }
    }

    return instructions;
}