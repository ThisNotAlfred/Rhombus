#pragma once

#include "instruction.hpp"

#include <map>
#include <string>
#include <vector>

class Parser
{
        public:
    Parser(std::vector<std::string>& tokens) : tokens(tokens) {};
    ~Parser() = default;

    auto parse() -> std::vector<Instructions::Instruction>;

    auto parse_mov(std::size_t index) -> Instructions::Instruction;
    auto parse_add(std::size_t index) -> Instructions::Instruction;
    auto parse_sub(std::size_t index) -> Instructions::Instruction;
    auto parse_shr(std::size_t index) -> Instructions::Instruction;
    auto parse_shl(std::size_t index) -> Instructions::Instruction;
    auto parse_xor(std::size_t index) -> Instructions::Instruction;
    auto parse_or(std::size_t index) -> Instructions::Instruction;
    auto parse_and(std::size_t index) -> Instructions::Instruction;
    auto parse_cmpe(std::size_t index) -> Instructions::Instruction;
    auto parse_cmps(std::size_t index) -> Instructions::Instruction;
    auto parse_jmp(std::size_t index) -> Instructions::Instruction;
    auto parse_jmpe(std::size_t index) -> Instructions::Instruction;
    auto parse_jmpb(std::size_t index) -> Instructions::Instruction;
    auto parse_jmps(std::size_t index) -> Instructions::Instruction;
    auto parse_print(std::size_t index) -> Instructions::Instruction;
    auto parse_scan(std::size_t index) -> Instructions::Instruction;

        private:
    std::vector<std::string>& tokens;
    std::map<std::string_view, std::size_t> labels = {};
};