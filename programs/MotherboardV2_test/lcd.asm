section .text
global lcd_init
global lcd_print_string
global lcd_clear

%macro delay 0
    push cx
    mov cx, 0x100
    %%rel:
    loop %%rel
    pop cx
%endmacro

lcd_init:
    push es
    mov ax, 0x2000
    mov es, ax
    delay
    delay
    mov word [es:0], 0x0030
    delay
    mov word [es:0], 0x0030
    delay
    mov word [es:0], 0x0030
    delay
    mov word [es:0], 0x0038
    delay

    mov word [es:0], 0x0008 ;;;;;;;;;;
    delay
    mov word [es:0], 0x0001
    delay
    mov word [es:0], 0x0006
    delay
    
    mov word [es:0], 0x000C
    delay

    pop es
    ret

lcd_clear:
    push es
    mov ax, 0x2000
    mov es, ax
    mov word [es:0], 0x0001
    delay
    pop es
    ret

lcd_print_string:
    push bp
    mov bp, sp
    push bx
    push es
    
    mov ax, 0x2000
    mov es, ax
    mov bx, word [SS: bp+4] ;first parameter
    mov ah, 0x01
    lcd_anthor_char:
    mov al, byte [SS:bx]
    cmp al, 0
    je lcd_end_print
    mov word [es:0], ax
    ;delay??
 ;       delay
    delay
    delay
    delay
    delay
    inc bx
    jmp lcd_anthor_char
    lcd_end_print:
    delay
    delay
    delay
    delay
    delay
    delay
    delay
    pop es
    pop bx
    pop bp
    ret

%macro lcd_set_cursor 2
    push es
    mov ax, 0x2000
    mov es, ax
    mov word [es:0], (0x0080 | (%1<<6) | %2)
    delay
    pop es
%endmacro

%macro send_char 1
    push es
    push ax
    mov ax, 0x2000
    mov es, ax
    pop ax
    mov ah, 0x01
    mov al, %1
    mov word [es:0], ax
    pop es
%endmacro







;;;;;;;;;;;;;;;;;;;;   example code   ;;;;;;;;;;;;;;
; it worked for me for about the first 5 seconds and then there were problams

;    call lcd_init
;    delay_ms 100
;    
;    code_again:
;    mov ax, str_welcome
;    push ax
;    call lcd_print_string
;    delay_ms 10
;    pop ax
;    
;    delay_ms 1000
;    call lcd_clear
;    delay_ms 10
;    delay_ms 500
;    ;jmp code_again
;    
;    ;delay_ms 2000
;    mov ax, lcd_str_2
;    push ax
;    call lcd_print_string
;    delay_ms 10
;    pop ax
;    mov cx, 5
;    countdown:
;        lcd_set_cursor 1,0
;        delay_ms 10
;        mov al, cl
;        or al, 0x30
;        send_char al
;        delay_ms 1000
;    loop countdown
;    call lcd_clear
;    delay_ms 50
;    jmp code_again





;   hlt_loop:
;    
;     ;   int 4
;        call print_string
;        delay_ms 1500
;    ;    int 2
;        call lcd_clear
;        delay_ms 500
;    ;    mov [0xaf0], ax
;        inc word [SS: 0x1f00]
;        jmp hlt_loop
;    
;    print_string:
;        push ax
;        ;lcd_set_cursor 0, 0
;        ;delay_ms 10
;        mov ax, string_1
;        push ax
;        call lcd_print_string
;        delay_ms 10
;        pop ax
;        pop ax
;        ret
;    
;    string_1:
;    db 'Test String!',0



;    push ds
;    mov di, 0x100 ;memory start
;    mov ax, 0 ;memory segment
;    mov es, ax
;    mov si, 0 ;message start
;    mov ax, 0x1000 ;message segment
;    mov ds, ax
;    mov cx, 30 ;message length
;    REP MOVSB ;moves cx bytes from ds:si to es:di
;    pop ds
;
;    mov ax, 0x1000
;    mov es, ax
;    mov word [es:0x1234], 0x5678
;;    mov cx, 0x100
; ;   del_2: loop del_2
;    mov word [es:0x1110], 0x1234
;    mov word [es:0x2220], 0x2345
;    mov word [es:0x3330], 0x3456
;    mov word [es:0x4440], 0x4567
;    mov word [es:0x5550], 0x890a
;    mov word [es:0x6660], 0x90ab
;    mov word [es:0x7770], 0x0abc
;    mov word [es:0x8880], 0xabcd
;    mov word [es:0x9990], 0xbcde
;    mov word [es:0x0000], 0xcdef



;    mov ax, str_welcome
;    push ax
;    call write_uart_string



;    call lcd_clear
;    delay_ms 10



;show_register:
;    push bx
;    jmp next
;    cell:
;    db '0000',0
;    next:
;    mov bx, ax
;    and bl, 0x0f
;    or bl, 0x30
;    mov [SS:cell+3], bl
;    mov bx, ax
;    and bx, 0xf0
;    shr bx, 1
;    shr bx, 1
;    shr bx, 1
;    shr bx, 1
;    or bx, 0x30
;    mov [SS:cell+2], bl
;    mov bx, ax
;    and bh, 0x0f
;    or bh, 0x30
;    mov [SS:cell+1], bh
;    mov bx, ax
;    and bh, 0xf0
;    shr bh, 1
;    shr bh, 1
;    shr bh, 1
;    shr bh, 1
;    or bh, 0x30
;    mov [SS:cell+0], bh
;    mov ax, cell
;    push ax
;    call lcd_print_string
;    delay_ms 10
;    pop ax
;    pop bx
;    ret



;    mov ax, 0x1234
;    mov bx, 0x3456
;    mov cx, 0x5678
;    mov dx, 0x7890
;    
;    lcd_set_cursor 0, 0
;    mov ax,ax
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 0, 8
;    mov ax,bx
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 1, 0
;    mov ax,cx
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 1, 8
;    mov ax,dx
;    call show_register
;        delay_ms 100
;    IRET
;    
;    lcd_set_cursor 0, 7
;    mov ax, lcd_str
;    call lcd_print_string
;    lcd_set_cursor 1, 0    
;    mov ax, lcd_str_2
;    call lcd_print_string



;    mov ax, 0x1234
;    mov bx, 0x3456
;    mov cx, 0x5678
;    mov dx, 0x7890
;    
;    lcd_set_cursor 0, 0
;    mov ax,ax
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 0, 8
;    mov ax,bx
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 1, 0
;    mov ax,cx
;    call show_register
;        delay_ms 100
;    lcd_set_cursor 1, 8
;    mov ax,dx
;    call show_register
;        delay_ms 100
;    IRET
;    
;    lcd_set_cursor 0, 7
;    mov ax, lcd_str
;    call lcd_print_string
;    lcd_set_cursor 1, 0    
;    mov ax, lcd_str_2
;    call lcd_print_string



