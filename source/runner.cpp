#include "runner.hpp"
#include "instruction.hpp"

#include <iostream>
#include <tuple>
#include <variant>

auto
Runner::run() -> void
{
    for (const auto& instruction : this->instructions) {
        if (std::holds_alternative<InstNoReg>(instruction)) {
            switch (std::get<InstNoReg>(instruction).instruction) {
                case InstNoReg::NOP:
                    continue;
            }
        }

        if (std::holds_alternative<InstOneReg>(instruction)) {
            switch (std::get<InstOneReg>(instruction).instruction) {
                case InstOneReg::JMP:
                    break;

                case InstOneReg::JMPE:
                    break;

                case InstOneReg::JMPB:
                    break;

                case InstOneReg::JMPS:
                    break;

                case InstOneReg::PRINT:
                    break;

                case InstOneReg::SCAN:
                    break;
            }
        }

        if (std::holds_alternative<InstTwoReg>(instruction)) {
            auto src  = std::get<InstTwoReg>(instruction).source;
            auto dest = std::get<InstTwoReg>(instruction).dest;

            switch (std::get<InstTwoReg>(instruction).instruction) {
                case InstTwoReg::MOV:
                    this->memory[dest] = src;
                    break;

                case InstTwoReg::SHR:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] >> src; });

                    this->memory[dest] >>= src;
                    break;

                case InstTwoReg::SHL:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] << src; });

                    this->memory[dest] <<= src;
                    break;

                case InstTwoReg::ADD:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] + src; });

                    this->memory[dest] += src;
                    break;

                case InstTwoReg::SUB:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] - src; });

                    this->memory[dest] -= src;
                    break;

                case InstTwoReg::XOR:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] ^ src; });

                    this->memory[dest] ^= src;
                    break;

                case InstTwoReg::OR:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] | src; });

                    this->memory[dest] |= src;
                    break;

                case InstTwoReg::AND:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] & src; });

                    this->memory[dest] &= src;
                    break;

                case InstTwoReg::CMPRS:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return this->memory[dest] > src; });
                    break;

                case InstTwoReg::CMPRE:
                    this->check_for_flags(
                        src, this->memory[dest],
                        [this](uint16_t src, uint16_t dest) { return dest == src; });
                    break;
            }
        }
    }
}

inline auto
Runner::check_for_flags(std::uint16_t source, std::uint16_t dest,
                        const std::function<std::uint16_t(std::uint16_t, std::uint16_t)>& opr)
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
