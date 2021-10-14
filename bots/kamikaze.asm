.section .bot #0x400000 #0x400 rwx
_start:
	lea $r3, [$pc+#0x64]
	mov $r0, $r3
	mov $r1, $r0
	and $r1, #0xfffff000
	lea $r6, [$r1+0x40]
	lea $sp, [$r1+#0x3a0]
	lea $r2, [$r1+#0x400] ; upper bound
	
	mov $rc, #0x060f1142 ; kamikaze opcode:
	mov $rb, #0x020f1115
	mov $ra, #0x003c003c
	mov $r9, #0x003c003c
	mov $r8, #0x000f0146
	mov $r7, #0xffffffff ; illegal instructions to kill opponent
	mov $r0, $r7
	mov $r1, $r7
	jmp $r3

	pusha
	jmp $sp

_kamikaze:
	cmp $sp, $r6	
	cmovb $sp, $r2
	pusha
	pusha
	pusha
	pusha
	jmp $sp
