;DS, ES, CS, SS
;at location 0xffff0:
jmp 0xf000:start

start:
mov ax, 0x1000 ;input segment
mov ES, ax
mov ax, 0x0000 ;memory segment
mov DS, ax
mov bx, 0x0000

write_loop:
    sub bx, 2
    wait
    mov al, byte [ES:0] ;even address
    wait
    mov ah, byte [ES:0] ;even address
    mov [DS:bx], ax
    jmp write_loop