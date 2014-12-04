.text
.globl	_alpha_main
_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
# Begin Scope
	subl	$96, %esp
# Begin Var
	movl	$42, 0(%esp)
# End Var
# Begin Var
	movl	$23, 32(%esp)
# End Var
# Begin Var
	movl	-96(%ebp), %eax
	movl	%eax, 64(%esp)
# End Var
# Begin print
	pushl	$LC0
	call	_print_str
	addl	$4, %esp
	movl	-96(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$LC1
	call	_print_str
	addl	$4, %esp
	movl	-64(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$LC2
	call	_print_str
	addl	$4, %esp
	movl	-32(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$LC3
	call	_print_str
	addl	$4, %esp
# Begin AddExpr 
	movl	-96(%ebp), %eax
	pushl	%eax
# Begin MulExpr 
	movl	-64(%ebp), %eax
	pushl	%eax
	movl	$3, %eax
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin Var
# Begin MulExpr 
	pushl	$3
	movl	$3, %eax
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulExpr 
	movl	%eax, 64(%esp)
# End Var
# Begin print
	pushl	$LC4
	call	_print_str
	addl	$4, %esp
	movl	-32(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$LC5
	call	_print_str
	addl	$4, %esp
	movl	-32(%ebp), %eax
	negl	%eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
	addl	$96, %esp
# End Scope
	popl	%ebp
ret
LC0:
	.ascii	"a = \0"
LC1:
	.ascii	"b = \0"
LC2:
	.ascii	"c = \0"
LC3:
	.ascii	"a + (b * 3) = \0"
LC4:
	.ascii	"c = \0"
LC5:
	.ascii	"-c = \0"
