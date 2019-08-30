    mov CX, message_end-message
    mov ax, 0 ;seg message
    mov DS, ax
    mov SI, message
    mov AX, 0 ;seg memory_start
    mov ES, AX
    mov DI, memory_start
    REP MOVSB ;moves cx bytes from ds:si to es:di


    mov ax, 0
    mov bx, 0x1234
    push bx
    mov bx, 0x2345
    push bx
    call function_add
    pop ax
    mov [14], ax
    mov bl, 0x67
    div bl
    mov [12], ax
    
    mov cx, 10
    counter:
        mov bx,cx
        mov[bx + 0x10], cl
    loop counter
    
    cmp cx, 0
    je is_zero
    mov [0x1a], BYTE 0x11    
    jmp next
    is_zero:
    mov [0x1b], BYTE 0x22
    jmp next
    
    mov [0x1c], BYTE 0x33
    next:
    
    mov cx, 5
    cmp cx, 0
    je is_zero_2
    mov [0x1d], BYTE 0x11    
    jmp next_2
    is_zero_2:
    mov [0x1e], BYTE 0x22
    next_2:
    
    mov CX, 0x1234
    push CX
    mov CX, 0x5678
    push CX
    pop AX
    mov CX, 0x9abc
    push CX
    mov [14], AX

function_add:
    pop CX
    pop ax
    pop bx
    add ax,bx
    push ax
    push CX
    ret

message:
DB "eldad's 8086"
message_end: