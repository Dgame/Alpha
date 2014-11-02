	.file	"test_data.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Hallo\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$42, 28(%esp)
	jmp	L2
L3:
	subl	$1, 28(%esp)
L2:
	cmpl	$0, 28(%esp)
	jg	L3
	movl	$LC0, 24(%esp)
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	_printf
	leave
	ret
	.ident	"GCC: (GNU) 4.9.1"
	.def	_printf;	.scl	2;	.type	32;	.endef
