#pragma once
#include <string>
#include <optional>
#include <vector>

enum class TokenType {
    exit,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {
public:
    inline Tokenizer(std::string src) : m_src(std::move(src)) {
    }

    inline std::vector<Token> tokenize() {
    }

private:

    std::optional<char> peek() const {
        if (m_index + 1 >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index);
    }

    int m_index;
    const std::string m_src;
};
