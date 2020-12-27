extern printf
extern exit
global main

print_int:
    push ebp
    mov ebp, esp
    mov eax, [ebp + 0x8]
    push eax
    push format
    call printf  ; printf(format, 2)
    mov esp, ebp
    pop ebp
    ret

main:
    push ebp
    mov ebp, esp
    call print_int
    mov esp, ebp
    pop ebp
    ret


section .data
    format db "%d",0
