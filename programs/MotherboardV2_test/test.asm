BITS 16
CPU 8086
section .text
memory_start:

%include "interrupt_jmp_table.asm"
jmp start

%include "RGB_LCD.asm"
%include "macros.asm"
;%include "lcd.asm"

screen_string:
db "Hello! this string will print on lcd!",0
screen_string_2:
db "ABCDEFGHIJKLMNOPQRSTUVWXYZ",0

start:
call rgblcd_init
mov dx, BLACK
call rgblcd_fill_screen
delay_ms 100
draw_string str_welcome, 0, 0
delay_s 1
draw_string str_welcome_2, 0, 20
draw_string str_welcome_3, 0, 40
delay_s 5

screen_again:
;    mov dx, BLACK
;    call rgblcd_fill_screen

;    draw_letter 'o', 0, 0
;    draw_letter 'g', 20, 0
;    draw_string screen_string, 0, 0
;    draw_string screen_string_2, 0, 100
;    delay_s 2

;    mov dx, RED
;    call rgblcd_fill_screen
;
;    draw_rect BLUE, 100, 100, 150, 150
;    delay_s 2
;
;    mov dx, GREEN
;    call rgblcd_fill_screen
;    draw_rect BLACK, 0, 100, 240, 150
;    delay_s 2
;
;    mov dx, BLUE
;    call rgblcd_fill_screen
;    draw_rect BLACK, 100, 0, 140, 320
;    delay_s 2

    mov dx, BLACK
    call rgblcd_fill_screen
    mov cx, 0
    animation:
        mov dx, RED
        mov ax, cx
        push ax
        push ax
        add ax, 10
        push ax
        push ax
        call rgblcd_draw_rect
        mov dx, BLACK
        delay_ms 500
        call rgblcd_draw_rect
        add cx, 2
        cmp cx, 200
        jne animation

    mov cx, 0
    animation_2:
        mov dx, RED
        mov ax, cx
        push ax
        push ax
        add ax, 10
        push ax
        push ax
        call rgblcd_draw_rect
        mov dx, BLACK
        delay_ms 500

        add sp,4
        mov ax, cx
        add ax, 2
        push ax
        add ax, 8
        push ax
        call rgblcd_draw_rect

        add sp,4
        mov ax, cx
        add ax, 10
        push ax
        sub ax, 8
        push ax
        call rgblcd_draw_rect

        add cx, 2
        cmp cx, 200
        jne animation_2

    jmp screen_again

test_end:
HLT
jmp test_end

register_interrupt 0, interrupt_0, 0
;STI
;cli

interrupt_0:
    IRET

str_welcome:
db 'Welcome!',0
str_welcome_2:
db '8086 Computer',0
str_welcome_3:
db 'EH',0

;times 0x1500-$+memory_start db 0x90 ;fill memory until specified address
;db 'this is where the string should go'
times 0x1ff0-$+memory_start db 0x90 ;fill memory until specified address

reset:
mov SP, 0x0
jmp 0x0000:0x0400 ;end of interrupt table

times 0x2000-$+memory_start db 0x90 ;fill memory until specified address
