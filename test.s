.text
.globl	_alpha_main
.def	_alpha_main

_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
# Begin print
	pushl	$LS1
	call	_print_string
	addl	$4, %esp
# End print
# Begin Var 
# Begin AddOp 
# Begin NumExpr 
	movl	$1, %eax
# End NumExpr 
	pushl	%eax
# Begin MulOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	movl	%eax, 0(%esp)
# End Var 
# Begin Var 
# Begin MulOp 
# Begin AddOp 
# Begin NumExpr 
	movl	$1, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	pushl	%eax
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	movl	%eax, 4(%esp)
# End Var 
# Begin Var 
# Begin SubOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin MulOp 
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	movl	%eax, 8(%esp)
# End Var 
# Begin Var 
# Begin MulOp 
# Begin SubOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	movl	%eax, 12(%esp)
# End Var 
# Begin print
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	12(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS2
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	pushl	%eax
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin MulOp 
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	pushl	%eax
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
	addl	$16, %esp
	popl	%ebp
	ret
.data
	LS1:	.ascii "Math. variable\0"
	LS2:	.ascii "Math. prints with variables\0"
