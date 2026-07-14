OUTPUT_FORMAT("elf32-littlemips", "elf32-littlemips", "elf32-littlemips")
OUTPUT_ARCH(mips)
ENTRY(_start)
SECTIONS
{
  . = 0x01D00000;   /* fixed load address, inside your reserved top ~2MB */

  .text : { *(.text) *(.text.*) }
  .rodata : { *(.rodata) *(.rodata.*) }
  .data : { *(.data) *(.data.*) }
  .bss  : { *(.bss)  *(.bss.*) }
  _end = .;
}
