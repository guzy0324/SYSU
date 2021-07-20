j main
.data
.align 4
system_println_newline: .asciiz "\n"
.text
system_println:
li $t1 1
blt $s0 $t1 system_println_string_print
lw $a0 0($a0)
system_println_int_by_val_print:
li $v0 1     # println - int
syscall
j system_println_newline_print
system_println_string_print:
li $v0 4     # println - string
syscall
jr $ra
system_println_newline_print:
li $v0 4
la $a0 system_println_newline
syscall
jr $ra
system_readln:
move $t2 $a0
li $v0 5     # readln
syscall
sw $v0 0($t2)
jr $ra
.data
.align 4
base:
.text
.data
.align 4
.text
la $gp base
main:
move $t9 $sp
addi $t5 $sp -4
sw $t5 0($sp)
addi $sp $sp -4
li $t2 0    # uninitialized local var decl
sw $t2 0($sp)
addi $sp $sp -4
addi $t5 $sp -4
sw $t5 0($sp)
addi $sp $sp -4
li $t2 0    # uninitialized local var decl
sw $t2 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
move $s0 $0    # clear s0 before passing params
move $t8 $0
.data
.align 4
string_0: .asciiz "x=?"
.text
la $a0 string_0      # string param
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
move $s0 $0    # clear s0 before passing params
move $t8 $0
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $a0 $t0
addi $s0 $0 2
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_readln
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
     # if stmt
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
addi $t0 $0 10
sw $t0 0($sp)
addi $sp $sp -4
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
slt $t0 $t2 $t3     # calculate >
li $t1 1
slt $t0 $t0 $t1
slt $t4 $t2 $t3
slt $t5 $t3 $t2
or $t4 $t4 $t5
slt $t4 $t4 $t1
xor $t5 $t0 $t4
and $t0 $t0 $t5
beq $0 $t0 if_false_0
move $s0 $0    # clear s0 before passing params
move $t8 $0
.data
.align 4
string_1: .asciiz ">10"
.text
la $a0 string_1      # string param
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
j if_endif_0
if_false_0:
     # if stmt
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
addi $t0 $0 5
sw $t0 0($sp)
addi $sp $sp -4
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
slt $t0 $t2 $t3     # calculate >
li $t1 1
slt $t0 $t0 $t1
slt $t4 $t2 $t3
slt $t5 $t3 $t2
or $t4 $t4 $t5
slt $t4 $t4 $t1
xor $t5 $t0 $t4
and $t0 $t0 $t5
beq $0 $t0 if_false_1
move $s0 $0    # clear s0 before passing params
move $t8 $0
.data
.align 4
string_2: .asciiz ">5"
.text
la $a0 string_2      # string param
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
j if_endif_0
if_false_1:
     # else
move $s0 $0    # clear s0 before passing params
move $t8 $0
.data
.align 4
string_3: .asciiz "<=5"
.text
la $a0 string_3      # string param
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
j if_endif_0
if_endif_0:
addi $t0 $0 1
sw $t0 ($sp)   # stash RHS
addi $sp $sp -4
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
addi $sp $sp 4
lw $t2 ($sp)   # load RHS
sw $t2 0($t0)  # assign RHS to LHS
addi $t0 $0 0
sw $t0 ($sp)   # stash RHS
addi $sp $sp -4
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 -8($t0)    # get the addr
addi $sp $sp 4
lw $t2 ($sp)   # load RHS
sw $t2 0($t0)  # assign RHS to LHS
while_start_0:
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
addi $t0 $0 10
sw $t0 0($sp)
addi $sp $sp -4
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
slt $t0 $t2 $t3     # calculate <=
slt $t4 $t2 $t3
slt $t5 $t3 $t2
or $t4 $t4 $t5
li $t1 1
slt $t4 $t4 $t1
or $t0 $t0 $t4
beq $0 $t0 while_end_0
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 -8($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
add $t0 $t2 $t3
sw $t0 ($sp)   # stash RHS
addi $sp $sp -4
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 -8($t0)    # get the addr
addi $sp $sp 4
lw $t2 ($sp)   # load RHS
sw $t2 0($t0)  # assign RHS to LHS
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
move $t3 $t0
lw $t0 0($t3)
sw $t0 0($sp)
addi $sp $sp -4
addi $t0 $0 1
sw $t0 0($sp)
addi $sp $sp -4
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
add $t0 $t2 $t3
sw $t0 ($sp)   # stash RHS
addi $sp $sp -4
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 0($t0)    # get the addr
addi $sp $sp 4
lw $t2 ($sp)   # load RHS
sw $t2 0($t0)  # assign RHS to LHS
j while_start_0
while_end_0:
move $s0 $0    # clear s0 before passing params
move $t8 $0
.data
.align 4
string_4: .asciiz "y="
.text
la $a0 string_4      # string param
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
move $s0 $0    # clear s0 before passing params
move $t8 $0
move $t2 $0    # begin eval addr
move $t3 $0
move $t0 $t2   # prepare to return
add $t0 $t0 $t9    # local var access
lw $t0 -8($t0)    # get the addr
move $a0 $t0
addi $s0 $0 2
sw $t0 0($sp)
addi $sp $sp -4
sw $t1 0($sp)
addi $sp $sp -4
sw $t2 0($sp)
addi $sp $sp -4
sw $t3 0($sp)
addi $sp $sp -4
sw $t4 0($sp)
addi $sp $sp -4
sw $t5 0($sp)
addi $sp $sp -4
sw $t6 0($sp)
addi $sp $sp -4
sw $t7 0($sp)
addi $sp $sp -4
sw $t8 0($sp)
addi $sp $sp -4
sw $t9 0($sp)
addi $sp $sp -4
sw $ra 0($sp)
addi $sp $sp -4
sw $fp 0($sp)
addi $sp $sp -4
move $fp $sp
jal system_println
move $sp $fp
addi $sp $sp 4
lw $fp 0($sp)
addi $sp $sp 4
lw $ra 0($sp)
addi $sp $sp 4
lw $t9 0($sp)
addi $sp $sp 4
lw $t8 0($sp)
addi $sp $sp 4
lw $t7 0($sp)
addi $sp $sp 4
lw $t6 0($sp)
addi $sp $sp 4
lw $t5 0($sp)
addi $sp $sp 4
lw $t4 0($sp)
addi $sp $sp 4
lw $t3 0($sp)
addi $sp $sp 4
lw $t2 0($sp)
addi $sp $sp 4
lw $t1 0($sp)
addi $sp $sp 4
lw $t0 0($sp)
add $sp $sp $t8
li $v0 10   # exit
syscall
