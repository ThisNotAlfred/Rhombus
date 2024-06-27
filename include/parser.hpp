#pragma once

#include "instruction.hpp"

#include <string_view>
#include <vector>

class Parser
{
        public:
    Parser(std::vector<std::string>& tokens) : tokens(tokens) {};
    ~Parser() = default;

    auto parse() -> std::vector<Instructions::Instruction>;

    auto no_reg(std::size_t index) -> Instructions::Instruction;

    auto one_mem(std::size_t index) -> Instructions::Instruction;
    auto one_reg(std::size_t index) -> Instructions::Instruction;

    auto two_mem(std::size_t index) -> Instructions::Instruction;
    auto imm_two_reg(std::size_t index) -> Instructions::Instruction;
    auto two_reg(std::size_t index) -> Instructions::Instruction;

        private:
    std::vector<std::string>& tokens;
};