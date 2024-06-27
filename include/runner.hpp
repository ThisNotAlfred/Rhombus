#pragma once

#include "instruction.hpp"

#include <functional>
#include <typeinfo>
#include <vector> // namespace

class Runner
{
        public:
    Runner(std::vector<Instructions::Instruction>& instructions) : instructions(instructions) {};
    ~Runner() = default;

    auto start() -> void;

    auto run_instruction(const Instructions::Instruction& instruction) -> void;

    inline auto run_mem_one_register(const Instructions::MemOneRegister& instruction) -> void;
    inline auto run_one_register(const Instructions::OneRegister& instruction) -> void;
    inline auto run_mem_two_register(const Instructions::MemTwoRegister& instruction) -> void;
    inline auto run_imm_two_register(const Instructions::ImmTwoRegister& instruction) -> void;
    inline auto run_two_register(const Instructions::TwoRegister& instruction) -> void;

    inline auto check_for_flags(std::uint16_t source, std::uint16_t dest,
                                const std::function<int32_t(uint16_t, uint16_t)>& opr) -> void;
    inline auto set_negative() -> void;
    inline auto set_zero() -> void;
    inline auto set_overflow() -> void;
    inline auto set_carry() -> void;

        private:
    std::vector<Instructions::Instruction>& instructions;

    std::vector<std::uint16_t> memory = {};
    std::size_t instruction_pointer   = 0;

    bool negative_flag = false;
    bool zero_flag     = false;
    bool overflow_flag = false;
    bool carry_flag    = false;

    std::array<std::uint16_t, 8> stack = {};
    std::size_t stack_pointer          = 0;
    std::size_t stack_base             = 0;
};