[org 0x7c00]

mov ah, 0x0e

mov al, 'A'
int 0x10
mov al, 'R'
int 0x10
mov al, 'S'
int 0x10
mov al, 'H'
int 0x10
mov al, 'A'
int 0x10
mov al, 'N'
int 0x10

jmp $

times 510-($-$$) db 0
dw 0xaa55




[org 0x7c00]

mov si, message

print:
    lodsb
    cmp al, 0
    je done
    mov ah, 0x0e
    int 0x10
    jmp print

done:
    jmp $

message db "Hello, this is Arshan's OS!", 0

times 510-($-$$) db 0
dw 0xaa55

