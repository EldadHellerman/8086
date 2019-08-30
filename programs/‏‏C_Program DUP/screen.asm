CPU 8086
BITS 16

global screen_init
global screen_fill
global screen_fill_black
global screen_rect
global screen_image
global screen_letter

%include "font.asm"

%macro delay_ms 1
    push cx
    mov cx, (27*%1)
    %%rel:
    loop %%rel
    pop cx
%endmacro

    %macro write_command 1 ;ch is 0
        mov cl, ((%1 >> 8)&0xff)
        mov word [es:0], cx
        mov cl, (%1&0xff)
        mov word [es:0], cx
    %endmacro

;    %macro write_data 1 ;dh is 1
;        mov dl, ((%1 >> 8)&0xff)
;        mov word [es:0], dx
;        mov dl, (%1&0xff)
;        mov word [es:0], dx
;    %endmacro

%macro write_with_data 2
    mov cl, ((%1 >> 8)&0xff)
    mov word [es:0], cx
    mov cl, (%1&0xff)
    mov word [es:0], cx

    mov dl, ((%2 >> 8)&0xff)
    mov word [es:0], dx
    mov dl, (%2&0xff)
    mov word [es:0], dx
%endmacro

screen_init:
    push es
    mov dx, 0x3000
    mov es, dx
    mov ch, 0 ;command
    mov dh, 1 ;data

    write_with_data 0x0002, 0x0200
    write_with_data 0x0003, 0x1030
;    write_with_data 0x0003, 0x1018
;    write_with_data 0x0004, 0x0000
;    write_with_data 0x0005, 0x0002

    ;----------- Power On sequence ----------- ;
    write_with_data 0x0010, 0x0000
    write_with_data 0x0011, 0x0007
    write_with_data 0x0012, 0x0000
    write_with_data 0x0013, 0x0000
    write_with_data 0x0007, 0x0001
    delay_ms 200

    write_with_data 0x0010, 0x1690
    write_with_data 0x0011, 0x0227
    delay_ms 50

    write_with_data 0x0012, 0x0085
    delay_ms 50

    write_with_data 0x0013, 0x1200
    write_with_data 0x0029, 0x000A
    write_with_data 0x002B, 0x000D
    delay_ms 50

    write_with_data 0x0020, 0x0000
    write_with_data 0x0021, 0x0000

    ;gamma correction:
    write_with_data 0x0030, 0x0000
    write_with_data 0x0031, 0x0404
    write_with_data 0x0032, 0x0003
    write_with_data 0x0035, 0x0405
    write_with_data 0x0036, 0x0808
    write_with_data 0x0037, 0x0407
    write_with_data 0x0038, 0x0303
    write_with_data 0x0039, 0x0707
    write_with_data 0x003C, 0x0504
    write_with_data 0x003D, 0x0808

    write_with_data 0x0060, 0x2700
    write_with_data 0x0061, 0x0001
    write_with_data 0x006A, 0x0000
    write_with_data 0x0080, 0x0000
    write_with_data 0x0081, 0x0000
    write_with_data 0x0082, 0x0000
    write_with_data 0x0083, 0x0000
    write_with_data 0x0084, 0x0000
    write_with_data 0x0085, 0x0000

    write_with_data 0x0090, 0x0010
    write_with_data 0x0092, 0x0000
    write_with_data 0x0007, 0x0133

    pop es
    ret


screen_fill:
    push bp
    mov bp,sp
    push es
    mov dx, 0x3000
    mov es, dx
    mov dh, 1
    mov ch, 0
    write_with_data 0x20, 0
    write_with_data 0x21, 0
    write_with_data 0x50, 0
    write_with_data 0x52, 0
    write_with_data 0x51, 239
    write_with_data 0x53, 319
    write_command 0x22

    mov dh, 1 ;data high
    mov dl, byte [bp+5]
    mov ah, 1 ;data low
    mov al, byte [bp+4]

    mov cx, 240
    screen_fill_draw_x:
        push cx
            mov cx, 320
            screen_fill_draw_y:
                mov word [es:0], dx
                mov word [es:0], ax
                loop screen_fill_draw_y
        pop cx
        loop screen_fill_draw_x
    pop es
    pop bp
    ret


screen_fill_black:
    push bp
    mov bp,sp
    push si
    push di
    push es
    mov dx, 0x3000
    mov es, dx
    mov dh, 1
    mov ch, 0
    write_with_data 0x20, 0
    write_with_data 0x21, 0
    write_with_data 0x50, 0
    write_with_data 0x52, 0
    write_with_data 0x51, 239
    write_with_data 0x53, 319
    write_command 0x22

    cld ;increment in rep movsw
    mov cx, 240
    screen_fill_black_draw_x:
        push cx
            mov cx, 640
            mov si, screen_black
            rep movsw ;Move word at address DS:(E)SI to address ES:(E)DI
        pop cx
        loop screen_fill_black_draw_x
    pop es
    pop di
    pop si
    pop bp
    ret

