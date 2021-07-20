	.file	"monc.c"
	.code16gcc
	.text
#APP
	.code16gcc

#NO_APP
	.comm	chheader,4,4
	.comm	cursor,4,4
	.comm	cursor_x,4,4
	.comm	cursor_y,4,4
	.globl	int2str
	.type	int2str, @function
int2str:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	.L2
.L3:
	movl	8(%ebp), %eax
	movl	$10, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	leal	48(%eax), %ecx
	movl	-4(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -4(%ebp)
	movb	%cl, %dl
	movb	%dl, -14(%ebp,%eax)
	movl	8(%ebp), %ecx
	movl	$1717986919, %eax
	imull	%ecx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 8(%ebp)
.L2:
	cmpl	$0, 8(%ebp)
	jne	.L3
	jmp	.L4
.L5:
	decl	-4(%ebp)
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%eax, %edx
	leal	-14(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movb	(%eax), %al
	movb	%al, (%edx)
.L4:
	cmpl	$0, -4(%ebp)
	jne	.L5
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	int2str, .-int2str
	.globl	BCD2str
	.type	BCD2str, @function
BCD2str:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	8(%ebp), %eax
	movb	%al, -4(%ebp)
	movb	-4(%ebp), %al
	shrb	$4, %al
	addl	$48, %eax
	movb	%al, %dl
	movl	12(%ebp), %eax
	movb	%dl, (%eax)
	movb	-4(%ebp), %al
	andl	$15, %eax
	leal	48(%eax), %edx
	movl	12(%ebp), %eax
	incl	%eax
	movb	%dl, (%eax)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	BCD2str, .-BCD2str
	.globl	display_str
	.type	display_str, @function
display_str:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$12, %esp
	.cfi_offset 3, -12
	movl	$0, -8(%ebp)
	movl	$0, -12(%ebp)
	movl	$0, -16(%ebp)
	jmp	.L8
.L11:
	movl	-16(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	cmpb	$10, %al
	jne	.L9
	movl	$0, -8(%ebp)
	incl	-12(%ebp)
	jmp	.L10
.L9:
	movl	16(%ebp), %edx
	movl	-12(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	-8(%ebp), %eax
	addl	%eax, %edx
	movl	-16(%ebp), %ebx
	movl	8(%ebp), %eax
	addl	%ebx, %eax
	movb	(%eax), %al
	movsbl	%al, %eax
	pushl	20(%ebp)
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	call	_display
	addl	$16, %esp
	incl	-8(%ebp)
.L10:
	incl	-16(%ebp)
.L8:
	movl	-16(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	testb	%al, %al
	jne	.L11
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	display_str, .-display_str
	.globl	new_page
	.type	new_page, @function
new_page:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, cursor_x
	movl	$0, cursor_y
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	call	_cls
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	new_page, .-new_page
	.globl	print
	.type	print, @function
print:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	.L14
.L17:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	cmpb	$10, %al
	jne	.L15
	movl	$0, cursor_x
	movl	cursor_y, %eax
	incl	%eax
	movl	%eax, cursor_y
	jmp	.L16
.L15:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	movsbl	%al, %eax
	pushl	%eax
	call	_put
	addl	$4, %esp
	movl	cursor_x, %eax
	incl	%eax
	movl	%eax, cursor_x
.L16:
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	incl	-4(%ebp)
.L14:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	testb	%al, %al
	jne	.L17
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	print, .-print
	.globl	new_node
	.type	new_node, @function
new_node:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	jne	.L19
	movl	$0, %eax
	jmp	.L20
.L19:
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%eax, (%edx)
	cmpl	$0, 8(%ebp)
	je	.L21
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	-4(%ebp), %edx
	leal	0(,%edx,8), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	movl	4(%eax), %eax
	movl	%eax, 4(%edx)
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L22
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%eax, (%edx)
.L22:
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%eax, 4(%edx)
	jmp	.L23
.L21:
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	$0, 4(%eax)
.L23:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, 8(%ebp)
	jne	.L24
	movl	12(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
.L24:
	movl	-4(%ebp), %eax
.L20:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	new_node, .-new_node
	.globl	delete_node
	.type	delete_node, @function
delete_node:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, 8(%ebp)
	jne	.L26
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
.L26:
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L27
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	8(%ebp), %edx
	leal	0(,%edx,8), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	movl	(%edx), %edx
	leal	0(,%edx,8), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	movl	4(%eax), %eax
	movl	%eax, 4(%edx)
.L27:
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L28
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	8(%ebp), %edx
	leal	0(,%edx,8), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	movl	4(%edx), %edx
	leal	0(,%edx,8), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	movl	(%eax), %eax
	movl	%eax, (%edx)
.L28:
	movl	8(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	movl	16(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	delete_node, .-delete_node
	.globl	init_node
	.type	init_node, @function
init_node:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	.L30
.L31:
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	-4(%ebp), %edx
	incl	%edx
	movl	%edx, (%eax)
	incl	-4(%ebp)
.L30:
	movl	16(%ebp), %eax
	decl	%eax
	cmpl	%eax, -4(%ebp)
	jl	.L31
	movl	-4(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	$0, (%eax)
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	pushl	12(%ebp)
	pushl	8(%ebp)
	pushl	$0
	call	new_node
	addl	$12, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	init_node, .-init_node
	.comm	chsp,256,32
	.comm	chndsp,2048,32
	.globl	new_ch
	.type	new_ch, @function
new_ch:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movb	%al, -8(%ebp)
	pushl	$chndsp
	pushl	$chheader
	pushl	12(%ebp)
	call	new_node
	addl	$12, %esp
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	je	.L33
	movl	-4(%ebp), %eax
	leal	chsp(%eax), %edx
	movb	-8(%ebp), %al
	movb	%al, (%edx)
.L33:
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	new_ch, .-new_ch
	.globl	dump_node
	.type	dump_node, @function
dump_node:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	.L36
.L42:
	movl	chheader, %eax
	movb	chsp(%eax), %al
	cmpb	$96, %al
	jle	.L37
	movl	chheader, %eax
	movb	chsp(%eax), %al
	cmpb	$122, %al
	jg	.L37
	movl	chheader, %eax
	movb	chsp(%eax), %al
	leal	-32(%eax), %edx
	movl	chheader, %eax
	movb	%dl, chsp(%eax)
	jmp	.L38
.L37:
	movl	chheader, %eax
	movb	chsp(%eax), %al
	cmpb	$9, %al
	jne	.L38
	movl	chheader, %eax
	movb	$32, chsp(%eax)
.L38:
	movl	chheader, %eax
	movl	-4(%ebp), %ecx
	movl	8(%ebp), %edx
	addl	%ecx, %edx
	movb	chsp(%eax), %al
	movb	%al, (%edx)
	movl	chheader, %eax
	pushl	$chndsp
	pushl	$chheader
	pushl	%eax
	call	delete_node
	addl	$12, %esp
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	cmpb	$32, %al
	jne	.L39
	jmp	.L40
.L41:
	movl	chheader, %eax
	pushl	$chndsp
	pushl	$chheader
	pushl	%eax
	call	delete_node
	addl	$12, %esp
.L40:
	movl	chheader, %eax
	testl	%eax, %eax
	je	.L39
	movl	chheader, %eax
	movb	chsp(%eax), %al
	cmpb	$32, %al
	je	.L41
	movl	chheader, %eax
	movb	chsp(%eax), %al
	cmpb	$9, %al
	je	.L41
.L39:
	incl	-4(%ebp)
.L36:
	movl	chheader, %eax
	movb	chsp(%eax), %al
	testb	%al, %al
	jne	.L42
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	dump_node, .-dump_node
	.globl	read
	.type	read, @function
read:
.LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	chheader, %eax
	movl	%eax, cursor
	movl	$0, cursor_x
	movl	$0, cursor_y
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	call	_get
	movw	%ax, -18(%ebp)
	leal	-18(%ebp), %eax
	movw	(%eax), %ax
	movw	%ax, -20(%ebp)
	jmp	.L44
.L62:
	movb	-20(%ebp), %al
	testb	%al, %al
	je	.L45
	movb	-20(%ebp), %al
	cmpb	$-32, %al
	jne	.L46
.L45:
	movb	-19(%ebp), %al
	cmpb	$75, %al
	jne	.L47
	movl	cursor, %eax
	movl	chndsp+4(,%eax,8), %eax
	testl	%eax, %eax
	je	.L63
	movl	cursor, %eax
	movl	chndsp+4(,%eax,8), %eax
	movl	%eax, cursor
	movl	cursor_x, %eax
	decl	%eax
	movl	%eax, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L63
.L47:
	movb	-19(%ebp), %al
	cmpb	$77, %al
	jne	.L50
	movl	cursor, %eax
	movl	chndsp(,%eax,8), %eax
	testl	%eax, %eax
	je	.L63
	movl	cursor, %eax
	movl	chndsp(,%eax,8), %eax
	movl	%eax, cursor
	movl	cursor_x, %eax
	incl	%eax
	movl	%eax, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L63
.L50:
	movb	-19(%ebp), %al
	cmpb	$72, %al
	jne	.L52
	movl	chheader, %eax
	movl	%eax, cursor
	movl	$0, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L63
.L52:
	movb	-19(%ebp), %al
	cmpb	$80, %al
	jne	.L63
	jmp	.L53
.L54:
	movl	cursor_x, %eax
	incl	%eax
	movl	%eax, cursor_x
	movl	cursor, %eax
	movl	chndsp(,%eax,8), %eax
	movl	%eax, cursor
.L53:
	movl	cursor, %eax
	movb	chsp(%eax), %al
	testb	%al, %al
	jne	.L54
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L63
.L46:
	movb	-20(%ebp), %al
	cmpb	$8, %al
	jne	.L56
	movl	cursor, %eax
	movl	chndsp+4(,%eax,8), %eax
	testl	%eax, %eax
	je	.L55
	movl	cursor, %eax
	movl	chndsp+4(,%eax,8), %eax
	pushl	$chndsp
	pushl	$chheader
	pushl	%eax
	call	delete_node
	addl	$12, %esp
	movl	cursor_x, %eax
	decl	%eax
	movl	%eax, cursor_x
	movl	cursor_x, %eax
	movl	%eax, -4(%ebp)
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	movl	cursor, %eax
	movl	%eax, -8(%ebp)
	jmp	.L58
.L59:
	movl	-8(%ebp), %eax
	addl	$chsp, %eax
	movb	(%eax), %al
	movsbl	%al, %eax
	pushl	%eax
	call	_put
	addl	$4, %esp
	incl	-4(%ebp)
	movl	cursor_y, %eax
	pushl	%eax
	pushl	-4(%ebp)
	call	_move
	addl	$8, %esp
	movl	-8(%ebp), %eax
	movl	chndsp(,%eax,8), %eax
	movl	%eax, -8(%ebp)
.L58:
	cmpl	$0, -8(%ebp)
	jne	.L59
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L55
.L56:
	movl	cursor, %edx
	movb	-20(%ebp), %al
	movsbl	%al, %eax
	pushl	%edx
	pushl	%eax
	call	new_ch
	addl	$8, %esp
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	.L55
	movl	cursor_x, %eax
	movl	%eax, -16(%ebp)
	jmp	.L60
.L61:
	movl	-12(%ebp), %eax
	addl	$chsp, %eax
	movb	(%eax), %al
	movsbl	%al, %eax
	pushl	%eax
	call	_put
	addl	$4, %esp
	incl	-16(%ebp)
	movl	cursor_y, %eax
	pushl	%eax
	pushl	-16(%ebp)
	call	_move
	addl	$8, %esp
	movl	-12(%ebp), %eax
	movl	chndsp(,%eax,8), %eax
	movl	%eax, -12(%ebp)
.L60:
	movl	-12(%ebp), %eax
	addl	$chsp, %eax
	movb	(%eax), %al
	testb	%al, %al
	jne	.L61
	movl	cursor_x, %eax
	incl	%eax
	movl	%eax, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	jmp	.L55
.L63:
	nop
.L55:
	call	_get
	movw	%ax, -18(%ebp)
	leal	-18(%ebp), %eax
	movw	(%eax), %ax
	movw	%ax, -20(%ebp)
.L44:
	movb	-20(%ebp), %al
	cmpb	$13, %al
	jne	.L62
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	read, .-read
	.globl	cmp
	.type	cmp, @function
cmp:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	.L65
.L67:
	incl	-4(%ebp)
.L65:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %al
	testb	%al, %al
	je	.L66
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %dl
	movl	12(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movb	(%eax), %al
	cmpb	%al, %dl
	je	.L67
.L66:
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	addl	%edx, %eax
	movb	(%eax), %dl
	movl	12(%ebp), %ecx
	movl	-4(%ebp), %eax
	addl	%ecx, %eax
	movb	(%eax), %al
	cmpb	%al, %dl
	sete	%al
	movzbl	%al, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	cmp, .-cmp
	.comm	program,96,32
	.comm	progsz,4,4
	.globl	vir2phy
	.type	vir2phy, @function
vir2phy:
.LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	$18, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	leal	1(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %ecx
	movl	$954437177, %eax
	imull	%ecx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %ecx
	movl	$954437177, %eax
	imull	%ecx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	andl	$1, %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	movl	%edx, (%eax)
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	vir2phy, .-vir2phy
	.globl	cmd_call
	.type	cmd_call, @function
cmd_call:
.LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	jmp	.L71
.L73:
	incl	-8(%ebp)
.L71:
	movl	-8(%ebp), %eax
	movb	(%eax), %al
	testb	%al, %al
	je	.L72
	movl	-8(%ebp), %eax
	movb	(%eax), %al
	cmpb	$32, %al
	jne	.L73
.L72:
	movl	-8(%ebp), %eax
	movb	(%eax), %al
	testb	%al, %al
	je	.L74
	movl	-8(%ebp), %eax
	movb	$0, (%eax)
	movl	$0, -12(%ebp)
	jmp	.L75
.L78:
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program, %eax
	movl	(%eax), %eax
	pushl	%eax
	pushl	8(%ebp)
	call	cmp
	addl	$8, %esp
	testl	%eax, %eax
	je	.L76
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+4, %eax
	movl	(%eax), %eax
	leal	-28(%ebp), %edx
	pushl	%edx
	leal	-24(%ebp), %edx
	pushl	%edx
	leal	-20(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	vir2phy
	addl	$16, %esp
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+8, %eax
	movl	(%eax), %ebx
	movl	-28(%ebp), %ecx
	movl	-24(%ebp), %edx
	movl	-20(%ebp), %eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	call	_callf
	addl	$16, %esp
	nop
	jmp	.L77
.L76:
	incl	-12(%ebp)
.L75:
	movl	progsz, %eax
	cmpl	%eax, -12(%ebp)
	jl	.L78
.L77:
	incl	-8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 8(%ebp)
	jmp	.L71
.L74:
	movl	$0, -16(%ebp)
	jmp	.L80
.L83:
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program, %eax
	movl	(%eax), %eax
	pushl	%eax
	pushl	8(%ebp)
	call	cmp
	addl	$8, %esp
	testl	%eax, %eax
	je	.L81
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+4, %eax
	movl	(%eax), %eax
	leal	-40(%ebp), %edx
	pushl	%edx
	leal	-36(%ebp), %edx
	pushl	%edx
	leal	-32(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	vir2phy
	addl	$16, %esp
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+8, %eax
	movl	(%eax), %ebx
	movl	-40(%ebp), %ecx
	movl	-36(%ebp), %edx
	movl	-32(%ebp), %eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	call	_callf
	addl	$16, %esp
	nop
	jmp	.L84
.L81:
	incl	-16(%ebp)
.L80:
	movl	progsz, %eax
	cmpl	%eax, -16(%ebp)
	jl	.L83
.L84:
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	cmd_call, .-cmd_call
	.section	.rodata
.LC0:
	.string	"Name"
.LC1:
	.string	"Start"
.LC2:
	.string	"Size"
	.text
	.globl	cmd_list
	.type	cmd_list, @function
cmd_list:
.LFB14:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	call	new_page
	pushl	$.LC0
	call	print
	addl	$4, %esp
	movl	$13, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	pushl	$.LC1
	call	print
	addl	$4, %esp
	movl	$20, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	pushl	$.LC2
	call	print
	addl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	.L88
.L89:
	movl	cursor_y, %eax
	incl	%eax
	movl	%eax, cursor_y
	movl	$0, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program, %eax
	movl	(%eax), %eax
	pushl	%eax
	call	print
	addl	$4, %esp
	movl	$13, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+4, %eax
	movl	(%eax), %eax
	leal	-15(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	int2str
	addl	$8, %esp
	leal	-15(%ebp), %eax
	pushl	%eax
	call	print
	addl	$4, %esp
	movl	$20, cursor_x
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$program+8, %eax
	movl	(%eax), %eax
	leal	-15(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	int2str
	addl	$8, %esp
	leal	-15(%ebp), %eax
	pushl	%eax
	call	print
	addl	$4, %esp
	incl	-4(%ebp)
.L88:
	movl	progsz, %eax
	cmpl	%eax, -4(%ebp)
	jl	.L89
	call	_get
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE14:
	.size	cmd_list, .-cmd_list
	.comm	command,64,32
	.comm	cmdsz,4,4
	.globl	execute
	.type	execute, @function
execute:
.LFB15:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L91
.L93:
	incl	-4(%ebp)
.L91:
	movl	-4(%ebp), %eax
	movb	(%eax), %al
	cmpb	$32, %al
	je	.L92
	movl	-4(%ebp), %eax
	movb	(%eax), %al
	testb	%al, %al
	jne	.L93
.L92:
	movl	-4(%ebp), %eax
	movb	(%eax), %al
	testb	%al, %al
	je	.L94
	movl	-4(%ebp), %eax
	movb	$0, (%eax)
	incl	-4(%ebp)
.L94:
	movl	$0, -8(%ebp)
	jmp	.L95
.L98:
	movl	-8(%ebp), %eax
	movl	command(,%eax,8), %eax
	pushl	%eax
	pushl	8(%ebp)
	call	cmp
	addl	$8, %esp
	testl	%eax, %eax
	je	.L96
	movl	-8(%ebp), %eax
	movl	command+4(,%eax,8), %eax
	pushl	-4(%ebp)
	call	*%eax
	addl	$4, %esp
	movl	$1, %eax
	jmp	.L97
.L96:
	incl	-8(%ebp)
.L95:
	movl	cmdsz, %eax
	cmpl	%eax, -8(%ebp)
	jl	.L98
	movl	$0, %eax
.L97:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	execute, .-execute
	.comm	lysp,256,32
	.comm	lyndsp,128,32
	.comm	lyheader,4,4
	.globl	new_layer
	.type	new_layer, @function
new_layer:
.LFB16:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	pushl	$lyndsp
	pushl	$lyheader
	pushl	24(%ebp)
	call	new_node
	addl	$12, %esp
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	je	.L100
	movl	-4(%ebp), %eax
	sall	$4, %eax
	leal	lysp(%eax), %edx
	movl	8(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %eax
	sall	$4, %eax
	leal	lysp+4(%eax), %edx
	movl	12(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %eax
	sall	$4, %eax
	leal	lysp+8(%eax), %edx
	movl	16(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %eax
	sall	$4, %eax
	leal	lysp+12(%eax), %edx
	movl	20(%ebp), %eax
	movl	%eax, (%edx)
.L100:
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE16:
	.size	new_layer, .-new_layer
	.comm	lyfnsp,192,32
	.comm	lyfnndsp,128,32
	.comm	lyfnheader,4,4
	.globl	new_layfun
	.type	new_layfun, @function
new_layfun:
.LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	pushl	$lyfnndsp
	pushl	$lyfnheader
	pushl	20(%ebp)
	call	new_node
	addl	$12, %esp
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	je	.L103
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	leal	lyfnsp(%eax), %edx
	movl	8(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	leal	lyfnsp+4(%eax), %edx
	movl	12(%ebp), %eax
	movl	%eax, (%edx)
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	leal	lyfnsp+8(%eax), %edx
	movl	16(%ebp), %eax
	movl	%eax, (%edx)
.L103:
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE17:
	.size	new_layfun, .-new_layfun
	.globl	hotwheel_arr
	.data
	.align 4
	.type	hotwheel_arr, @object
	.size	hotwheel_arr, 4
hotwheel_arr:
	.string	"/|\\"
	.globl	hotwheel_str
	.bss
	.type	hotwheel_str, @object
	.size	hotwheel_str, 2
hotwheel_str:
	.zero	2
	.text
	.globl	clock_hotwheel
	.type	clock_hotwheel, @function
clock_hotwheel:
.LFB18:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	$3, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	movb	hotwheel_arr(%eax), %al
	movb	%al, hotwheel_str
	movl	lyheader, %eax
	pushl	%eax
	pushl	$63
	pushl	$24
	pushl	$60
	pushl	$hotwheel_str
	call	new_layer
	addl	$20, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	$3, %ecx
	cltd
	idivl	%ecx
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L107
	movl	8(%ebp), %eax
	movl	$3, (%eax)
.L107:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE18:
	.size	clock_hotwheel, .-clock_hotwheel
	.globl	clock_str
	.data
	.align 4
	.type	clock_str, @object
	.size	clock_str, 20
clock_str:
	.string	"20yy/mm/dd hh:mm:ss"
	.text
	.globl	clock_time
	.type	clock_time, @function
clock_time:
.LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L109
	call	_get_time
	movl	$clock_str+2, -4(%ebp)
	movl	$0, -8(%ebp)
	jmp	.L110
.L111:
	movl	-8(%ebp), %eax
	addl	$_time, %eax
	movb	(%eax), %al
	movzbl	%al, %eax
	pushl	-4(%ebp)
	pushl	%eax
	call	BCD2str
	addl	$8, %esp
	addl	$3, -4(%ebp)
	incl	-8(%ebp)
.L110:
	cmpl	$5, -8(%ebp)
	jle	.L111
	movl	lyheader, %eax
	pushl	%eax
	pushl	$61
	pushl	$24
	pushl	$61
	pushl	$clock_str
	call	new_layer
	addl	$20, %esp
.L109:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L113
	movl	8(%ebp), %eax
	movl	$2, (%eax)
.L113:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE19:
	.size	clock_time, .-clock_time
	.globl	ouch_str
	.data
	.align 4
	.type	ouch_str, @object
	.size	ouch_str, 11
ouch_str:
	.string	"OUCH!OUCH!"
	.comm	ouch_color,4,4
	.text
	.globl	clock_ouch
	.type	clock_ouch, @function
clock_ouch:
.LFB20:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	lyheader, %edx
	movl	ouch_color, %eax
	pushl	%edx
	pushl	%eax
	pushl	$12
	pushl	$35
	pushl	$ouch_str
	call	new_layer
	addl	$20, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$1, %eax
	jne	.L115
	movl	$0, ouch_color
	jmp	.L117
.L115:
	movl	ouch_color, %eax
	notl	%eax
	movl	%eax, ouch_color
.L117:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE20:
	.size	clock_ouch, .-clock_ouch
	.globl	clock
	.type	clock, @function
clock:
.LFB21:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$4, %esp
	.cfi_offset 3, -12
	movl	lyfnheader, %eax
	movl	%eax, -8(%ebp)
	jmp	.L119
.L121:
	movl	-8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp, %eax
	leal	8(%eax), %ebx
	movl	-8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp+4, %eax
	movl	(%eax), %edx
	movl	-8(%ebp), %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$2, %eax
	addl	$lyfnsp, %eax
	movl	(%eax), %eax
	pushl	%ebx
	pushl	%edx
	pushl	%eax
	call	_call
	addl	$12, %esp
	movl	-8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp+8, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L120
	pushl	$lyfnndsp
	pushl	$lyfnheader
	pushl	-8(%ebp)
	call	delete_node
	addl	$12, %esp
.L120:
	movl	-8(%ebp), %eax
	movl	lyfnndsp(,%eax,8), %eax
	movl	%eax, -8(%ebp)
.L119:
	movl	-8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L121
	movl	-8(%ebp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp+4, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L121
	jmp	.L122
.L123:
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+12, %eax
	movl	(%eax), %ebx
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+8, %eax
	movl	(%eax), %ecx
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+4, %eax
	movl	(%eax), %edx
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp, %eax
	movl	(%eax), %eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	call	display_str
	addl	$16, %esp
	movl	lyheader, %eax
	pushl	$lyndsp
	pushl	$lyheader
	pushl	%eax
	call	delete_node
	addl	$12, %esp
.L122:
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L123
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE21:
	.size	clock, .-clock
	.section	.rodata
.LC3:
	.string	"CALL"
.LC4:
	.string	"LIST"
.LC5:
	.string	"LTUP.COM"
.LC6:
	.string	"LTDN.COM"
.LC7:
	.string	"RTUP.COM"
.LC8:
	.string	"RTDN.COM"
.LC9:
	.string	"CAL.COM"
.LC10:
	.string	"WP.COM"
	.text
	.globl	init
	.type	init, @function
init:
.LFB22:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	_cls
	movl	$.LC3, command
	movl	$cmd_call, command+4
	movl	$.LC4, command+8
	movl	$cmd_list, command+12
	movl	$2, cmdsz
	movl	$.LC5, program
	movl	$32, program+4
	movl	$1, program+8
	movl	$.LC6, program+12
	movl	$33, program+16
	movl	$1, program+20
	movl	$.LC7, program+24
	movl	$34, program+28
	movl	$1, program+32
	movl	$.LC8, program+36
	movl	$35, program+40
	movl	$1, program+44
	movl	$.LC9, program+48
	movl	$36, program+52
	movl	$12, program+56
	movl	$.LC10, program+60
	movl	$48, program+64
	movl	$1, program+68
	movl	$6, progsz
	pushl	$256
	pushl	$chndsp
	pushl	$chheader
	call	init_node
	addl	$12, %esp
	movl	chheader, %eax
	movb	$0, chsp(%eax)
	pushl	$16
	pushl	$lyndsp
	pushl	$lyheader
	call	init_node
	addl	$12, %esp
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+4, %eax
	movl	$0, (%eax)
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+8, %eax
	movl	$0, (%eax)
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp, %eax
	movl	$0, (%eax)
	movl	lyheader, %eax
	sall	$4, %eax
	addl	$lysp+12, %eax
	movl	$0, (%eax)
	pushl	$16
	pushl	$lyfnndsp
	pushl	$lyfnheader
	call	init_node
	addl	$12, %esp
	movl	lyfnheader, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp, %eax
	movl	$0, (%eax)
	movl	lyfnheader, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp+4, %eax
	movl	$0, (%eax)
	movl	lyfnheader, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	$lyfnsp+8, %eax
	movl	$0, (%eax)
	movl	lyfnheader, %eax
	pushl	%eax
	pushl	$3
	pushl	$_clock_hotwheel
	pushl	$2048
	call	new_layfun
	addl	$16, %esp
	movl	lyfnheader, %eax
	pushl	%eax
	pushl	$4
	pushl	$_clock_time
	pushl	$2048
	call	new_layfun
	addl	$16, %esp
	pushl	$8
	pushl	$_clock
	pushl	$2048
	call	_set_int
	addl	$12, %esp
	pushl	$32
	pushl	$_int_20h
	pushl	$2048
	call	_set_int
	addl	$12, %esp
	pushl	$33
	pushl	$_int_21h
	pushl	$2048
	call	_set_int
	addl	$12, %esp
	pushl	$34
	pushl	$_int_22h
	pushl	$2048
	call	_set_int
	addl	$12, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE22:
	.size	init, .-init
	.section	.rodata
.LC11:
	.string	"Not a commad!"
.LC12:
	.string	"EXIT"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$256, %esp
	call	init
.L127:
	call	new_page
	call	read
	leal	-256(%ebp), %eax
	pushl	%eax
	call	dump_node
	addl	$4, %esp
	leal	-256(%ebp), %eax
	pushl	%eax
	call	execute
	addl	$4, %esp
	testl	%eax, %eax
	jne	.L126
	movl	$0, cursor_x
	movl	cursor_y, %eax
	incl	%eax
	movl	%eax, cursor_y
	movl	cursor_y, %edx
	movl	cursor_x, %eax
	pushl	%edx
	pushl	%eax
	call	_move
	addl	$8, %esp
	pushl	$.LC11
	call	print
	addl	$4, %esp
	call	_get
.L126:
	pushl	$.LC12
	leal	-256(%ebp), %eax
	pushl	%eax
	call	cmp
	addl	$8, %esp
	testl	%eax, %eax
	je	.L127
	call	_cls
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
