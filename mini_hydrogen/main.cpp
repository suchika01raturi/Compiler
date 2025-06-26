#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "generation.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: hydro <file.hy>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open input file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    Tokenizer tokenizer(source);
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(tokens);
    std::vector<Statement*> ast = parser.parse();

    CodeGenerator generator(ast);
    generator.generate("out.asm");

    system("nasm -fwin64 out.asm -o out.obj");
    system("g++ out.obj -o out.exe");

    std::cout << "Compilation successful. Run: ./out.exe" << std::endl;
    return 0;
}