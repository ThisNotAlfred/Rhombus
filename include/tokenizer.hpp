#pragma once

#include <string>
#include <vector>

class Tokenizer
{
        public:
    Tokenizer(std::string& content) : content(content) {};
    ~Tokenizer() = default;

    auto tokenize() -> std::vector<std::string>;

    auto tokenize_brackets() -> std::string;
    auto tokenize_instruction() -> std::string;
    auto tokenize_string() -> std::string;
    auto skip_comment() -> void;

        private:
    std::string_view content;
    std::size_t current_header = 0;
};