.data
w1: .word
h1: .half
b1: .byte
.text
addiu  $1,$0,8
ori  $2,$0,2
add  $3,$2,$1
sub  $5,$3,$2
and  $4,$5,$2
or  $8,$4,$2
l1:
sll  $8,$8,1
bne $8,$1,l1
slti  $6,$2,4
slti  $7,$6,0
l2:
addiu $7,$7,8
beq $7,$1,l2
la $1, w1
sw  $2,4($1)
lw  $9,4($1)
addiu  $10,$0,-2
l3:
addiu  $10,$10,1
bltz $10,l3
andi  $11,$2,2
lui $12, 0xffff
sra $12, $12, 1
srl $12, $12, 1
sllv $12, $12, $6
srav $12, $12, $6
srlv $12, $12, $6
xor $15, $15, $15
l4:
xori $13, 1
bgtz $13, l4
nor $13, $13, $14
xor $13, $13, $14
slt $14, $13, $14
la $1 h1
sh $12, 2($1)
lh $12, 2($1)
la $1 b1
sb $12, 1($1)
lb $12, 1($1)
jal l5
j  halt
l5:
multu $13, $9
mfhi $15
mflo $16
divu $13, $9
mfhi $17
mflo $18
jr $ra
halt:
