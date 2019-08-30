times 0xff0-$+memory_start db 0x90 ;fill memory until specified address

reset:
mov SP, 0x100
jmp 0:start

times 0x1000-$+memory_start db 0x90 ;fill memory until specified address