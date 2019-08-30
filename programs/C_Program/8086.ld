OUTPUT_FORMAT("binary")
OUTPUT_ARCH(i8086)
ENTRY(c_runtime_start)
INPUT("Debug\C_runtime.o")

MEMORY{
  ram (RWX) : org = 0, len = 64K
  rom (RX!W) : org = 0x80000, len = 512K
  }

SECTIONS{
  .ivt 0xc000   : { *C_runtime.o(.IVT .start)}
  .start  : { *(.start) }
  .text   : { *(.text .text.* ) }
  .rodata : { *(.rodata .rodata.* .rodata1 .rodata1.*) }
  .data   : { *(.data .data.* .data1 .data1.*) }
  . = .;
  __bss_start = .;
  .bss    : { *(.bss .bss.*) }
	. = .;
  . = 0xfff0;
  .boot   : { *(.boot)}
  _end = .;
  PROVIDE (end = .);
  /DISCARD/ : { *(.*)}
}
