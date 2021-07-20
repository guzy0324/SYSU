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
	add	$t3	$fp	16
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	20
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
	lw	$t3	12($fp)
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
	lw	$t3	12($fp)
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	lw	$t3	12($fp)
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
	lw	$ra	0($fp)
	move	$sp	$fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	addi	$sp	$sp	16
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
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	0
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
	li	$t1	4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	li	$t1	3
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	add	$t3	$fp	-4
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	li	$t2	0
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	add	$t1	$t3	$t2
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
	add	$t3	$fp	-8
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
	li	$v0	1
	lw	$a0	4($sp)
	addi	$sp	$sp	4
	syscall
	li	$v0	4
	la	$a0	Enter
	syscall
	add	$t3	$fp	-8
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
	lw	$ra	0($fp)
	move	$sp	$fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	addi	$sp	$sp	4
	jr	$ra
