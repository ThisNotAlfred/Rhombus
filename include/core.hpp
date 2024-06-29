#pragma once

#include "instruction.hpp"

#include <functional>
#include <typeinfo>
#include <vector>

class Core
{
        public:
    Core(std::vector<Instructions::Instruction>& instructions) : instructions(instructions) {};
    ~Core() = default;

    auto start() -> void;

    auto run_instruction(const Instructions::Instruction& instruction) -> void;

    auto run_index_one_op(const Instructions::IndexOneOp& instruction) -> void;
    auto run_mem_one_op(const Instructions::MemOneOp& instruction) -> void;
    auto run_one_op(const Instructions::OneOp& instruction) -> void;
    auto run_index_two_op(const Instructions::IndexTwoOp& instruction) -> void;
    auto run_mem_two_op(const Instructions::MemTwoOp& instruction) -> void;
    auto run_imm_two_op(const Instructions::ImmTwoOp& instruction) -> void;
    auto run_two_op(const Instructions::TwoOp& instruction) -> void;

    inline auto check_for_flags(std::uint16_t source, std::uint16_t dest,
                                const std::function<int32_t(uint16_t, uint16_t)>& opr) -> void;
    
    inline auto set_negative() -> void;
    inline auto set_zero() -> void;
    inline auto set_overflow() -> void;
    inline auto set_carry() -> void;

        private:
    std::vector<Instructions::Instruction>& instructions;
    std::vector<std::uint16_t> memory       = {};
    std::array<std::uint16_t, 16> registers = {};

    bool negative_flag = false;
    bool zero_flag     = false;
    bool overflow_flag = false;
    bool carry_flag    = false;
};