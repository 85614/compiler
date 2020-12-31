
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
    sub esp, 0x18
    mov eax, 0
    mov [ebp-0x18], eax
for_go_on_0:
    mov eax, [ebp-0x18]
    cmp eax, 3
    jge goto0
    mov eax, [ebp-0x18]
    add eax, 1 ; +
    mov ebx, 0x4
    imul ebx, [ebp-0x18]
    mov ecx, ebp
    sub ecx, 0xc
    add ebx, ecx
    mov [ebx], eax
    mov eax, [ebp-0x18]
    add eax, 1 ; +
    mov [ebp-0x18], eax
    jmp for_go_on_0
goto0:
    mov eax, 0
    mov [ebp-0x18], eax
for_go_on_1:
    mov eax, [ebp-0x18]
    cmp eax, 3
    jge goto1
    mov eax, 0x4
    imul eax, [ebp-0x18]
    mov ebx, ebp
    sub ebx, 0xc
    add eax, ebx
    sub esp, 0x4
    mov [ebp-0x1c], eax
    mov ebx, [ebp-0x1c]
    mov ecx, [ebx]
    push ecx
    call print_int
    mov eax, [ebp-0x18]
    add eax, 1 ; +
    mov [ebp-0x18], eax
    jmp for_go_on_1
goto1:
    mov eax, ebp
    sub eax, 0xc
    mov [ebp-0x10], eax
    mov eax, ebp
    sub eax, 0x10
    mov [ebp-0x14], eax
    mov ebx, [ebp-0x14]
    mov eax, [ebx]
    mov ebx, 2
    sal ebx, 0x2
    add eax, ebx ; +
    mov ebx, 4
    mov [eax], ebx
    mov eax, 0
    mov [ebp-0x18], eax
for_go_on_2:
    mov eax, [ebp-0x18]
    cmp eax, 3
    jge goto2
    mov eax, 0x4
    imul eax, [ebp-0x18]
    mov ebx, ebp
    sub ebx, 0xc
    add eax, ebx
    sub esp, 0x4
    mov [ebp-0x24], eax
    mov ebx, [ebp-0x24]
    mov ecx, [ebx]
    push ecx
    call print_int
    mov eax, [ebp-0x18]
    add eax, 1 ; +
    mov [ebp-0x18], eax
    jmp for_go_on_2
goto2:
    mov ebx, [ebp-0x14]
    mov ecx, [ebx]
    mov ebx, [ecx]
    push ebx
    call print_int
    mov eax, ebp
    sub eax, 0xc
    mov ebx, 2
    sal ebx, 0x2
    add eax, ebx ; +
    mov [ebp-0x10], eax
    mov ebx, [ebp-0x14]
    mov ecx, [ebx]
    mov ebx, [ecx]
    push ebx
    call print_int
    mov eax, [ebp-0x10]
    mov ebx, ebp
    sub ebx, 0xc
    sub eax, ebx ; -
    sar eax, 0x2
    push eax
    call print_int
return_1:
    mov esp, ebp
    pop ebp
    ret

section .data

