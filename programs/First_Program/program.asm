BITS 16
CPU 8086

section .text

memory_start:
times 32 db 0

start:
    mov cx, 0x20
    again:
        mov bx, cx
        mov ax, cx
        call factorial
        mov [SS:bx-1], al
    loop again
    
    closed_loop:
    HLT
    jmp closed_loop


factorial:
    ;num in al
    ;result is in ax    
    cmp al, 1
    jne not_one
    ret
    not_one:

    push ax
        sub al, 1
        call factorial
    pop bx
 ;   mul bl
    add al, bl
    ret

times 0xff0-$+memory_start db 0x90 ;fill memory until specified address

reset:
mov SP, 0x0
jmp 0x9000:0x0000

times 0x1000-$+memory_start db 0x90 ;fill memory until specified address