OUTPUT_FORMAT("binary")
OUTPUT_ARCH(i8086)
ENTRY(c_runtime_start)
INPUT("Debug\C_runtime.o")

SECTIONS{
  .ivt    : { *C_runtime.o(.IVT .start)}
  .start  : { *(.start) }
  .text   : { *(.text .text.* ) }
  .rodata : { *(.rodata .rodata.* .rodata1 .rodata1.*) }
  .data   : { *(.data .data.* .data1 .data1.*) }
  . = .;
  __bss_start = .;
  .bss : {
   *(.bss .bss.*)
  }
	. = .;
  _end = .;
  PROVIDE (end = .);
  /DISCARD/ : { *(.*)}
}
