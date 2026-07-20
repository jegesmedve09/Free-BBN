OUTPUT_FORMAT("elf32-littlemips")
OUTPUT_ARCH(mips)
ENTRY(_start)

SECTIONS
{
    . = 0x01F00000;

    /* GP base — must be defined for PS2SDK libs */
    _gp = . + 0x7FF0;

    .text : {
        *(.text.start)   /* crt0 _start goes first */
        *(.text*)
    }

    .rodata : { *(.rodata*) }

    .data : { *(.data*) }

    /* _fbss = start of zero-init region (BSS clear loop uses this) */
    _fbss = ALIGN(16);

    .bss : {
        *(.bss*)
        *(COMMON)
    }

    /* _end = first address past BSS (required by libcglue _sbrk) */
    _end = ALIGN(16);

    /* Private stack — 16 KB */
    _stack_start = _end;
    _stack_end   = _end + 0x4000;

    /* Ensure we fit in 1 MB */
    . = 0x01F00000 + 0x100000;
    ASSERT(_stack_end <= 0x01F00000 + 0x100000, "Loader exceeds 1 MB!")
}
