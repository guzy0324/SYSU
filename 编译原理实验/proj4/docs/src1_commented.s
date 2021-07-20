.data			# directive tells the assembler to store the string in the program’s data segment
Enter:	.asciiz	"
"               # stores a null-terminated string in memory
base:
.text			# directive tells the assembler to store the instructions in its text segment
.data
V0:
	.word	-1
.text
# the main function
main:
	# load the address of V0 into $t1
	la	$t1	V0
	# then save $t1 onto stack
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	# save $fp (old frame pointer) onto stack
	sw	$fp	0($sp)
	addi	$sp	$sp	-4
	# set up new fp, pointing to sp
	move	$fp	$sp
	# save $ra (return address) onto stack
	sw	$ra	0($sp)
	addi	$sp	$sp	-4
	# load constant 4, and then save onto stack
	li	$t1	4
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	# let t3 point to $fp-4 (i.e., -1),
	# and then save its value onto stack
	add	$t3	$fp	-4
	sw	$t3	0($sp)
	addi	$sp	$sp	-4
	# load constant 0 into $t2
	li	$t2	0
	# pop value at $sp+4 (i.e., fp-4) into $t3
	lw	$t3	4($sp)
	addi	$sp	$sp	4
	# perform addition (t1=fp-4)
	add	$t1	$t3	$t2
	# load address $t1 into $t1 (i.e.,sp-4) 
	lw	$t1	0($t1)
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	# load constant 0 into $t1, then save onto stack
	li	$t1	0
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	# pop (t1=4)
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	# pop (t2=0)
	lw	$t2	4($sp)
	addi	$sp	$sp	4
	# do comparison (t1 >= t2)
	sge	$t1	$t2	$t1
	# save result onto stack
	sw	$t1	0($sp)
	addi	$sp	$sp	-4
	# pop (t1=1)
	lw	$t1	4($sp)
	addi	$sp	$sp	4
	# jump to L1, if $t1 is zero (for the case here,
    # execute the following syscall, instead of jumping to L1)
	beqz	$t1	L1
# system call of println
.data
V1:	.asciiz	"x>=0"
.text
    # system call code for print_str
	li	$v0	4
    # load address of string to print
	la	$a0	V1
    # do the print
	syscall
	b	L0
# to wrap up the main function
L1:
L0:
	# restore $ra
	lw	$ra	0($fp)
	# restore sp
	move	$sp	$fp
	# pop $fp
	lw	$fp	4($sp)
	addi	$sp	$sp	4
	# pop
	addi	$sp	$sp	4
	# jump
	jr	$ra
