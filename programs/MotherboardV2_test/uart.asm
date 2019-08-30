uart_write:
    mov byte [es:0000], 0
    mov cl, 2
    for_delay:
    NOP
    NOP
    NOP
    loop for_delay
    mov cl, 1
    write_again:
    test al,cl
    jz write_zero
    mov byte[ds:0000], 0
    nop
    nop
    nop
    nop
    nop
    shl cl, 1
    jnz write_again
    ret

    write_zero:
    mov byte[es:0000], 0
    shl cl, 1
    jnz write_again
    ret

uart_write_char:
    push cx
    mov cx, 0
    push ax
    mov ax, 0x1000
    mov es, ax
    mov ax, 0x2000
    mov ds, ax
    pop ax
    call uart_write
    pop cx
    ret

uart_write_string:
    pop dx ;ret address
    pop bx ;address
;    pop cx ;segment
;    mov ds,cx
    mov si, 0
    write_one_char:
;        mov al, [ds : bx + si]
        mov al, [SS : bx + si]
        cmp al, 0
        je end ;end if null char reached
        mov [SS : 0x950 + si], al
        call uart_write_char
        inc si
        jmp write_one_char
    end:
    push dx ;ret address
    ret

uart_string:
db "this is a sting to send through uart",0