[org 0x9000]          ; tell NASM where this code will live in memory

jmp main
 
main:
    mov bx, KERNEL_MSG
    call print_string_kernel
    jmp $

print_string_kernel:  ; print function
    mov ah, 0x0e
.loop:
    mov al, [bx]
    cmp al, 0
    je .done
    int 0x10
    inc bx 
    jmp .loop
.done: 
    ret
 
KERNEL_MSG: db "Successfully landed in the Kernel!", 0
