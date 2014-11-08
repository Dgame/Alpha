	.file	"test_data.c"
	.text
	.globl	_foo
	.def	_foo;	.scl	2;	.type	32;	.endef
_foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -8(%ebp)
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$64, %esp
	call	___main
	movl	$42, 60(%esp)
	movl	$9, 32(%esp)
	movl	$8, 28(%esp)
	movl	$7, 24(%esp)
	movl	$6, 20(%esp)
	movl	$5, 16(%esp)
	movl	$4, 12(%esp)
	movl	$3, 8(%esp)
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	call	_foo
	leave
	ret
	.ident	"GCC: (GNU) 4.9.1"
