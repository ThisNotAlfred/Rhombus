#include "runner.hpp"
#include "instruction.hpp"

#include <iostream>
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
Runner::run_instruction(const Instruction& instruction) -> void
{
    if (std::holds_alternative<InstNoReg>(instruction)) {
        switch (std::get<InstNoReg>(instruction).instruction) {
            case InstNoReg::NOP:
                ++this->instruction_pointer;
        }
    }

    else if (std::holds_alternative<InstOneReg>(instruction)) {
        auto dest = std::get<InstOneReg>(instruction).dest;

        switch (std::get<InstOneReg>(instruction).instruction) {
            case InstOneReg::JMP:
                this->instruction_pointer = dest;
                break;

            case InstOneReg::JMPE:
                if (this->zero_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case InstOneReg::JMPB:
                if (this->zero_flag && this->negative_flag == this->overflow_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case InstOneReg::JMPS:
                if (this->negative_flag != this->overflow_flag) {
                    this->instruction_pointer = dest;
                } else {
                    ++this->instruction_pointer;
                }
                break;

            case InstOneReg::PRINT:
                std::cout << static_cast<char>(this->memory[dest]);
                break;

            case InstOneReg::SCAN:
                std::cin >> this->memory[dest];
                break;
        }
    }

    else if (std::holds_alternative<InstTwoReg>(instruction)) {
        auto src  = std::get<InstTwoReg>(instruction).source;
        auto dest = std::get<InstTwoReg>(instruction).dest;

        switch (std::get<InstTwoReg>(instruction).instruction) {
            case InstTwoReg::MOV:
                this->memory[dest] = src;
                break;

            case InstTwoReg::SHR:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] >> src;
                });
                this->memory[dest] >>= src;
                ++this->instruction_pointer;
                break;

            case InstTwoReg::SHL:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] << src;
                });
                this->memory[dest] <<= src;
                ++this->instruction_pointer;

                break;

            case InstTwoReg::ADD:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] + src;
                });
                this->memory[dest] += src;
                ++this->instruction_pointer;

                break;

            case InstTwoReg::SUB:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] - src;
                });
                this->memory[dest] -= src;
                ++this->instruction_pointer;
                break;

            case InstTwoReg::XOR:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] ^ src;
                });
                this->memory[dest] ^= src;
                ++this->instruction_pointer;
                break;

            case InstTwoReg::OR:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] | src;
                });
                this->memory[dest] |= src;
                ++this->instruction_pointer;
                break;

            case InstTwoReg::AND:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] & src;
                });
                this->memory[dest] &= src;
                ++this->instruction_pointer;
                break;

            case InstTwoReg::CMPRS:
                this->check_for_flags(src, this->memory[dest], [this](uint16_t src, uint16_t dest) {
                    return this->memory[dest] > src;
                });
                ++this->instruction_pointer;
                break;

            case InstTwoReg::CMPRE:
                this->check_for_flags(src, this->memory[dest],
                                      [](uint16_t src, uint16_t dest) { return dest == src; });
                ++this->instruction_pointer;
                break;
        }
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
