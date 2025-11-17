#include <iostream>
#include <fstream>
#include <sstream>

#include "generation.hpp"
#include "tokenization.hpp"
#include "parser.hpp"


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

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value()) {
        std::cerr << "NO EXIT STATEMENT FOUND!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());

    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("/usr/bin/ld -o out out.o");

    return EXIT_SUCCESS;
}
