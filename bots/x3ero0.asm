.section .init 0x401000 0x100 r-x
_start:
	ret

.section .bot 0x402000 0x100 r-x

lea $r9, [$pc]
lea $ra, [$r9+#0x80]
mov $rb, $r9
and $rb, #0xfffff000
lea $rc, [$rb+#0x400]
; mov $ra, $rb
_outer_loop:
    cmp $ra, $r9
    rjz add_size_ra
    
    _inner_hook1:

    mov $r1, [$ra]
    test $r1, $r1
    rjnz place_invalid_instruction

    _inner_hook2:

    add $ra, #8
    cmp $ra, $rc
    rjae reset_ra
    rjmp _outer_loop

add_size_ra:
    add $ra, #0x80; size
    rjmp _inner_hook1

place_invalid_instruction:
    mov [$ra], #0xffffffff
    rjmp _inner_hook2

reset_ra:
    mov $ra, $rb
    rjmp _outer_loop
