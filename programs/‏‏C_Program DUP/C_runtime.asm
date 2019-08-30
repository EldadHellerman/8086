CPU 8086
BITS 16

section .IVT
interrupt_table_start:
times 256 db 0x00, 0x04, 0x00, 0x00
interrupt_table_end:


extern main
global c_runtime_start
section .start
c_runtime_start:
call main
end_loop:
HLT
  jmp end_loop

;define standard funstions such as strcmp, malloc, printf, screenIO, delay, etc...
;create a file in c as well -"C_runtime.c"
