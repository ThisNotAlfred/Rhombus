#include <string_view>
#include <vector>

class Parser
{
    auto tokenize(std::string_view& content) -> std::vector<std::string_view>;
};