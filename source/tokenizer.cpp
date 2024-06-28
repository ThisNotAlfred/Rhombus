#include "tokenizer.hpp"

#include <algorithm>

auto
Tokenizer::tokenize() -> std::vector<std::string>
{
    std::vector<std::string> tokens;

    for (; this->current_header < this->content.size();) {
        // skipping whitespaces
        if (this->content[this->current_header] == ' ' ||
            this->content[this->current_header] == '\n' ||
            this->content[this->current_header] == '\r' ||
            this->content[this->current_header] == '\t') {
            this->current_header++;
            continue;
        }

        if (this->content[this->current_header] == ';') {
            skip_comment();
        }

        if (this->content[this->current_header] == '[') {
            tokens.push_back(this->tokenize_brackets());
        }

        // reading whole tokens of instructions
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

    for (auto i = this->current_header; i < this->content.size(); ++i) {
        this->current_header++;

        if (this->content[i] == '\n' || this->content[i] == '\r' || this->content[i] == ',' ||
            this->content[i] == ';') {
            break;
        }

        temp_token.push_back(this->content[i]);
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    return token;
}


auto
Tokenizer::tokenize_instruction() -> std::string
{
    std::vector<char> temp_token = {};

    for (auto i = this->current_header; i < this->content.size(); ++i) {
        this->current_header++;


        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\0' || this->content[i] == ',' || this->content[i] == '\r' ||
            this->content[i] == ';' || this->content[i] == '[') {
            break;
        }

        temp_token.push_back(this->content[i]);
    }

    auto token = std::string { temp_token.begin(), temp_token.end() };

    std::transform(token.begin(), token.end(), token.begin(),
                   [](auto chr) { return std::tolower(chr); });

    return token;
}

auto
Tokenizer::skip_comment() -> void
{
    for (auto i = this->current_header; i < this->content.size(); ++i) {
        this->current_header++;
        if (this->content[i] == '\n') {
            break;
        }
    }
}