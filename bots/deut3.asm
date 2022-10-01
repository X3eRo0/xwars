

.section .bot #0x402000 #0x100 rwx

;r0-r9 ra rb rc sp bp pc
;lea source destination

; 1337000 - 13373ff
; 0x00 illegal, 0x1c

; mul $r1 (r, imm)
; add r (r, imm)
; div rx ry -> remainder in r5 division in rx


_start:
    ;mov $r4, #0x00150a0b
    ;mov $r5, #0x23110a00
    ;mov $r6, #0x23110d0c
    lea $ra, [$pc]
    mov $r0, #27
    and $ra, #0xfffff000  ;start
    lea $r9, [$ra+#0x3f4]
    mov [$r9], #0x0b0a1500
    mov [$r9+#4], #0x000a1123  ;#0x23110a00
    mov [$r9+#8], #0x0c0d1123  ;#0x23110d0c
    mov $rb, #0xfffffff8
    mov $rc, #-12
    mov $pc, $r9

loop:
    mov [$ra], $rb
    add $ra, $r0
    add $pc, $rc 
    ;rjmp loop

