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
    explicit Tokenizer(std::string src) : m_index(0),
                                          m_src(std::move(src)) {
    }

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::string buf;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }

                if (buf == "exit") {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                }

                std::cerr << "Invalid token!" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }

            if (peek().value() == ';') {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }

            if (std::isspace(peek().value())) {
                while (std::isspace(peek().value())) {
                    consume();
                }
                continue;
            }

            std::cerr << "Invalid syntax!" << std::endl;
            exit(EXIT_FAILURE);
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(int ahead = 1) const {
        if (m_index + ahead > m_src.length()) {
            return {};
        }
        return m_src.at(m_index);
    }

    char consume() {
        return m_src.at(m_index++);
    }

    int m_index;
    const std::string m_src;
};
