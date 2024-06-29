#include "parser.hpp"

#include <print>

namespace
{
inline auto
get_register(std::string& reg)
{
    if (reg == "i0") {
        return Instructions::Register::i0;
    }

    if (reg == "i1") {
        return Instructions::Register::i1;
    }

    if (reg == "i2") {
        return Instructions::Register::i2;
    }

    if (reg == "i3") {
        return Instructions::Register::i3;
    }

    if (reg == "i4") {
        return Instructions::Register::i4;
    }

    if (reg == "i5") {
        return Instructions::Register::i5;
    }

    if (reg == "i6") {
        return Instructions::Register::i6;
    }

    if (reg == "i7") {
        return Instructions::Register::i7;
    }

    if (reg == "i8") {
        return Instructions::Register::i8;
    }

    if (reg == "i9") {
        return Instructions::Register::i9;
    }

    if (reg == "i10") {
        return Instructions::Register::i10;
    }

    if (reg == "i11") {
        return Instructions::Register::i11;
    }

    if (reg == "i12") {
        return Instructions::Register::i12;
    }

    if (reg == "i13") {
        return Instructions::Register::i13;
    }

    if (reg == "i14") {
        return Instructions::Register::i14;
    }

    if (reg == "i15") {
        return Instructions::Register::i15;
    }

    std::print(stderr, "wrong register parameter {}\n", reg);
    std::exit(EXIT_FAILURE);
}

inline auto
parse_value(std::string& token)
{
    token.erase(token.begin());

    return static_cast<std::uint16_t>(std::stoi(token));
}

inline auto
parse_brackets(std::string& token)
{
    token.erase(token.begin());

    return static_cast<std::uint16_t>(std::stoi(token));
}

inline auto
parse_variable(std::string& token)
{
    auto split_point = token.find('[');

    // reconstructing label
    std::string label = {};
    label.append(token.data(), split_point);
    label.replace(0, 1, "@");

    std::string index_token = token.substr(split_point, token.size() - split_point);
    // removing brackets
    index_token.erase(index_token.begin());
    index_token.erase(index_token.find(']'));
    // parsing index
    auto index = get_register(index_token);

    return std::make_pair(label, index);
}
}; // namespace

auto
Parser::parse() -> std::vector<Instructions::Instruction>
{
    std::vector<Instructions::Instruction> instructions = {};

    for (std::size_t i = 0; i < this->tokens.size();) {
        if (this->tokens[i][0] == '@') {
            this->labels.emplace(this->tokens[i], instructions.size());
            i += 1;
        }

        else if (this->tokens[i] == "db") {
            for (const auto& chr : this->tokens[i + 1]) {
                instructions.emplace_back(
                    Instructions::Data { static_cast<Instructions::Data>(chr) });
            }
            i += 2;
        }

        else if (this->tokens[i] == "mov") {
            instructions.emplace_back(this->parse_mov(i));
            i += 3;
        }

        else if (this->tokens[i] == "add") {
            instructions.emplace_back(this->parse_add(i));
            i += 3;
        }

        else if (this->tokens[i] == "sub") {
            instructions.emplace_back(this->parse_sub(i));
            i += 3;
        }

        else if (this->tokens[i] == "shr") {
            instructions.emplace_back(this->parse_shr(i));
            i += 3;
        }

        else if (this->tokens[i] == "shl") {
            instructions.emplace_back(this->parse_shl(i));
            i += 3;
        }

        else if (this->tokens[i] == "xor") {
            instructions.emplace_back(this->parse_xor(i));
            i += 3;
        }

        else if (this->tokens[i] == "or") {
            instructions.emplace_back(this->parse_or(i));
            i += 3;
        }

        else if (this->tokens[i] == "and") {
            instructions.emplace_back(this->parse_and(i));
            i += 3;
        }

        else if (this->tokens[i] == "cmp") {
            instructions.emplace_back(this->parse_cmp(i));
            i += 3;
        }

        else if (this->tokens[i] == "jmp") {
            instructions.emplace_back(this->parse_jmp(i));
            i += 2;
        }

        else if (this->tokens[i] == "jmpe") {
            instructions.emplace_back(this->parse_jmpe(i));
            i += 2;

        }

        else if (this->tokens[i] == "jmpb") {
            instructions.emplace_back(this->parse_jmpb(i));
            i += 2;
        }

        else if (this->tokens[i] == "jmps") {
            instructions.emplace_back(this->parse_jmps(i));
            i += 2;
        }

        else if (this->tokens[i] == "print") {
            instructions.emplace_back(this->parse_print(i));
            i += 2;
        }

        else if (this->tokens[i] == "scan") {
            instructions.emplace_back(this->parse_scan(i));
            i += 2;
        }

        else if (this->tokens[i] == "nop") {
            instructions.emplace_back(Instructions::NoOp { Instructions::NoOp::NOP });
            i += 1;
        }

        else {
            std::print(stderr, "wrong parameter at token {}\n", this->tokens[i]);
            std::exit(EXIT_FAILURE);
        }
    }

    return instructions;
}

