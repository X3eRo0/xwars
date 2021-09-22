.section .init 0x401000 0x100 r-x
_start:
    ret

.section .bot 0x402000 0x100 r-x
; size = 0x400

bot_start:
    lea $r9, [$pc]
    lea $ra, [$r9+#0x92]
    mov $rb, $r9
    and $rb, #0xfffff000
    lea $rc, [$rb+#0x400]

    lea $r1, [$rb+#0x200]
    mov $r2, $r1

    mov $r5, #0x0

start_loop:
    inc $r5
    cmp $r5, #0x200
    rjz exit_loop
    lea $r1, [$r1+#0x08]
    lea $r2, [$r2-#0x08]
    cmp [$r1], #0x00
    rjnz patch_instruction1
    cmp [$r2], #0x00
    rjnz patch_instruction2
    rjmp start_loop

patch_instruction1:
    mov [$r1], #0xffffffff
    rjmp start_loop

patch_instruction2:
    mov [$r2], #0xffffffff
    rjmp start_loop

exit_loop:
    rjmp bot_start
