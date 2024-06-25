#include "parser.hpp"

#include <iostream>
#include <string>
#include <vector>

auto
Parser::two_reg(std::size_t index) -> Instruction
{
    auto first_reg  = std::stoul(this->tokens[index + 1].data());
    auto second_reg = std::stoul(this->tokens[index + 2].data());

    if (tokens[index] == "mov") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "add") {
        return Instruction {
            InstTwoReg {InstTwoReg::ADD, first_reg, second_reg}
        };
    }

    if (tokens[index] == "sub") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "xor") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "or") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "and") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "shr") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "shl") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    if (tokens[index] == "cmpr") {
        return Instruction {
            InstTwoReg {InstTwoReg::MOV, first_reg, second_reg}
        };
    }

    std::cerr << "error in parsing at character " << index << ". go figure rest of it. bye!\n";
    exit(EXIT_FAILURE);
}

auto
Parser::one_reg(std::size_t index) -> Instruction
{
    auto first_reg = std::stoul(this->tokens[index + 1].data());

    if (tokens[index] == "JMPE") {
        return Instruction {
            InstOneReg {InstOneReg::JMPE, first_reg}
        };
    }

    if (tokens[index] == "JMPS") {
        return Instruction {
            InstOneReg {InstOneReg::JMPS, first_reg}
        };
    }

    if (tokens[index] == "JMPB") {
        return Instruction {
            InstOneReg {InstOneReg::JMPB, first_reg}
        };
    }

    if (tokens[index] == "SCAN") {
        return Instruction {
            InstOneReg {InstOneReg::SCAN, first_reg}
        };
    }

    if (tokens[index] == "PRINT") {
        return Instruction {
            InstOneReg {InstOneReg::PRINT, first_reg}
        };
    }


    std::cerr << "error in parsing at character " << index << ". go figure rest of it. bye!\n";
    exit(EXIT_FAILURE);
}

auto
Parser::no_reg(std::size_t index) -> Instruction
{
    if (tokens[index] == "nop") {
        return Instruction { InstNoReg {} };
    }

    std::cerr << "error in parsing at character " << index << ". go figure rest of it. bye!\n";
    exit(EXIT_FAILURE);
}

auto
Parser::parse() -> std::vector<Instruction>
{
    std::vector<Instruction> instructions = {};

    for (auto i = 0; i < this->tokens.size(); ++i) {
        if (this->tokens[i] == "mov" || this->tokens[i] == "shr" || this->tokens[i] == "add" ||
            this->tokens[i] == "sub" || this->tokens[i] == "xor" || this->tokens[i] == "or" ||
            this->tokens[i] == "and" || this->tokens[i] == "cmpr") {
            instructions.emplace_back(this->two_reg(i));
            i += 3;
        } else if (this->tokens[i] == "jmpe" || this->tokens[i] == "jmpb" ||
                   this->tokens[i] == "jmps" || this->tokens[i] == "print" ||
                   this->tokens[i] == "scan") {
            instructions.emplace_back(this->one_reg(i));
            i += 2;
        } else if (this->tokens[i] == "nop") {
            instructions.emplace_back(this->no_reg(i));
            i += 1;
        }
    }

    return std::move(instructions);
}