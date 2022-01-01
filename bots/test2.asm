.section .bot #0x402000 #0x100 rwx
_start:
    mov $r1, #0x1337000
    rjmp main

main:
    mov $r0, [$r1]
    mov [$r1], $r1
    add $r1, #4
    cmp $r1, #0x1337400
    cmovae $r1, #0x1337000
    rjmp main
