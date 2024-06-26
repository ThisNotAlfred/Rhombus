#pragma once

#include "instruction.hpp"

#include <cstdint>
#include <vector>

class Runner
{
        public:
    Runner(std::vector<Instruction>& instructions) : instructions(instructions) {};
    ~Runner() = default;

    auto run() -> void;

        private:
    std::vector<Instruction>& instructions;

    std::vector<std::uint32_t> memory = {};

    bool negative_flag = false;
    bool zero_flag     = false;
    bool overflow_flag = false;
    bool carry_flag    = false;
};