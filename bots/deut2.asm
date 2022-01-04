
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
    mov $r0, #39
    and $ra, #0xfffff055
    mov $rb, #0xfffffff8
    mov $rc, #-12

loop:
    mov [$ra], $rb
    add $ra, $r0
    add $pc, $rc 
    ;rjmp loop

