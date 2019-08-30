#include "screen.h"

void delay_ms(int ms){
  //%macro lcd_delay_ms 1    push cx    mov cx, (27*%1)    %%rel:    loop %%rel    pop cx  %endmacro
  for(int i=0; i<ms; i++);
}

unsigned int init_seq[][2] =   {{0x0002, 0x0200}, {0x0003, 0x1030},
                          {0x0010, 0x0000}, {0x0011, 0x0007}, {0x0012, 0x0000}, {0x0013, 0x0000}, {0x0007, 0x0001}, //Power On sequence
                          {0x0000, 200},
                          {0x0010, 0x1690}, {0x0011, 0x0227},
                          {0x0000, 50},
                          {0x0012, 0x0085},
                          {0x0000, 50},
                          {0x0013, 0x1200},{0x0029, 0x000A},{0x002B, 0x000D},{0x0000, 50},
                          {0x0020, 0x0000}, {0x0021, 0x0000},
                          {0x0030, 0x0000},{0x0031, 0x0404},{0x0032, 0x0003},{0x0035, 0x0405},{0x0036, 0x0808},{0x0037, 0x0407},{0x0038, 0x0303},{0x0039, 0x0707},{0x003C, 0x0504},{0x003D, 0x0808}, //gamma correction
                          {0x0060, 0x2700},{0x0061, 0x0001},{0x006A, 0x0000},{0x0080, 0x0000},{0x0081, 0x0000},{0x0082, 0x0000},{0x0083, 0x0000},{0x0084, 0x0000},{0x0085, 0x0000},
                          {0x0090, 0x0010},{0x0092, 0x0000},{0x0007, 0x0133}};
void lcd_init(){
  for(int i=0; i<sizeof(init_seq); i++){
    if(init_seq[i][0] == 0) delay_ms(init_seq[i][1]);
    else{
      //write_with_data(init_seq[i][0],init_seq[i][1]);
      asm volatile(
        "mov bx, 0x3000\n\t"
        "mov es, bx\n\t"
      "    mov ch, 0\n\t"
      "    mov cl, %0\n\t"
      "    mov word [es:0], cx\n\t"
      "    mov cl, %1\n\t"
      "    mov word [es:0], cx\n\t"

      "    mov ch, 1\n\t"
      "    mov cl, %2\n\t"
      "    mov word [es:0], cx\n\t"
      "    mov cl, %3\n\t"
      "    mov word [es:0], cx\n\t"
      :
      : "r" (init_seq[i][0]>>8), "r" (init_seq[i][0]&0xff), "r" (init_seq[i][1]>>8), "r" (init_seq[i][1]&0xff)
      : "bx","cx","es"
      );
    }
  }
}

/*void lcd_fill(int color){
  asm volatile(
    "%macro write_data_or_command 2\n\t"
    "    mov ch, %1 ;rs 1 if data\n\t"
    "    mov cl, ((%2 >> 8)&0xff)\n\t"
    "    mov word [es:0], cx\n\t"
    "    mov cl, (%2&0xff)\n\t"
    "    mov word [es:0], cx\n\t"
    "%endmacro\n\t"
    "\n\t"
    "%macro write_with_data 2 ;parameter is 0 if command, 1 if data\n\t"
    "    write_data_or_command 0, %1\n\t"
    "    write_data_or_command 1, %2\n\t"
    "%endmacro\n\t"
    "push es\n\t"
    "push bx\n\t"
    "push cx\n\t"
    "mov bx, 0x3000\n\t"
    "mov es, bx\n\t"

    "mov dx, 0xf800\n\t"

    "write_with_data 0x20, 0\n\t"
    "write_with_data 0x21, 0\n\t"
    "write_with_data 0x50, 0\n\t"
    "write_with_data 0x52, 0\n\t"
    "write_with_data 0x51, 239\n\t"
    "write_with_data 0x53, 319\n\t"
    "\n\t"
    "write_data_or_command 0, 0x22\n\t"
    "mov cx, 240\n\t"
    "draw_x:\n\t"
    "    push cx\n\t"
    "        mov cx, 320\n\t"
    "        draw_y:\n\t"
    "        ;mov bx, cx\n\t"
    "            mov bh, 1\n\t"
    ";                write_data_or_command 1, 0x001F ;blue color\n\t"
    ";                write_data_or_command 1, 0xf800\n\t"
    "            mov bl, dh\n\t"
    "            mov word [es:0], bx\n\t"
    "            mov bl, dl\n\t"
    "            mov word [es:0], bx\n\t"
    "           ;mov cx, bx\n\t"
    "            loop draw_y\n\t"
    "    pop cx\n\t"
    "    loop draw_x\n\t"
    "\n\t"
    "pop cx\n\t"
    "pop bx\n\t"
    "pop es\n\t"
    :
    :
    :"ax","bx","cx","dx","es"
  );
}*/

