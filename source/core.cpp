#include "core.hpp"
#include "instruction.hpp"

#include <cstdio>
#include <utility>
#include <variant>

auto
Core::start() -> void
{
    // resizing from 0 to 64KB (2^^16 * 4 / 1024 * 16)
    memory.resize(static_cast<std::size_t>(65536 * 4 / 1024));

    for (; this->registers[0] < instructions.size();) {
        this->run_instruction(instructions[this->registers[0]]);
    }
}

auto
Core::run_instruction(const Instructions::Instruction& instruction) -> void
{
    if (std::holds_alternative<Instructions::NoOp>(instruction)) {
        switch (std::get<Instructions::NoOp>(instruction).instruction) {
            case Instructions::NoOp::NOP:
                this->registers[0]++;
        }
    }

    else if (std::holds_alternative<Instructions::IndexOneOp>(instruction)) {
        this->run_index_one_op(std::get<Instructions::IndexOneOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::MemOneOp>(instruction)) {
        this->run_mem_one_op(std::get<Instructions::MemOneOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::OneOp>(instruction)) {
        this->run_one_op(std::get<Instructions::OneOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::IndexTwoOp>(instruction)) {
        this->run_index_two_op(std::get<Instructions::IndexTwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::MemTwoOp>(instruction)) {
        this->run_mem_two_op(std::get<Instructions::MemTwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::ImmTwoOp>(instruction)) {
        this->run_imm_two_op(std::get<Instructions::ImmTwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::TwoOp>(instruction)) {
        this->run_two_op(std::get<Instructions::TwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::Data>(instruction)) {
        this->registers[0]++;
    }

    else {
        std::unreachable();
    }
}

auto
Core::run_index_one_op(const Instructions::IndexOneOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::IndexOneOp::JMP:
            this->registers[0] =
                instruction.beginning_of_data + this->registers[instruction.index_register];
            break;

        case Instructions::IndexOneOp::JMPE:
            if (this->zero_flag) {
                this->registers[0] =
                    instruction.beginning_of_data + this->registers[instruction.index_register];
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::IndexOneOp::JMPB:
            if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                this->registers[0] =
                    instruction.beginning_of_data + this->registers[instruction.index_register];
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::IndexOneOp::JMPS:
            if (this->negative_flag != this->overflow_flag) {
                this->registers[0] =
                    instruction.beginning_of_data + this->registers[instruction.index_register];
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::IndexOneOp::PRINT:
            std::putchar(static_cast<char>(std::get<Instructions::Data>(
                this->instructions[instruction.beginning_of_data +
                                   this->registers[instruction.index_register]])));
            this->registers[0]++;
            break;
    }
}

auto
Core::run_mem_one_op(const Instructions::MemOneOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::MemOneOp::JMP:
            this->registers[0] = instruction.dest;
            break;

        case Instructions::MemOneOp::JMPE:
            if (this->zero_flag) {
                this->registers[0] = instruction.dest;
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::MemOneOp::JMPB:
            if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                this->registers[0] = instruction.dest;
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::MemOneOp::JMPS:
            if (this->negative_flag != this->overflow_flag) {
                this->registers[0] = instruction.dest;
            } else {
                this->registers[0]++;
            }
            break;

        case Instructions::MemOneOp::PRINT:
            std::putchar(static_cast<char>(this->registers[instruction.dest]));
            this->registers[0]++;
            break;

        case Instructions::MemOneOp::SCAN:
            this->memory[instruction.dest] = std::getchar();
            this->registers[0]++;
            break;
    }
}

auto
Core::run_one_op(const Instructions::OneOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::OneOp::PRINT:
            std::putchar(static_cast<char>(this->registers[instruction.dest]));
            this->registers[0]++;
            break;

        case Instructions::OneOp::SCAN:
            this->registers[instruction.dest] = std::getchar();
            this->registers[0]++;
            break;
    }
}

auto
Core::run_index_two_op(const Instructions::IndexTwoOp& instruction) -> void
{
    auto data = std::get<Instructions::Data>(
        this->instructions[instruction.beginning_of_data +
                           this->registers[instruction.index_register]]);

    switch (instruction.instruction) {
        case Instructions::IndexTwoOp::MOV:
            this->registers[instruction.dest] = data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::SHR:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] >> src; });
            this->memory[instruction.dest] >>= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::SHL:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] << src; });
            this->memory[instruction.dest] >>= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::ADD:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] + src; });
            this->memory[instruction.dest] += data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::SUB:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] - src; });
            this->memory[instruction.dest] -= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::XOR:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] ^ src; });
            this->memory[instruction.dest] ^= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::OR:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] | src; });
            this->memory[instruction.dest] |= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::AND:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] & src; });
            this->memory[instruction.dest] &= data;
            this->registers[0]++;
            break;

        case Instructions::IndexTwoOp::CMP:
            this->check_for_flags(
                data, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] - src; });
            this->registers[0]++;
            break;
    }
}

auto
Core::run_mem_two_op(const Instructions::MemTwoOp& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.source);

    switch (instruction.instruction) {
        case Instructions::MemTwoOp::MOV:
            this->memory[instruction.dest] = value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::SHR:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] >> src; });
            this->memory[instruction.dest] >>= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::SHL:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] << src; });
            this->memory[instruction.dest] <<= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::ADD:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->memory[instruction.dest] += value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::SUB:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->memory[instruction.dest] -= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->memory[instruction.dest] ^= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::OR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->memory[instruction.dest] |= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::AND:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->memory[instruction.dest] &= value;
            registers[0]++;
            break;

        case Instructions::MemTwoOp::CMP:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            registers[0]++;
            break;
    }
}

auto
Core::run_imm_two_op(const Instructions::ImmTwoOp& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.value);

    switch (instruction.instruction) {
        case Instructions::ImmTwoOp::MOV:
            this->registers[instruction.dest] = value;
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::SHR:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->registers[instruction.dest] >>= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::SHL:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->registers[instruction.dest] <<= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::ADD:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->registers[instruction.dest] += value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::SUB:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->registers[instruction.dest] -= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->registers[instruction.dest] ^= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::OR:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->registers[instruction.dest] |= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::AND:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->registers[instruction.dest] &= value;
            this->registers[0]++;
            break;

        case Instructions::ImmTwoOp::CMP:
            this->check_for_flags(value, this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->registers[0]++;
            break;
    }
}

auto
Core::run_two_op(const Instructions::TwoOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::ImmTwoOp::MOV:
            this->registers[instruction.dest] = this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::SHR:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->registers[instruction.dest] >>= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::SHL:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->registers[instruction.dest] <<= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::ADD:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->registers[instruction.dest] += this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::SUB:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->registers[instruction.dest] -= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::XOR:
            this->check_for_flags(this->registers[instruction.source],
                                  this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->registers[instruction.dest] ^= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::OR:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->registers[instruction.dest] |= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::AND:
            this->check_for_flags(this->registers[instruction.source],
                                  this->registers[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->registers[instruction.dest] &= this->registers[instruction.source];
            registers[0]++;
            break;

        case Instructions::ImmTwoOp::CMP:
            this->check_for_flags(this->registers[instruction.source],
                                  this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            registers[0]++;
            break;
    }
}

inline auto
Core::check_for_flags(std::uint16_t source, std::uint16_t dest,
                      const std::function<std::int32_t(std::uint16_t, std::uint16_t)>& opr) -> void
{
    this->zero_flag = opr(source, dest) == 0;

    this->negative_flag = opr(source, dest) < 0;

    this->overflow_flag = opr(source, dest) > INT16_MAX;

    this->carry_flag = opr(source, dest) > UINT16_MAX;
}