#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tokenization.hpp"


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

    return EXIT_SUCCESS;
}
