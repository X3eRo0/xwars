.section .init #0x400000 #0x400 rwx
	lea $r0, [$pc]
	mov $r1, $r0
	and $r1, #0xfffff000
	lea $sp, [$r1+#0x3a0]
	lea $r2, [$r1+#0x400] ; upper bound
	
	mov $rc, #0x0146003c ; kamikaze opcode:
	mov $rb, #0x0f11450f
	mov $ra, #0x0f11060f
	mov $r9, #0x3c000c02
	mov $r8, #0x3c003c00
    mov $r7, #0x0f014600
	mov $r5, #0xffffffff ; illegal instructions to kill opponent
	mov $r0, $r5
	mov $r1, $r5
	ret

.section .bot #0x401000 #0x400 rwx
_start:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
	pusha
	jmp $sp

_kamikaze:
	test $sp, $sp
	cmovz $sp, $r2
	pusha
	pusha
	pusha
	pusha
	jmp $sp
