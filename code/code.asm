
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
    sub esp, 0x1c
    mov eax, ebp
    sub eax, 0xc
    mov [ebp-0x10], eax
    mov eax, ebp
    sub eax, 0xc
    mov ebx, 1
    sal ebx, 0x2
    add eax, ebx
    mov [ebp-0x14], eax
    mov eax, [ebp-0x10]
    mov ebx, 2
    sal ebx, 0x2
    add eax, ebx
    mov [ebp-0x18], eax
    mov eax, 1
    mov ebx, [ebp-0x10]
    mov [ebx], eax
    mov eax, 2
    mov ebx, [ebp-0x14]
    mov [ebx], eax
    mov eax, 3
    mov ebx, [ebp-0x18]
    mov [ebx], eax
    mov eax, 0
    mov [ebp-0x1c], eax
for_go_on_0:
    mov eax, [ebp-0x1c]
    cmp eax, 3
    jge goto0
    mov eax, 0x4
    imul eax, [ebp-0x1c]
    mov ebx, ebp
    sub ebx, 0xc
    add eax, ebx
    mov ebx, [eax]
    push ebx
    call print_int
    mov eax, [ebp-0x1c]
    add eax, 1
    mov [ebp-0x1c], eax
    jmp for_go_on_0
goto0:
    mov eax, [ebp-0x18]
    sub eax, [ebp-0x10]
    sar eax, 0x2
    push eax
    call print_int
return_1:
    mov esp, ebp
    pop ebp
    ret

section .data

