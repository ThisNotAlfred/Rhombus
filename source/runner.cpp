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
                    std::cout << "nop\n";
                    continue;
            }
        }

        if (std::holds_alternative<InstOneReg>(instruction)) {
            switch (std::get<InstOneReg>(instruction).instruction) {
                case InstOneReg::JMPE:
                    std::cout << "jmpe " << std::get<InstOneReg>(instruction).dest << "\n";
                    break;

                case InstOneReg::JMPB:
                    std::cout << "jmpb " << std::get<InstOneReg>(instruction).dest << "\n";
                    break;

                case InstOneReg::JMPS:
                    std::cout << "jmps " << std::get<InstOneReg>(instruction).dest << "\n";
                    break;

                case InstOneReg::PRINT:
                    std::cout << "print " << std::get<InstOneReg>(instruction).dest << "\n";
                    break;

                case InstOneReg::SCAN:
                    std::cout << "scan " << std::get<InstOneReg>(instruction).dest << "\n";
                    break;
            }
        }

        if (std::holds_alternative<InstTwoReg>(instruction)) {
            switch (std::get<InstTwoReg>(instruction).instruction) {
                case InstTwoReg::MOV:
                    std::cout << "mov " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::SHR:
                    std::cout << "shr " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::SHL:
                    std::cout << "shl " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::ADD:
                    std::cout << "add " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::SUB:
                    std::cout << "sub " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::XOR:
                    std::cout << "xor " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::OR:
                    std::cout << "or " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::AND:
                    std::cout << "and " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;

                case InstTwoReg::CMPR:
                    std::cout << "cmpr " << std::get<InstTwoReg>(instruction).dest << " "
                              << std::get<InstTwoReg>(instruction).source << "\n";
                    break;
            }
        }
    }
}
