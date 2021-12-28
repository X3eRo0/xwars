.section .bot #0x402000 #0x100 rwx
_start:
    mov $r0, $pc
    mov $r1, [$r0+0x5]
    mov $r2, [$r0+0x5]
    rjmp _start
