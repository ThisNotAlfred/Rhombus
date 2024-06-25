#include "instruction.hpp"

#include <string_view>
#include <vector>

class Parser
{
        public:
    Parser(std::vector<std::string_view>& tokens) : tokens(tokens) {};
    ~Parser() = default;

    auto parse() -> std::vector<Instruction>;

        private:
    std::vector<std::string_view> tokens = {};
};