[bits 32] ; Tell NASM this is 32-bit code

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; Set EDX to the start of video memory

print_string_pm_loop:
    mov al, [ebx]          ; Store the char at EBX in AL
    mov ah, WHITE_ON_BLACK ; Store the attributes in AH

    cmp al, 0
    je print_string_pm_done

    mov [edx], ax          ; Store char and attributes at current character cell
    add ebx, 1             ; Increment EBX to the next char in string
    add edx, 2             ; Move to next character cell in video memory

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret
