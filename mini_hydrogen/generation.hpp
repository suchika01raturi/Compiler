#pragma once
#include <fstream>
#include <unordered_map>
#include "parser.hpp"

class CodeGenerator {
    std::vector<Statement*> ast;
    std::unordered_map<std::string, bool> variables;  // Track declared variables

    void generate_expr(std::ofstream& out, Expression* expr) {
        if (auto num = dynamic_cast<NumberExpr*>(expr)) {
            out << "    mov rax, " << num->value << "\n";
        }
        else if (auto var = dynamic_cast<VariableExpr*>(expr)) {
            out << "    mov rax, [rel " << var->name << "]\n";
        }
        else if (auto bin = dynamic_cast<BinaryExpr*>(expr)) {
            generate_expr(out, bin->left);
            out << "    push rax\n";
            generate_expr(out, bin->right);
            out << "    pop rcx\n";

            switch (bin->op) {
                case '+':
                    out << "    add rax, rcx\n";
                    break;
                case '-':
                    out << "    sub rcx, rax\n";   // rcx = left - right (swap)
                    out << "    mov rax, rcx\n";
                    break;
                case '*':
                    out << "    imul rax, rcx\n";
                    break;
                case '/':
                    out << "    xor rdx, rdx\n";    // clear rdx before idiv
                    out << "    mov rbx, rax\n";    // divisor in rbx
                    out << "    mov rax, rcx\n";    // dividend in rax
                    out << "    idiv rbx\n";        // divide rax by rbx; quotient in rax
                    break;
            }
        }
    }

public:
    CodeGenerator(const std::vector<Statement*>& s) : ast(s) {}

    void generate(const std::string& filename) {
        std::ofstream out(filename);

        // Section .data: format string for printf
        out << "section .data\n";
        out << "fmt db \"%d\", 10, 0\n";

        // Collect variables from AST
        for (Statement* stmt : ast) {
            if (auto letStmt = dynamic_cast<LetStatement*>(stmt)) {
                variables[letStmt->name] = true;
            }
        }

        // Section .bss: uninitialized variables
        out << "section .bss\n";
        for (auto& pair : variables) {
            out << pair.first << " resq 1\n";
        }

        // Section .text: code
        out << "section .text\n";
        out << "global main\n";
        out << "extern printf\n";
        out << "main:\n";

        for (Statement* stmt : ast) {
            if (auto letStmt = dynamic_cast<LetStatement*>(stmt)) {
                generate_expr(out, letStmt->expr);
                out << "    mov [rel " << letStmt->name << "], rax\n";
            }
            else if (auto printStmt = dynamic_cast<PrintStatement*>(stmt)) {
                if (auto var = dynamic_cast<VariableExpr*>(printStmt->expr)) {
                    out << "    mov rdx, [rel " << var->name << "]\n";
                }
                else if (auto num = dynamic_cast<NumberExpr*>(printStmt->expr)) {
                    out << "    mov rdx, " << num->value << "\n";
                }
                else {
                    generate_expr(out, printStmt->expr);
                    out << "    mov rdx, rax\n";
                }
                out << "    lea rcx, [rel fmt]\n";   // 1st argument: format string
                out << "    xor rax, rax\n";         // zero rax for variadic functions
                out << "    call printf\n";
            }
        }

        out << "    mov rax, 0\n";
        out << "    ret\n";
    }
};