/*
write_command:
    ;command at ax
    push es
    push bx
    push cx
    mov bx, 0x3000
    mov es, bx

    mov ch, 0 ;rs set to data
    mov cl, ah
    mov word [es:0], cx
    mov cl, al
    mov word [es:0], cx
    pop cx
    pop bx
    pop es
    ret

write_data:
    ;parameter at ax
    push es
    push bx
    push cx
    mov bx, 0x3000
    mov es, bx

    mov ch, 1 ;rs set to data
    mov cl, ah
    mov word [es:0], cx
    mov cl, al
    mov word [es:0], cx
    pop cx
    pop bx
    pop es
    ret

%macro write_data_or_command 2
    mov ch, %1 ;rs 1 if data
    mov cl, ((%2 >> 8)&0xff)
    mov word [es:0], cx
    mov cl, (%2&0xff)
    mov word [es:0], cx
%endmacro

%macro write_data_word 2
    mov ch, 1 ;rs 1 if data
    mov cl, %1
    mov word [es:0], cx
    mov cl, %2
    mov word [es:0], cx
%endmacro

%macro write_with_data 2 ;parameter is 0 if command, 1 if data
    write_data_or_command 0, %1
    write_data_or_command 1, %2
%endmacro
*/



/*
    void lcd_rect(int sx, int sy, int w, int h);
    void lcd_draw_letter(char c, int x, int y);
    void lcd_draw_string(char *str, int x, int y);



    rgblcd_draw_rect:
        push bp
        mov bp,sp
        push es
        push dx
        push cx
        push bx
        push ax
        mov bx, 0x3000
        mov es, bx
        ;bp relative list:
        ;bp+10  ->   start x
        ;bp+8   ->   start Y
        ;bp+6   ->   end x
        ;bp+4   ->   end y

        write_data_or_command 0,0x20
        write_data_word byte [bp+11] , byte [bp+10]

        write_data_or_command 0,0x50
        write_data_word byte [bp+11] , byte [bp+10]

        write_data_or_command 0,0x51
        write_data_word byte [bp+7] , byte [bp+6]

        write_data_or_command 0,0x21
        write_data_word byte [bp+9] , byte [bp+8]

        write_data_or_command 0,0x52
        write_data_word byte [bp+9] , byte [bp+8]

        write_data_or_command 0,0x53
        write_data_word byte [bp+5] , byte [bp+4]

        write_data_or_command 0, 0x22
        mov cx, word [bp+6]
        sub cx, word [bp+10]
        add cx, 1
        mov ax, word [bp+4]
        sub ax, word [bp+8]
        add ax, 1
        push cx ;bp-12
    ;    mov [bp-12], cx

        mov bh, 1
        rect_draw_x:
            mov cx, ax
            rect_draw_y:
                mov bl, dh
                mov word [es:0], bx
                mov bl, dl
                mov word [es:0], bx
                dec cx
                jnz rect_draw_y
            dec word [bp-12]
            jnz rect_draw_x

        pop cx
        pop ax
        pop bx
        pop cx
        pop dx
        pop es
        pop bp
        ret





        rgblcd_draw_letter:
            push bp
            mov bp,sp
            push es
            push dx
            push cx
            push bx
            push ax
            mov bx, 0x3000
            mov es, bx
            ;bp relative list:
            ;bp+6   ->   start x
            ;bp+4   ->   start Y

            ;dl   ->   letter

            write_data_or_command 0,0x20
            write_data_word byte [bp+7] , byte [bp+6]

            write_data_or_command 0,0x50
            write_data_word byte [bp+7] , byte [bp+6]

            write_data_or_command 0,0x51
            mov bx, word [bp+6]
            add bx, 7
         ;   add bx, 12
            write_data_word bh, bl

            write_data_or_command 0,0x21
            write_data_word byte [bp+5] , byte [bp+4]
            write_data_or_command 0,0x52
            write_data_word byte [bp+5] , byte [bp+4]

            write_data_or_command 0,0x53
            mov bx, word [bp+4]
         ;   add bx, 7
            add bx, 12
            write_data_word bh, bl

            mov ax, 13
            sub dl, ' '
            mul dl
            add ax, letters
            mov bx, ax
            write_data_or_command 0, 0x22
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

            pop ax
            pop bx
            pop cx
            pop dx
            pop es
            pop bp
            ret








            rgblcd_draw_string:
                push bp
                mov bp,sp
                push cx
                push bx
                ;bp relative list:
                ;bp+6   ->   start x
                ;bp+4   ->   start Y
                ;di     ->   string pointer
                mov bx, [bp+6]
                mov cx, [bp+4]
                mov ax, 0
                draw_another_letter:
                    mov dl, byte [ds:di]
                    cmp dl, 0
                    je draw_string_end
                    push bx
                    push cx
                    call rgblcd_draw_letter
                    add sp, 4

                    inc di
                    add bx, 13
                    cmp bx, 227
                    jle no_new_line
                        add cx, 15
                        mov bx, 0
                    no_new_line:
                    jmp draw_another_letter
                draw_string_end:
                pop bx
                pop cx
                pop bp
                ret
  */
