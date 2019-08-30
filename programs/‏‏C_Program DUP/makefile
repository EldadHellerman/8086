all: program.bin

C_runtime.o: C_runtime.asm
	nasm C_runtime.asm -o Debug\C_runtime.o -felf32

screen.o: screen.asm
	nasm screen.asm -o Debug\screen.o -felf32

program.bin: program.c C_runtime.o screen.o
	ia16-elf-gcc program.c Debug\screen.o -o Debug\program.bin -T 8086.ld -O1

dis: program.bin
	ia16-elf-objdump Debug\program.bin -D -b binary -M intel -mi8086 -z --start-address=0x400
