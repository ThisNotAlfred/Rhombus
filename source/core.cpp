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

    for (; this->stack[0] < instructions.size();) {
        this->run_instruction(instructions[this->stack[0]]);
    }
}

auto
Core::run_instruction(const Instructions::Instruction& instruction) -> void
{
    if (std::holds_alternative<Instructions::NoOp>(instruction)) {
        switch (std::get<Instructions::NoOp>(instruction).instruction) {
            case Instructions::NoOp::NOP:
                this->stack[0]++;
        }
    }

    else if (std::holds_alternative<Instructions::MemOneOp>(instruction)) {
        this->run_mem_one_register(std::get<Instructions::MemOneOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::OneOp>(instruction)) {
        this->run_one_register(std::get<Instructions::OneOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::MemTwoOp>(instruction)) {
        this->run_mem_two_register(std::get<Instructions::MemTwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::ImmTwoOp>(instruction)) {
        this->run_imm_two_register(std::get<Instructions::ImmTwoOp>(instruction));
    }

    else if (std::holds_alternative<Instructions::TwoOp>(instruction)) {
        this->run_two_register(std::get<Instructions::TwoOp>(instruction));
    }

    else {
        std::unreachable();
    }
}

auto
Core::run_mem_one_register(const Instructions::MemOneOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::MemOneOp::JMP:
            this->stack[0] = instruction.dest;
            break;

        case Instructions::MemOneOp::JMPE:
            if (this->zero_flag) {
                this->stack[0] = instruction.dest;
            } else {
                this->stack[0]++;
            }
            break;

        case Instructions::MemOneOp::JMPB:
            if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                this->stack[0] = instruction.dest;
            } else {
                this->stack[0]++;
            }
            break;

        case Instructions::MemOneOp::JMPS:
            if (this->negative_flag != this->overflow_flag) {
                this->stack[0] = instruction.dest;
            } else {
                this->stack[0]++;
            }
            break;

        case Instructions::MemOneOp::PRINT:
            std::putchar(static_cast<char>(this->stack[instruction.dest]));
            this->stack[0]++;
            break;

        case Instructions::MemOneOp::SCAN:
            this->memory[instruction.dest] = std::getchar();
            this->stack[0]++;
            break;
    }
}

auto
Core::run_one_register(const Instructions::OneOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::OneOp::PRINT:
            std::putchar(static_cast<char>(this->stack[instruction.dest]));
            this->stack[0]++;
            break;

        case Instructions::OneOp::SCAN:
            this->stack[instruction.dest] = std::getchar();
            this->stack[0]++;
            break;
    }
}

auto
Core::run_mem_two_register(const Instructions::MemTwoOp& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.source);

    switch (instruction.instruction) {
        case Instructions::MemTwoOp::MOV:
            this->memory[instruction.dest] = value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::SHR:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] >> src; });
            this->memory[instruction.dest] >>= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::SHL:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] << src; });
            this->memory[instruction.dest] <<= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::ADD:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->memory[instruction.dest] += value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::SUB:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->memory[instruction.dest] -= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->memory[instruction.dest] ^= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::OR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->memory[instruction.dest] |= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::AND:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->memory[instruction.dest] &= value;
            stack[0]++;
            break;

        case Instructions::MemTwoOp::CMPE:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            stack[0]++;
            break;

        case Instructions::MemTwoOp::CMPS:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            stack[0]++;
            break;
    }
}

auto
Core::run_imm_two_register(const Instructions::ImmTwoOp& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.value);

    switch (instruction.instruction) {
        case Instructions::ImmTwoOp::MOV:
            this->stack[instruction.dest] = value;
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::SHR:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->stack[instruction.dest] >>= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::SHL:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->stack[instruction.dest] <<= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::ADD:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->stack[instruction.dest] += value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::SUB:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->stack[instruction.dest] -= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->stack[instruction.dest] ^= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::OR:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->stack[instruction.dest] |= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::AND:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->stack[instruction.dest] &= value;
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::CMPE:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            this->stack[0]++;
            break;

        case Instructions::ImmTwoOp::CMPS:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            this->stack[0]++;
            break;
    }
}

auto
Core::run_two_register(const Instructions::TwoOp& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::ImmTwoOp::MOV:
            this->stack[instruction.dest] = this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::SHR:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->stack[instruction.dest] >>= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::SHL:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->stack[instruction.dest] <<= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::ADD:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->stack[instruction.dest] += this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::SUB:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->stack[instruction.dest] -= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::XOR:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->stack[instruction.dest] ^= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::OR:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->stack[instruction.dest] |= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::AND:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->stack[instruction.dest] &= this->stack[instruction.source];
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::CMPE:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            stack[0]++;
            break;

        case Instructions::ImmTwoOp::CMPS:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            stack[0]++;
            break;
    }
}

inline auto
Core::check_for_flags(std::uint16_t source, std::uint16_t dest,
                      const std::function<std::int32_t(std::uint16_t, std::uint16_t)>& opr) -> void
{
    if (opr(source, dest) == 0) {
        this->set_zero();
    }

    if (opr(source, dest) < 0) {
        this->set_negative();
    }

    if (opr(source, dest) > INT16_MAX) {
        this->set_overflow();
    }

    if (opr(source, dest) > UINT16_MAX) {
        this->set_overflow();
    }
}

inline auto
Core::set_negative() -> void
{
    this->negative_flag = !this->negative_flag;
}

inline auto
Core::set_zero() -> void
{
    this->zero_flag = !this->zero_flag;
}

inline auto
Core::set_overflow() -> void
{
    this->overflow_flag = !this->overflow_flag;
}

inline auto
Core::set_carry() -> void
{
    this->carry_flag = !this->carry_flag;
}
