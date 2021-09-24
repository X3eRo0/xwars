.section .init #0x400000 #0x400 rwx
	mov $r3, [$sp]
	mov $r0, $r3
	mov $r1, $r0
	and $r1, #0xfffff000
	lea $sp, [$r1+#0x3a0]
	lea $r2, [$r1+#0x400] ; upper bound
	
	mov $rc, #0x0f0f1145 ; kamikaze opcode:
	mov $rb, #0x020f1106
	mov $ra, #0x003c003c
	mov $r9, #0x003c003c
	mov $r8, #0x000f0146
	mov $r7, #0xffffffff ; illegal instructions to kill opponent
	mov $r0, $r7
	mov $r1, $r7
	jmp $r3

.section .bot #0x401000 #0x400 rwx
_start:
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
