#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tokenization.hpp"



std::vector<Token> tokenize(const std::string& str) {
    std::vector<Token> tokens {};

    std::string buf;
    int i = 0;
    while (i != str.size()) {
        char c = str.at(i);
        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "exit") {
                tokens.push_back({.type = TokenType::exit});
                buf.clear();
                continue;
            } else {
                std::cerr << "you messed up!";
                exit(EXIT_FAILURE);
            }

            if (std::isspace(c)) {
                continue;
            }
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "hydro <input.hy> " << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream input(argv[1], std::ios::in);
    std::stringstream strstream;
    strstream << input.rdbuf();
    input.close();

    std::string contents;
    contents = strstream.str();

    std::vector<Token> res = tokenize(contents);

    return EXIT_SUCCESS;
}
