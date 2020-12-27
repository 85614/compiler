extern printf

print:
    push ebp
    mov ebp, esp
    push edx
    push ecx
    push ebx
    push eax
    push format
    call printf  ; printf(format, 2)
    pop eax
    pop eax
    pop ebx
    pop ecx
    pop edx
    mov esp, ebp
    pop ebp
    ret

section .data
format db 'eax:%d ebx:%d ecx:%d edx:%d  ',0    