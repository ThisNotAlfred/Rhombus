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
read_file(const char* path) -> std::vector<char>
{
    auto file_size = std::filesystem::file_size(path);
    std::ifstream file(path, std::ios::in | std::ios::binary);

    std::vector<char> contents((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());

    return std::move(contents);
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
    std::for_each(tokenized.begin(), tokenized.end(),
                  [](auto element) { std::cout << element << ";"; });
    auto parsed = Parser(tokenized).parse();
    auto runner = Runner(parsed);
    runner.run();

    return 0;
}
