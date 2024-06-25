#include "tokenizer.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string_view>
#include <vector>

auto
Tokenizer::tokenize_instruction() -> std::string_view
{
    auto temp_token = std::make_shared<std::vector<char>>();

    for (auto i = this->current_header; i < this->content.size(); ++i) {
        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\0' || this->content[i] == ',' || this->content[i] == '\r' ||
            this->content[i] == ';') {
            break;
        }

        temp_token->push_back(this->content[i]);

        ++this->current_header;
    }

    return std::string_view { temp_token->begin(), temp_token->end() };
}

auto
Tokenizer::tokenize() -> std::vector<std::string_view>
{
    std::vector<std::string_view> tokens = {};

    for (const auto& chr : this->content) {
        // skipping whitespaces
        if (chr == ' ' || chr == '\n' || chr == '\r' || chr == '\t' || chr == '\0') {
            continue;
        }

        // skipping commas
        if (chr == ',') {
            continue;
        }

        // reading semi-colons
        if (chr == ';') {
            tokens.emplace_back(";");
        }

        // reading whole tokens of instructions
        tokens.emplace_back(this->tokenize_instruction());

        // moving header one forward
        ++this->current_header;
    }

    return std::move(tokens);
}
