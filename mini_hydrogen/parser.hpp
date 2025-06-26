#pragma once
#include <vector>
#include <string>
#include "tokenizer.hpp"

struct Expression {
    virtual ~Expression() = default;
};

struct NumberExpr : Expression {
    int value;
    NumberExpr(int val) : value(val) {}
};

struct VariableExpr : Expression {
    std::string name;
    VariableExpr(std::string n) : name(std::move(n)) {}
};

struct BinaryExpr : Expression {
    Expression* left;
    Expression* right;
    char op;  // '+', '-', '*', '/'
    BinaryExpr(Expression* l, Expression* r, char o) : left(l), right(r), op(o) {}
};

struct Statement {
    virtual ~Statement() = default;
};

struct LetStatement : Statement {
    std::string name;
    Expression* expr;
    LetStatement(std::string n, Expression* e) : name(std::move(n)), expr(e) {}
};

struct PrintStatement : Statement {
    Expression* expr;
    PrintStatement(Expression* e) : expr(e) {}
};

class Parser {
    std::vector<Token> tokens;
    size_t index = 0;

    Token peek() const { return tokens[index]; }
    Token advance() { return tokens[index++]; }

    bool match(TokenType type) {
        if (peek().type == type) {
            advance();
            return true;
        }
        return false;
    }

    // Parses a primary expression (number or variable)
    Expression* parse_primary() {
        if (peek().type == TokenType::Number) {
            int value = std::stoi(peek().text);
            advance();
            return new NumberExpr(value);
        }
        if (peek().type == TokenType::Identifier) {
            std::string name = peek().text;
            advance();
            return new VariableExpr(name);
        }
        return nullptr;
    }

    // Parses multiplication and division
    Expression* parse_factor() {
        Expression* left = parse_primary();

        while (peek().type == TokenType::Star || peek().type == TokenType::Slash) {
            TokenType op = peek().type;
            advance();
            Expression* right = parse_primary();
            char oper = (op == TokenType::Star) ? '*' : '/';
            left = new BinaryExpr(left, right, oper);
        }

        return left;
    }

    // Parses addition and subtraction
    Expression* parse_expression() {
        Expression* left = parse_factor();

        while (peek().type == TokenType::Plus || peek().type == TokenType::Minus) {
            TokenType op = peek().type;
            advance();
            Expression* right = parse_factor();
            char oper = (op == TokenType::Plus) ? '+' : '-';
            left = new BinaryExpr(left, right, oper);
        }

        return left;
    }

public:
    Parser(const std::vector<Token>& toks) : tokens(toks) {}

    std::vector<Statement*> parse() {
        std::vector<Statement*> stmts;
        while (peek().type != TokenType::EndOfFile) {
            if (match(TokenType::Let)) {
                std::string name = peek().text;
                advance();
                match(TokenType::Equal);
                Expression* expr = parse_expression();
                match(TokenType::Semicolon);
                stmts.push_back(new LetStatement(name, expr));
            } else if (match(TokenType::Print)) {
                Expression* expr = parse_expression();
                match(TokenType::Semicolon);
                stmts.push_back(new PrintStatement(expr));
            } else {
                advance(); // Skip invalid
            }
        }
        return stmts;
    }
};
