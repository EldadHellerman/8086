%macro register_interrupt 3
;interrupt_number, function_adress, function_segment
    mov word [SS:%1*4], %2
    mov word [SS:%1*4 + 2], %3
%endmacro

%macro delay_ms 1
    push cx
    mov cx, (25*%1)
    %%rel:
    loop %%rel
    pop cx
%endmacro

%macro delay_s 1
    push cx
    mov cx, %1*5
    %%rel:
    delay_ms 1000
    loop %%rel
    pop cx
%endmacro

%macro pushw 1
    mov ax, %1
    push ax
%endmacro