.data
Enter:	.asciiz	"
"
base:
.text
.data
V0:
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	3
	.word	5
	.word	7
.text
main:
	la	$t1	V0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$fp	0($sp)
	addi	$sp	$sp	-4
	move	$fp	$sp
	sw	$ra	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	17
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-100
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	3
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	add	$t3	$fp	-100
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	3
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	3
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	li	$t1	27
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
.data
V1:	.asciiz	"z="
.text
	li	$v0	4
	la	$a0	V1
	syscall
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
.data
V2:	.asciiz	"ia[0]="
.text
	li	$v0	4
	la	$a0	V2
	syscall
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
.data
V3:	.asciiz	"z="
.text
	li	$v0	4
	la	$a0	V3
	syscall
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
.data
V4:	.asciiz	"ia[1]="
.text
	li	$v0	4
	la	$a0	V4
	syscall
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
.data
V5:	.asciiz	"ia[2]="
.text
	li	$v0	4
	la	$a0	V5
	syscall
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	li	$t1	2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	li	$t2	0
	sub	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
L1:
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	slt	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	beqz	$t1	L0
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	b	L1
L0:
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
L3:
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	sle	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	beqz	$t1	L2
	lw	$t3	8($fp)
	add	$t3	$t3	40
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	sw	$t2	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	mul	$t1	$t1	4
	add	$t2	$t2	$t1
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-104
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t2	$t3	$t2
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	sw	$t1	0($t2)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	b	L3
L2:
	lw	$ra	0($fp)
	move	$sp	$fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	addi	$sp	$sp	4
	jr	$ra
