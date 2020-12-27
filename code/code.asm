
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
    sub esp, 0x10
    mov eax, 1
    mov [ebp-0x8], eax
    mov eax, 3
    mov [ebp-0xc], eax
    mov eax, 10
    mov ebx, 2
    cdq
    idiv ebx
    mov ebx, 3
    mov ecx, eax
    mov eax, 1
pow_go_on_0:
    cmp ebx, 0
    jle pow_over_0
    imul eax, ecx
    sub ebx, 1
    jmp pow_go_on_0
pow_over_0:
    mov ebx, [ebp-0x8]
    add ebx, eax
    mov [ebp-0x4], ebx
    mov eax, [ebp-0x4]
    cmp eax, 0
    je goto1
    mov eax, [ebp-0x4]
    push eax
    call print_int
while_go_on_2:
    mov eax, [ebp-0x4]
    cmp eax, 10
    jge goto3
    mov eax, [ebp-0x8]
    cmp eax, 10
    jge goto3
    mov eax, 1
    jmp goto4
goto3:
    mov eax, 0
goto4:
    cmp eax, 0
    je goto2
    mov eax, [ebp-0x4]
    push eax
    call print_int
    mov eax, [ebp-0x4]
    mov ebx, [ebp-0x8]
    imul eax, ebx
    mov ebx, [ebp-0xc]
    imul eax, ebx
    mov [ebp-0x4], eax
    mov eax, [ebp-0x8]
    mov ebx, 2
    cdq
    idiv ebx
    mov [ebp-0x8], edx
    jmp while_go_on_2
goto2:
    mov eax, 0
    mov [ebp-0x10], eax
for_go_on_5:
    mov eax, [ebp-0x10]
    cmp eax, 1
    jge goto5
    mov eax, [ebp-0x8]
    add eax, [ebp-0x4]
    mov [ebp-0x10], eax
    mov eax, 1
    add eax, [ebp-0x10]
    mov [ebp-0x10], eax
    jmp for_go_on_5
goto5:
goto1:
    mov eax, [ebp-0x4]
    push eax
    call print_int
    mov eax, [ebp-0x4]
    jmp return_1
return_1:
    mov esp, ebp
    pop ebp
    ret

section .data

