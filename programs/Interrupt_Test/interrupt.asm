BITS 16
CPU 8086

section .text

memory_start:

dw 0x0040,0x0000
dw 0x0044,0x0000
dw 0x0048,0x0000
dw 0x004c,0x0000
dw 0x0050,0x0000
dw 0x0054,0x0000
dw 0x0058,0x0000
dw 0x005c,0x0000
dw 0x0060,0x0000
dw 0x0064,0x0000
dw 0x0068,0x0000
dw 0x006c,0x0000
dw 0x0070,0x0000
dw 0x0074,0x0000
dw 0x0078,0x0000
dw 0x007c,0x0000


mov ax, 'i1'
IRET
mov ax, 'i2'
IRET
mov ax, 'i3'
IRET
mov ax, 'i4'
IRET
mov ax, 'i5'
IRET
mov ax, 'i6'
IRET
mov ax, 'i7'
IRET
mov ax, 'i8'
IRET
mov ax, 'i9'
IRET
mov ax, 'ia'
IRET
mov ax, 'ib'
IRET
mov ax, 'ic'
IRET
mov ax, 'id'
IRET
mov ax, 'ie'
IRET
mov ax, 'if'
IRET
mov ax, 'i0'
IRET

start:
STI
hlt_loop:
    HLT
    mov [0x100], ax
    jmp hlt_loop



times 0xff0-$+memory_start db 0x90 ;fill memory until specified address

reset:
mov SP, 0x100
jmp 0:start

times 0x1000-$+memory_start db 0x90 ;fill memory until specified address