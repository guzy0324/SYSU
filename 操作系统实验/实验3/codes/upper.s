	.file	"upper.c"
	.text
	.globl	_Message
	.data
	.align 4
_Message:
	.ascii "AaBbCcDdEe"
	.text
	.globl	_upper
	.def	_upper;	.scl	2;	.type	32;	.endef
_upper:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	$0, -4(%ebp)
	jmp	L2
L4:
	movl	-4(%ebp), %eax
	addl	$_Message, %eax
	movb	(%eax), %al
	cmpb	$96, %al
	jle	L3
	movl	-4(%ebp), %eax
	addl	$_Message, %eax
	movb	(%eax), %al
	cmpb	$122, %al
	jg	L3
	movl	-4(%ebp), %eax
	addl	$_Message, %eax
	movb	(%eax), %al
	subl	$32, %eax
	movb	%al, %dl
	movl	-4(%ebp), %eax
	addl	$_Message, %eax
	movb	%dl, (%eax)
L3:
	incl	-4(%ebp)
L2:
	movl	-4(%ebp), %eax
	addl	$_Message, %eax
	movb	(%eax), %al
	testb	%al, %al
	jne	L4
	nop
	nop
	leave
	ret
	.ident	"GCC: (Rev2, Built by MSYS2 project) 9.3.0"