auto
Parser::parse_mov(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::MOV,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::MOV,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::MOV,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::MOV,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_add(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::ADD,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::ADD,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::ADD,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::ADD,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_sub(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::SUB,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::SUB,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::SUB,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::SUB,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_shr(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::SHR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::SHR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::SHR,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::SHR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_shl(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::SHL,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::SHL,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::SHL,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::SHL,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_xor(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::XOR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::XOR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::XOR,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::XOR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_or(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::OR,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::OR,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::OR,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::OR,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_and(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::AND,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::AND,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::AND,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::AND,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_cmp(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '$') {
        return Instructions::ImmTwoOp {
            Instructions::ImmTwoOp::CMP,
            parse_value(this->tokens[index + 1]),
            get_register(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 2][0] == '[') {
        return Instructions::MemTwoOp {
            Instructions::MemTwoOp::CMP,
            get_register(this->tokens[index + 1]),
            parse_brackets(this->tokens[index + 2]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexTwoOp {
            Instructions::IndexTwoOp::CMP,
            data_index,
            this->labels[label],
            get_register(this->tokens[index + 2]),
        };
    }

    return Instructions::TwoOp {
        Instructions::TwoOp::CMP,
        get_register(this->tokens[index + 1]),
        get_register(this->tokens[index + 2]),
    };
}

auto
Parser::parse_jmp(std::size_t index) -> Instructions::Instruction
{
    std::size_t jump_dest = 0;
    if (this->tokens[index + 1][0] == '@') {
        jump_dest = this->labels[this->tokens[index + 1]];
    } else {
        jump_dest = parse_brackets(this->tokens[index + 1]);
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexOneOp {
            Instructions::IndexOneOp::JMP,
            data_index,
            this->labels[label],
        };
    }

    return Instructions::MemOneOp {
        Instructions::MemOneOp::JMP,
        jump_dest,
    };
}

auto
Parser::parse_jmpe(std::size_t index) -> Instructions::Instruction
{
    std::size_t jump_dest = 0;
    if (this->tokens[index + 1][0] == '@') {
        jump_dest = this->labels[this->tokens[index + 1]];
    } else {
        jump_dest = parse_brackets(this->tokens[index + 1]);
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexOneOp {
            Instructions::IndexOneOp::JMPE,
            data_index,
            this->labels[label],
        };
    }

    return Instructions::MemOneOp {
        Instructions::MemOneOp::JMPE,
        jump_dest,
    };
}

auto
Parser::parse_jmpb(std::size_t index) -> Instructions::Instruction
{
    std::size_t jump_dest = 0;
    if (this->tokens[index + 1][0] == '@') {
        jump_dest = this->labels[this->tokens[index + 1]];
    } else {
        jump_dest = parse_brackets(this->tokens[index + 1]);
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexOneOp {
            Instructions::IndexOneOp::JMPB,
            data_index,
            this->labels[label],
        };
    }

    return Instructions::MemOneOp {
        Instructions::MemOneOp::JMPB,
        jump_dest,
    };
}

auto
Parser::parse_jmps(std::size_t index) -> Instructions::Instruction
{
    std::size_t jump_dest = 0;
    if (this->tokens[index + 1][0] == '@') {
        jump_dest = this->labels[this->tokens[index + 1]];
    } else {
        jump_dest = parse_brackets(this->tokens[index + 1]);
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexOneOp {
            Instructions::IndexOneOp::JMPS,
            data_index,
            this->labels[label],
        };
    }

    return Instructions::MemOneOp {
        Instructions::MemOneOp::JMPS,
        jump_dest,
    };
}

auto
Parser::parse_print(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '[') {
        return Instructions::MemOneOp {
            Instructions::MemOneOp::PRINT,
            parse_brackets(this->tokens[index + 1]),
        };
    }

    if (this->tokens[index + 1][0] == '#') {
        const auto [label, data_index] = parse_variable(this->tokens[index + 1]);

        return Instructions::IndexOneOp {
            Instructions::IndexOneOp::PRINT,
            data_index,
            this->labels[label],
        };
    }

    return Instructions::OneOp {
        Instructions::OneOp::PRINT,
        get_register(this->tokens[index + 1]),
    };
}

auto
Parser::parse_scan(std::size_t index) -> Instructions::Instruction
{
    if (this->tokens[index + 1][0] == '[') {
        return Instructions::MemOneOp {
            Instructions::MemOneOp::SCAN,
            parse_brackets(this->tokens[index + 1]),
        };
    }

    return Instructions::OneOp {
        Instructions::OneOp::SCAN,
        get_register(this->tokens[index + 1]),
    };
}