screen_black:
  times 320 dw 0x0100, 0x0100

%macro write_data_word_from_memory 2 ;memory pointer relative to stack
    mov word [es:0], 0
    mov word [es:0], %1
    mov dl, [bp + %2 + 1]
    mov word [es:0], dx
    mov dl, [bp + %2]
    mov word [es:0], dx
%endmacro

screen_rect:
    push bp
    mov bp,sp
    push es
    push bx
    mov dx, 0x3000
    mov es, dx
    mov dh, 1
    mov ch, 0

    write_data_word_from_memory 0x20, 4   ;sx
    write_data_word_from_memory 0x21, 6   ;sy
    write_data_word_from_memory 0x50, 4   ;sx
    write_data_word_from_memory 0x51, 8   ;ex
    write_data_word_from_memory 0x52, 6   ;sy
    write_data_word_from_memory 0x53, 10  ;ey
    write_command 0x22

    mov dh, 1 ;data high
    mov dl, byte [bp+13]  ;color high
    mov ah, 1 ;data low
    mov al, byte [bp+12]  ;color low

    mov bx, word [bp+10]
    sub bx, word [bp+6]
    add bx, 1

    mov cx, word [bp+8]
    sub cx, word [bp+4]
    add cx, 1
    screen_rect_draw_x:
        push cx
            mov cx, bx
            screen_rect_draw_y:
                mov word [es:0], dx
                mov word [es:0], ax
                loop screen_rect_draw_y
        pop cx
        loop screen_rect_draw_x
    pop bx
    pop es
    pop bp
    ret


screen_image:
    push bp
    mov bp,sp
    push es
    push bx
    mov dx, 0x3000
    mov es, dx
    mov dh, 1
    mov ch, 0

    write_data_word_from_memory 0x20, 4   ;sx
    write_data_word_from_memory 0x21, 6   ;sy
    write_data_word_from_memory 0x50, 4   ;sx
    write_data_word_from_memory 0x51, 8   ;ex
    write_data_word_from_memory 0x52, 6   ;sy
    write_data_word_from_memory 0x53, 10  ;ey
    write_command 0x22

    mov bx, [bp+12] ;pointer to image

    mov ax, word [bp+10]
    sub ax, word [bp+6]
    add ax, 1

    mov cx, word [bp+8]
    sub cx, word [bp+4]
    add cx, 1

    screen_image_draw_x:
        push cx
            mov cx, ax
            screen_image_draw_y:
                mov dl, byte [bx]
                mov word [es:0], dx
                mov dl, byte [bx+1]
                mov word [es:0], dx
                add bx, 2
                loop screen_image_draw_y
        pop cx
        loop screen_image_draw_x
    pop bx
    pop es
    pop bp
    ret


screen_letter:
    push bp
    mov bp,sp
    push es
    push bx
    push si
    mov dx, 0x3000
    mov es, dx
    mov dh, 1
    mov ch, 0

    write_data_word_from_memory 0x20, 4   ;sx
    write_data_word_from_memory 0x50, 4   ;sx
    mov bx, word [bp+4]
    add bx, 7
    write_command 0x51
    mov dl, bh
    mov word [es:0], dx
    mov dl, bl
    mov word [es:0], dx

    write_data_word_from_memory 0x21, 6   ;sy
    write_data_word_from_memory 0x52, 6   ;sy
    mov bx, word [bp+6]
    add bx, 12
    write_command 0x53
    mov dl, bh
    mov word [es:0], dx
    mov dl, bl
    mov word [es:0], dx

    mov dl, byte [bp+8]
    sub dl, ' '
    mov ax, 13
    mul dl
    add ax, letters
    mov bx, ax
    write_command 0x22
    mov si, 13

    mov dh, 1
    letter_draw_line:
        mov cl, byte [bx+si-1]
        mov ch, 0x80 ;mask
        letter_draw_dot:
            test cl, ch
            jz letter_draw_black
            letter_draw_white:
            mov dl, 0xff
            mov word [es:0], dx
            mov dl, 0xff
            mov word [es:0], dx
            jmp letter_continue

            letter_draw_black:
            mov dl, 0x00
            mov word [es:0], dx
            mov dl, 0x00
            mov word [es:0], dx
            jmp letter_continue

            letter_continue:
            shr ch, 1
            jnz letter_draw_dot
        dec si
        jnz letter_draw_line
    pop si
    pop bx
    pop es
    pop bp
    ret
