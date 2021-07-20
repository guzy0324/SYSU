.data
Enter:	.asciiz	"
"
base:
.text
.data
V0:
.text
L0:
	sw	$fp	0($sp)
	addi	$sp	$sp	-4
	move	$fp	$sp
	sw	$ra	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	12
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
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
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	b	L1
L2:
	add	$t3	$fp	12
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
	seq	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	beqz	$t1	L3
	li	$t1	1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	b	L1
L3:
	add	$t3	$fp	12
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
	sub	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	0
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	jal	L0
	add	$t3	$fp	12
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
	sub	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	0
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	jal	L0
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t2	$t1
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-4
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
	add	$t3	$fp	-4
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	b	L1
L1:
	lw	$ra	0($fp)
	move	$sp	$fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	addi	$sp	$sp	8
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	jr	$ra
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
.data
V1:	.asciiz	"sum(5)="
.text
	li	$v0	4
	la	$a0	V1
	syscall
	li	$t1	5
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	0
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	jal	L0
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
	lw	$ra	0($fp)
	move	$sp	$fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	addi	$sp	$sp	4
	jr	$ra
