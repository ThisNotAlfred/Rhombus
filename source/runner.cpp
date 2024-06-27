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
    } else if (std::holds_alternative<Instructions::MemOneRegister>(instruction)) {
        auto dest = std::get<Instructions::MemOneRegister>(instruction).dest;

        switch (std::get<Instructions::MemOneRegister>(instruction).instruction) {
            case Instructions::MemOneRegister::JMP:
                this->instruction_pointer = dest;
                break;

            case Instructions::MemOneRegister::JMPE:
                if (this->zero_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case Instructions::MemOneRegister::JMPB:
                if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case Instructions::MemOneRegister::JMPS:
                if (this->negative_flag != this->overflow_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case Instructions::MemOneRegister::PRINT:
                std::print("{}", static_cast<char>(this->memory[dest]));
                break;

            case Instructions::MemOneRegister::SCAN:
                std::cin >> this->memory[dest];
                break;
        }
    } else if (std::holds_alternative<Instructions::MemTwoRegister>(instruction)) {
        auto source = std::get<Instructions::MemTwoRegister>(instruction).source;
        auto dest   = std::get<Instructions::MemTwoRegister>(instruction).dest;

        switch (std::get<Instructions::MemTwoRegister>(instruction).instruction) {
            case Instructions::MemTwoRegister::MOV:
                break;

            case Instructions::MemTwoRegister::SHR:
                break;

            case Instructions::MemTwoRegister::SHL:
                break;

            case Instructions::MemTwoRegister::ADD:
                break;

            case Instructions::MemTwoRegister::SUB:
                break;

            case Instructions::MemTwoRegister::XOR:
                break;

            case Instructions::MemTwoRegister::OR:
                break;

            case Instructions::MemTwoRegister::AND:
                break;

            case Instructions::MemTwoRegister::CMPRS:
                break;

            case Instructions::MemTwoRegister::CMPRE:

                break;
        }
    } else if (std::holds_alternative<Instructions::ImmTwoRegister>(instruction)) {
    } else if (std::holds_alternative<Instructions::TwoRegister>(instruction)) {
    } else {
        std::unreachable();
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
