#pragma once

#include <memory>
#include <string_view>
#include <vector>

class Tokenizer
{
        public:
    Tokenizer(std::string& content) : content(content) {};
    ~Tokenizer() = default;

    auto tokenize() -> std::vector<std::string>;
    auto tokenize_instruction() -> std::string;

        private:
    std::string_view content;
    std::size_t current_header = 0;
};