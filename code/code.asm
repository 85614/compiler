
extern printf
global main

print_int:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 0x8]
    push 0x0a6425
    mov ebx, esp
    push eax
    push ebx
    call printf 
    mov esp, ebp
    pop ebp
    ret

main:
    push ebp
    mov ebp, esp
    sub esp, 0x8
    mov eax, 1
    mov [ebp-0x4], eax
    mov eax, [ebp-0x4]
    push eax
    call print_int
    mov eax, 2
    mov [ebp-0x8], eax
    mov eax, [ebp-0x8]
    push eax
    call print_int
    mov eax, 3
    mov [ebp-0x8], eax
    mov eax, [ebp-0x8]
    push eax
    call print_int
    mov esp, ebp
    pop ebp
    ret

section .data

