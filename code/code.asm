
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

fibo:
    push ebp
    mov ebp, esp
    sub esp, 0x8
    mov eax, [ebp+0x8]
    cmp eax, 1
    jne goto0
    mov eax, 1
    jmp return_1
    jmp if_over_0
goto0:
    mov eax, [ebp+0x8]
    cmp eax, 2
    jne goto1
    mov eax, 2
    jmp return_1
goto1:
if_over_0:
    mov eax, [ebp+0x8]
    sub eax, 1
    push eax
    call fibo
    mov [ebp-0x4], eax
    mov eax, [ebp+0x8]
    sub eax, 2
    push eax
    call fibo
    mov [ebp-0x8], eax
    mov eax, [ebp-0x4]
    add eax, [ebp-0x8]
    jmp return_1
return_1:
    mov esp, ebp
    pop ebp
    ret

main:
    push ebp
    mov ebp, esp
    sub esp, 0x4
    push 5
    call fibo
    mov [ebp-0x4], eax
    mov eax, [ebp-0x4]
    push eax
    call print_int
return_2:
    mov esp, ebp
    pop ebp
    ret

section .data

