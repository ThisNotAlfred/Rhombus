#include "tokenizer.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

auto
Tokenizer::tokenize() -> std::vector<std::string>
{
    std::vector<std::string> tokens;

    for (const auto& chr : this->content) {
        // skipping whitespaces
        if (chr == ' ' || chr == '\n' || chr == '\r' || chr == '\t' || chr == '\0' || chr == ',') {
            continue;
        }

        if (chr == '[') {
            tokens.push_back(this->tokenize_brackets());
        }

        // reading whole tokens of instructions
        tokens.push_back(this->tokenize_instruction());

        // moving header one forward
        ++this->current_header;
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                                [](auto& element) { return element.size() < 1; }),
                 tokens.end());

    return tokens;
}

auto
Tokenizer::tokenize_brackets() -> std::string
{
    std::vector<char> temp_token = {};

    for (auto i = this->current_header; i < this->content.size(); ++i) {
        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\0' || this->content[i] == ',' || this->content[i] == '\r' ||
            this->content[i] == ';' || this->content[i] == '[' || this->content[i] == ']') {
            break;
        }

        temp_token.push_back(this->content[i]);

        ++this->current_header;
    }

    // getting rid of ']'
    auto token = std::string { temp_token.begin(), temp_token.end() };

    return token;
}


auto
Tokenizer::tokenize_instruction() -> std::string
{
    std::vector<char> temp_token = {};

    for (auto i = this->current_header; i < this->content.size(); ++i) {
        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\0' || this->content[i] == ',' || this->content[i] == '\r' ||
            this->content[i] == ';' || this->content[i] == '[') {
            break;
        }

        temp_token.push_back(this->content[i]);

        ++this->current_header;
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    return token;
}
