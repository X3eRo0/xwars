.section .bot #0x402000 #0x100 rwx

;r0-r9 ra rb rc sp bp pc
;lea source destination

; 1337000 - 13373ff
; 0x00 illegal, 0x1c

; mul $r1 (r, imm)
; add r (r, imm)
; div rx ry -> remainder in r5 division in rx


_start:
    lea $ra, [$pc]
    mov $r3, $ra
    ;mov $rb, $r9
    and $ra, #0xfffff000
    lea $rb, [$ra+#0x400]
    mov $rc, #0x400
    mov $r1, #0x13371337 ; a 
    ;mov $r2, #0xbadc0fee ; b
    ;mov $r3, #0xcafebabe ; r

loop:
    mov $r4, $ra

rand:
    mul $r3, $r1
    ;add $r3, $r2
    div $r3, $rc
    add $r4, $r5
    mov [$r4], #0xffffffff
    rjmp loop
    
    

