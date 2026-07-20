.set noreorder
.set noat

.section .text.start
.globl _start
.type  _start, @function

_start:
    la      $gp, _gp            # set GP — required by PS2SDK libs
    la      $sp, _stack_end     # high end of stack (grows downward)

    # Preserve argc/argv in callee-saved regs — survive BSS clear
    move    $s0, $a0
    move    $s1, $a1

    # Clear BSS — 16 bytes at a time with sq (PS2 quadword store)
    la      $t0, _fbss
    la      $t1, _end
1:
    sltu    $at, $t0, $t1
    beqz    $at, 2f
    nop
    sq      $zero, 0($t0)
    addiu   $t0, $t0, 16
    j       1b
    nop
2:
    # Restore argc/argv and call main
    move    $a0, $s0
    move    $a1, $s1
    jal     main
    nop
3:
    b       3b
    nop
