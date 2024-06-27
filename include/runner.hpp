#pragma once

#include "instruction.hpp"

#include <cstdint>
#include <functional>
#include <vector>

class Runner
{
        public:
    Runner(std::vector<Instruction>& instructions) : instructions(instructions) {};
    ~Runner() = default;

    auto start() -> void;

    auto run_instruction(const Instruction& instruction) -> void;

    auto check_for_flags(std::uint16_t source, std::uint16_t dest,
                         const std::function<int32_t(uint16_t, uint16_t)>& opr) -> void;
    auto set_negative() -> void;
    auto set_zero() -> void;
    auto set_overflow() -> void;
    auto set_carry() -> void;

        private:
    std::vector<Instruction>& instructions;

    std::vector<std::uint16_t> memory = {};
    std::size_t instruction_pointer   = 0;

    bool negative_flag = false;
    bool zero_flag     = false;
    bool overflow_flag = false;
    bool carry_flag    = false;
};