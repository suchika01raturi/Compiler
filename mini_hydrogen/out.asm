section .data
fmt db "%d", 10, 0
section .bss
x resq 1
section .text
global main
extern printf
main:
    mov rax, 5
    push rax
    mov rax, 3
    push rax
    mov rax, 2
    pop rcx
    imul rax, rcx
    pop rcx
    add rax, rcx
    push rax
    mov rax, 4
    push rax
    mov rax, 2
    pop rcx
    xor rdx, rdx
    mov rbx, rax
    mov rax, rcx
    idiv rbx
    pop rcx
    sub rcx, rax
    mov rax, rcx
    mov [rel x], rax
    mov rdx, [rel x]
    lea rcx, [rel fmt]
    xor rax, rax
    call printf
    mov rax, 0
    ret
