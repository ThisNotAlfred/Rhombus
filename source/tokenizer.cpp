#include "tokenizer.hpp"

#include <algorithm>

auto
Tokenizer::tokenize() -> std::vector<std::string>
{
    std::vector<std::string> tokens;

    while (this->current_header < this->content.size()) {
        if (this->content[this->current_header] == ' ' ||
            this->content[this->current_header] == '\n' ||
            this->content[this->current_header] == '\r' ||
            this->content[this->current_header] == '\t' ||
            this->content[this->current_header] == ',') {
            this->current_header++;
            continue;
        }

        if (this->content[this->current_header] == ';') {
            skip_comment();
            continue;
        }

        if (this->content[this->current_header] == '"') {
            tokens.push_back(this->tokenize_string());
            continue;
        }

        if (this->content[this->current_header] == '[') {
            tokens.push_back(this->tokenize_brackets());
            continue;
        }

        tokens.push_back(this->tokenize_instruction());
    }

    tokens.erase(
        std::remove_if(tokens.begin(), tokens.end(), [](auto& element) { return element.empty(); }),
        tokens.end());

    return tokens;
}

auto
Tokenizer::tokenize_brackets() -> std::string
{
    std::vector<char> temp_token = {};

    while (
        this->current_header < this->content.size() &&
        this->content[this->current_header] != '\n' && this->content[this->current_header] != ' ' &&
        this->content[this->current_header] != ',' && this->content[this->current_header] != '$' &&
        this->content[this->current_header] != ';') {
        temp_token.push_back(this->content[current_header]);
        this->current_header++;
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    return token;
}


auto
Tokenizer::tokenize_instruction() -> std::string
{
    std::vector<char> temp_token = {};

    while (
        this->current_header < this->content.size() &&
        this->content[this->current_header] != '\n' && this->content[this->current_header] != ' ' &&
        this->content[this->current_header] != ',' && this->content[this->current_header] != '[' &&
        this->content[this->current_header] != ']' && this->content[this->current_header] != ';') {
        temp_token.push_back(this->content[this->current_header]);
        this->current_header++;
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    std::transform(token.begin(), token.end(), token.begin(),
                   [](auto chr) { return std::tolower(chr); });

    return token;
}

auto
Tokenizer::tokenize_string() -> std::string
{
    std::vector<char> temp_token = {};

    // skipping first '"'
    this->current_header++;

    while (this->current_header < this->content.size() &&
           this->content[this->current_header] != '\n' &&
           this->content[this->current_header] != '"') {
        temp_token.push_back(this->content[this->current_header]);
        this->current_header++;
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    return token;
}

auto
Tokenizer::skip_comment() -> void
{
    while (this->current_header < this->content.size() &&
           this->content[this->current_header] != '\n') {
        this->current_header++;
    }
}