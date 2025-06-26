#pragma once
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    Let, Identifier, Number,
    Equal, Plus, Minus, Star, Slash,
    Print, Semicolon,
    EndOfFile, Invalid
};

struct Token {
    TokenType type;
    std::string text;

    Token(TokenType t, std::string txt) : type(t), text(std::move(txt)) {}
};

class Tokenizer {
    std::string source;
    size_t index = 0;

public:
    Tokenizer(const std::string& src) : source(src) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (index < source.size()) {
            char c = source[index];

            if (std::isspace(c)) {
                index++;
                continue;
            }

            if (std::isalpha(c)) {
                std::string ident;
                while (index < source.size() && std::isalnum(source[index])) {
                    ident += source[index++];
                }
                if (ident == "let") tokens.emplace_back(TokenType::Let, ident);
                else if (ident == "print") tokens.emplace_back(TokenType::Print, ident);
                else tokens.emplace_back(TokenType::Identifier, ident);
                continue;
            }

            if (std::isdigit(c)) {
                std::string num;
                while (index < source.size() && std::isdigit(source[index])) {
                    num += source[index++];
                }
                tokens.emplace_back(TokenType::Number, num);
                continue;
            }

            switch (c) {
                case '=': tokens.emplace_back(TokenType::Equal, "="); break;
                case '+': tokens.emplace_back(TokenType::Plus, "+"); break;
                case '-': tokens.emplace_back(TokenType::Minus, "-"); break;
                case '*': tokens.emplace_back(TokenType::Star, "*"); break;
                case '/': tokens.emplace_back(TokenType::Slash, "/"); break;
                case ';': tokens.emplace_back(TokenType::Semicolon, ";"); break;
                default: tokens.emplace_back(TokenType::Invalid, std::string(1, c)); break;
            }
            index++;
        }

        tokens.emplace_back(TokenType::EndOfFile, "");
        return tokens;
    }
};
