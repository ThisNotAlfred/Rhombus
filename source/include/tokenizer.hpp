#pragma once

#include <memory>
#include <string_view>
#include <vector>

class Tokenizer
{
        public:
    Tokenizer(std::vector<char>& content) : content(content) {};
    ~Tokenizer() = default;

    auto tokenize() -> std::vector<std::string_view>;

    auto tokenize_instruction() -> std::string_view;

        private:
    std::vector<char> content;
    std::size_t current_header = 0;
};