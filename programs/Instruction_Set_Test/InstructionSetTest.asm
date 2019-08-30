BITS 16
CPU 8086

section .text

memory_start:

times 32 db 0
start:

;;;;;;;;;;   AAA    ;;;;;;;;;;
;mov ax, 0
;mov al, 0xf1
;mov bl,al
;mov al, 0xF2
;add al,bl
;aaa
;push ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;   NEG    ;;;;;;;;;;
;mov [0], word 300
;neg WORD [0]
;mov [2], byte -128
;mov [3], byte 0
;mov [4], byte 127
;neg BYTE [2]
;neg BYTE [3]
;neg BYTE [4]
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;   XLAT   ;;;;;;;;;;
;jmp xlat_start
;table:
;db "this is a table used for translating from table!"
;xlat_start:
;mov cx, 16
;text_loop:
;    mov al, cl
;    mov bx, table
;    xlat
;    mov bx, cx
;    mov [bx], al
;    loop text_loop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;   XCHG   ;;;;;;;;;;
;mov [0], word 0x1234
;mov ax, 0x5678
;xchg [0],ax
;mov [2],ax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

hlt_loop:
    HLT
    jmp hlt_loop

%include "reset.inc"
;times 0xff0-$+memory_start db 0x90 ;fill memory until specified address
;reset:
;mov SP, 0x100
;jmp 0:start
;times 0x1000-$+memory_start db 0x90 ;fill memory until specified address