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
	pushl	$L_0_STR
	call	_print_str
	addl	$4, %esp
	movl	-96(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$L_1_STR
	call	_print_str
	addl	$4, %esp
	movl	-64(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$L_2_STR
	call	_print_str
	addl	$4, %esp
	movl	-32(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$L_3_STR
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
	pushl	$L_4_STR
	call	_print_str
	addl	$4, %esp
	movl	-32(%ebp), %eax
	pushl	%eax
	call	_print_int
	addl	$4, %esp
	call	_print_ln
# End print
# Begin print
	pushl	$L_5_STR
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
L_0_STR:
	.ascii	"a = \0"
L_1_STR:
	.ascii	"b = \0"
L_2_STR:
	.ascii	"c = \0"
L_3_STR:
	.ascii	"a + (b * 3) = \0"
L_4_STR:
	.ascii	"c = \0"
L_5_STR:
	.ascii	"-c = \0"
