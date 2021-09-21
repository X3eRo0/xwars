.section .init 0x401000 0x100 r-x
_start:
    ret

.section .bot 0x402000 0x100 r-x
    lea $r1, [$pc+#0x36]
    lea $r0, [$pc+#0x8]
    mov $r2, [$r1]
	inc $r1
    cmp $r2, #0x00000000
    jz $r0
    mov [$r1], #0xffffffff
    jmp $r0
