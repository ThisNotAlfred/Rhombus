#include "parser.hpp"
#include "runner.hpp"
#include "tokenizer.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string_view>

auto
read_file(const char* path) -> std::string
{
    auto file_size = std::filesystem::file_size(path);
    std::ifstream file(path, std::ios::in | std::ios::binary);

    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return contents;
}

auto
main(int argc, char* argv[]) -> int
{
    if (argc < 2 || argc > 2) {
        std::cerr
            << "wrong number of arguments to input. only provide path to your `.rhom` file.\n";
        return -1;
    }

    if (!std::filesystem::exists(argv[1])) {
        std::cerr << "provided input doesn't exist.\n";
        return -1;
    }

    auto contents  = read_file(argv[1]);
    auto tokenized = Tokenizer(contents).tokenize();
    auto parsed    = Parser(tokenized).parse();
    auto runner    = Runner(parsed);
    runner.run_instruction();

    return 0;
}
