	.file	"test_data.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$42, 12(%esp)
	jmp	L2
L3:
	subl	$1, 12(%esp)
L2:
	cmpl	$0, 12(%esp)
	jg	L3
	leave
	ret
	.ident	"GCC: (GNU) 4.9.1"
