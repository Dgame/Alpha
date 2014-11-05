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
	# Begin NumExpr
        movl    $1, %eax
# End NumExpr
        # pushl   %eax
# Begin NumExpr
        # movl    $2, %eax
# End NumExpr
        cmpl    $1, %eax
        # addl    $4, %esp
	jle	L2
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
