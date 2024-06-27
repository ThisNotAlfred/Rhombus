#pragma once

#include "instruction.hpp"

#include <cstdint>
#include <functional>
#include <vector>

namespace
{
struct Stack {
    std::uint16_t i0 = 0;
    std::uint16_t i1 = 0;
    std::uint16_t i2 = 0;
    std::uint16_t i3 = 0;
    std::uint16_t i4 = 0;
    std::uint16_t i5 = 0;
    std::uint16_t i6 = 0;
    std::uint16_t i7 = 0;
};
} // namespace

class Runner
{
        public:
    Runner(std::vector<Instructions::Instruction>& instructions) : instructions(instructions) {};
    ~Runner() = default;

    auto start() -> void;

    auto run_instruction(const Instructions::Instruction& instruction) -> void;

    auto check_for_flags(std::uint16_t source, std::uint16_t dest,
                         const std::function<int32_t(uint16_t, uint16_t)>& opr) -> void;
    auto set_negative() -> void;
    auto set_zero() -> void;
    auto set_overflow() -> void;
    auto set_carry() -> void;

        private:
    std::vector<Instructions::Instruction>& instructions;

    std::vector<std::uint16_t> memory = {};
    std::size_t instruction_pointer   = 0;

    bool negative_flag = false;
    bool zero_flag     = false;
    bool overflow_flag = false;
    bool carry_flag    = false;

    Stack stack = {};
};