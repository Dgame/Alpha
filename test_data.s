	.file	"test_data.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "c = %d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$4, 24(%esp)
	movl	$4, 20(%esp)
	movl	$23, 28(%esp)
	movl	24(%esp), %eax
	cmpl	20(%esp), %eax
	jle	L2
	movl	24(%esp), %eax
	cmpl	20(%esp), %eax
	jge	L2
	movl	$42, 28(%esp)
L2:
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	leave
	ret
	.ident	"GCC: (GNU) 4.9.1"
	.def	_printf;	.scl	2;	.type	32;	.endef
