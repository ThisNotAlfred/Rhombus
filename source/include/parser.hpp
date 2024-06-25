#include "instruction.hpp"

#include <string_view>
#include <vector>

class Parser
{
        public:
    Parser(std::vector<std::string_view>& tokens) : tokens(tokens) {};
    ~Parser() = default;

    auto parse() -> std::vector<Instruction>;

    auto no_reg(std::size_t index) -> Instruction;
    auto one_reg(std::size_t index) -> Instruction;
    auto two_reg(std::size_t index) -> Instruction;

        private:
    std::vector<std::string_view> tokens = {};
};