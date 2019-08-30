BITS 16
CPU 8086
section .text

%MACRO pushw 1
    mov ax, %1
    push ax
%ENDMACRO

memory_start:
times 0x50 db 0


start:
NOP
NOP
NOP
NOP
mov ax, 0x1234
out 20, ax
jmp 0:jump

jump:
NOP
NOP

HLT

mov sp, 0x0350

;multiply 0x1234 with 0x5678 (=0x06260060)
pushw 0x1234
pushw 0x5678
call multiply_16
pop WORD [0]
pop WORD [2]

jmp skip
    ;multiply 0x12345678 with 0x23456789 (=0x282174A83248E38)
    pushw 0x1234
    pushw 0x5678
    pushw 0x2345
    pushw 0x6789
    call multiply_32
    pop WORD [10h]
    pop WORD [12h]
    pop WORD [14h]
    pop WORD [16h]

skip:
;multiply 0x12345678 with 0x23456789 (=0x282174A83248E38)
pushw 0x1234
pushw 0x5678
pushw 0x2345
pushw 0x6789
call multiply_32_2
pop WORD [20h]
pop WORD [22h]
pop WORD [24h]
pop WORD [26h]


end:
    pushw 0x0000
    HLT
    jmp end

multiply_16:
;take 2 16bit numbers on the stack
;returns 32bit result on the stack
    mov bx, bp
    mov bp, sp
    mov ax, word [bp+2]
    mul word [bp+4]
    mov [bp+2], ax
    mov [bp+4], dx
    mov bp, bx
    ret

multiply_32_2:
    mov bp, sp
    ;less efficient because calling multiply_16
    ;bp      -> return addres
    ;bp+2    -> num1_low   /  result_4_low
    ;bp+4    -> num1_high  /  result_3
    ;bp+6    -> num2_low   /  result_2
    ;bp+8    -> num2_high  /  result_1_HIGH
    push word [bp+4]
    push word [bp+8]
    call multiply_16
    push word [bp+2]
    push word [bp+8]
    call multiply_16
    push word [bp+4]
    push word [bp+6]
    call multiply_16
    push word [bp+2]
    push word [bp+6]
    call multiply_16
    mov [bp+8], word 0
    pop word [bp+2]
    pop word [bp+4]
    ;pop high word of answer here, so that it is in carry calculations earlyer
    pop ax
    pop word [bp+6]
    pop bx
    pop cx
    add word [bp+4], ax
    adc word [bp+6], 0
    adc word [bp+8], 0
    add word [bp+4], bx
    adc word [bp+6], 0
    adc word [bp+8], 0
    add word [bp+6], cx
    adc word [bp+8], 0
    pop ax
    pop bx
    add word [bp+6], ax
    adc word [bp+8], 0
    add word [bp+8], bx
    ret
    

multiply_32:
    mov bp, sp
    ;currently does not support interrupts - will ruin the stack
    ;maybe subtract from sp here by amount needed
    
    ;sp    -> return address
    ;sp+2  -> first num low
    ;sp+4  -> first num high
    ;sp+6  -> second num low
    ;sp+8  -> second num high
    ;sp-2  -> answer low
    ;sp-4  -> answer right 1
    ;sp-6  -> answer right 2
    ;sp-8  -> answer right 3
    ;sp-10 -> answer left 1
    ;sp-12 -> answer left 2
    ;sp-14 -> answer left 3
    ;sp-16 -> answer HIGH
    mov ax, [bp+2]
    mov bx, [bp+6]
    mul bx
    mov [bp-2], ax
    mov [bp-4], dx
    
    mov ax, [bp+4]
    mul bx
    mov [bp-6], ax
    mov [bp-10], dx
    
    mov bx, [bp+8]
    mov ax, [bp+2]
    mul bx
    mov [bp-8], ax
    mov [bp-12], dx
    
    mov ax, [bp+4]
    mul bx
    mov [bp-14], ax
    mov [bp-16], dx ;gets discarded
    
    POP DX; return address
    push WORD [bp-2]
    mov ax, [bp-4]  ;it ignores
    add ax, [bp-6]  ;carry!!!
    add ax, [bp-8]  ;fix it!!!!
    push ax
    
    mov ax, [bp-10]  ;it ignores
    add ax, [bp-12]  ;carry!!!
    add ax, [bp-14]  ;fix it!!!!
    push ax
    
    push WORD [bp-16]
;    sub sp, 16
    push DX ;return address
    ret
  
%include "reset.inc"
