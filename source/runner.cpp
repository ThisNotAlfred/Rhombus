#include "runner.hpp"
#include "instruction.hpp"

#include <iostream>
#include <print>
#include <utility>
#include <variant>

auto
Runner::start() -> void
{
    // resizing from 0 to 128KB (2^^16 * 8 / 1024 * 16)
    memory.resize(static_cast<std::size_t>(65536 * 8 / 1024));

    for (; this->instruction_pointer < instructions.size(); ++this->instruction_pointer) {
        this->run_instruction(instructions[this->instruction_pointer]);
    }
}

auto
Runner::run_instruction(const Instructions::Instruction& instruction) -> void
{
    if (std::holds_alternative<Instructions::NoRegister>(instruction)) {
        switch (std::get<Instructions::NoRegister>(instruction).instruction) {
            case Instructions::NoRegister::NOP:
                ++this->instruction_pointer;
        }
    }

    else if (std::holds_alternative<Instructions::MemOneRegister>(instruction)) {
        this->run_mem_one_register(std::get<Instructions::MemOneRegister>(instruction));
    }

    else if (std::holds_alternative<Instructions::OneRegister>(instruction)) {
        this->run_one_register(std::get<Instructions::OneRegister>(instruction));
    }

    else if (std::holds_alternative<Instructions::MemTwoRegister>(instruction)) {
        this->run_mem_two_register(std::get<Instructions::MemTwoRegister>(instruction));
    }

    else if (std::holds_alternative<Instructions::ImmTwoRegister>(instruction)) {
        this->run_imm_two_register(std::get<Instructions::ImmTwoRegister>(instruction));
    }

    else if (std::holds_alternative<Instructions::TwoRegister>(instruction)) {
        this->run_two_register(std::get<Instructions::TwoRegister>(instruction));
    }

    else {
        std::unreachable();
    }
}

inline auto
Runner::run_mem_one_register(const Instructions::MemOneRegister& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::MemOneRegister::JMP:
            this->instruction_pointer = instruction.dest;
            break;

        case Instructions::MemOneRegister::JMPE:
            if (this->zero_flag) {
                this->instruction_pointer = instruction.dest;
            } else {
                ++this->instruction_pointer;
            }
            break;

        case Instructions::MemOneRegister::JMPB:
            if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                this->instruction_pointer = instruction.dest;
            } else {
                ++this->instruction_pointer;
            }
            break;

        case Instructions::MemOneRegister::JMPS:
            if (this->negative_flag != this->overflow_flag) {
                this->instruction_pointer = instruction.dest;
            } else {
                ++this->instruction_pointer;
            }
            break;

        case Instructions::MemOneRegister::PRINT:
            std::print("{}", static_cast<char>(this->memory[instruction.dest]));
            break;

        case Instructions::MemOneRegister::SCAN:
            std::cin >> this->memory[instruction.dest];
            break;
    }
}

inline auto
Runner::run_one_register(const Instructions::OneRegister& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::OneRegister::PRINT:
            std::print("{}", static_cast<char>(this->stack[instruction.dest]));
            this->instruction_pointer++;
            break;

        case Instructions::OneRegister::SCAN:
            std::cin >> this->stack[instruction.dest];
            this->instruction_pointer++;
            this->stack_pointer++;
            break;
    }
}

inline auto
Runner::run_mem_two_register(const Instructions::MemTwoRegister& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.source);

    switch (instruction.instruction) {
        case Instructions::MemTwoRegister::MOV:
            this->memory[instruction.dest] = value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::SHR:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] >> src; });
            this->memory[instruction.dest] >>= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::SHL:
            this->check_for_flags(
                value, this->memory[instruction.dest],
                [this](uint16_t src, uint16_t dest) { return this->memory[dest] << src; });
            this->memory[instruction.dest] <<= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::ADD:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->memory[instruction.dest] += value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::SUB:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->memory[instruction.dest] -= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->memory[instruction.dest] ^= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::OR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->memory[instruction.dest] |= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::AND:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->memory[instruction.dest] &= value;
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::CMPRE:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            instruction_pointer++;
            break;

        case Instructions::MemTwoRegister::CMPRS:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            instruction_pointer++;
            break;
    }
}

inline auto
Runner::run_imm_two_register(const Instructions::ImmTwoRegister& instruction) -> void
{
    auto value = static_cast<std::uint16_t>(instruction.value);

    switch (instruction.instruction) {
        case Instructions::ImmTwoRegister::MOV:
            this->stack[instruction.dest] = value;
            instruction_pointer++;
            stack_pointer++;
            break;

        case Instructions::ImmTwoRegister::SHR:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->stack[instruction.dest] >>= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::SHL:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->stack[instruction.dest] <<= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::ADD:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->stack[instruction.dest] += value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::SUB:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->stack[instruction.dest] -= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::XOR:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->stack[instruction.dest] ^= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::OR:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->stack[instruction.dest] |= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::AND:
            this->check_for_flags(value, this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->stack[instruction.dest] &= value;
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::CMPRE:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::CMPRS:
            this->check_for_flags(value, this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            instruction_pointer++;
            break;
    }
}

inline auto
Runner::run_two_register(const Instructions::TwoRegister& instruction) -> void
{
    switch (instruction.instruction) {
        case Instructions::ImmTwoRegister::MOV:
            this->stack[instruction.dest] = this->stack[instruction.source];
            instruction_pointer++;
            stack_pointer++;
            break;

        case Instructions::ImmTwoRegister::SHR:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest >> src; });
            this->stack[instruction.dest] >>= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::SHL:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest << src; });
            this->stack[instruction.dest] <<= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::ADD:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest + src; });
            this->stack[instruction.dest] += this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::SUB:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest - src; });
            this->stack[instruction.dest] -= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::XOR:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest ^ src; });
            this->stack[instruction.dest] ^= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::OR:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest | src; });
            this->stack[instruction.dest] |= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::AND:
            this->check_for_flags(this->stack[instruction.source], this->stack[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest & src; });
            this->stack[instruction.dest] &= this->stack[instruction.source];
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::CMPRE:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest == src; });
            instruction_pointer++;
            break;

        case Instructions::ImmTwoRegister::CMPRS:
            this->check_for_flags(this->stack[instruction.source], this->memory[instruction.dest],
                                  [](uint16_t src, uint16_t dest) { return dest > src; });
            instruction_pointer++;
            break;
    }
}

inline auto
Runner::check_for_flags(std::uint16_t source, std::uint16_t dest,
                        const std::function<std::int32_t(std::uint16_t, std::uint16_t)>& opr)
    -> void
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
Runner::set_negative() -> void
{
    this->negative_flag = !this->negative_flag;
}

inline auto
Runner::set_zero() -> void
{
    this->zero_flag = !this->zero_flag;
}

inline auto
Runner::set_overflow() -> void
{
    this->overflow_flag = !this->overflow_flag;
}

inline auto
Runner::set_carry() -> void
{
    this->carry_flag = !this->carry_flag;
}
