.section .bot #0x402000 #0x100 rwx

_start:
    mov $r0, #0x1337900
    mov $sp, $r0
    mov $rc, #0x0f0e1100
    mov $rb, #0x003c003c
    mov $ra, $rb
    mov $r9, $rb
    mov $r8, $rb
    mov $r7, #0xef0f0146
    dec $r6
    dec $r5
    dec $r4
    dec $r3
    dec $r2
    dec $r1
    ; 00 11 0e 0f
    ; 3c 00 3c 00
    ; 3c 00 3c 00
    ; 42 21 0f 20
    ; 00 00 00 18
    ; 11 0f 00 46
    ; 01 0f ef 00
botloop:
    nop
    mov $bp, $sp
    pusha
    pusha
    pusha
    pusha
    pusha
    pusha
    pusha
    pusha
    jmp $sp 
