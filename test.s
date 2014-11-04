.text
.globl	_alpha_main
.def	_alpha_main

_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
# Begin print
	pushl	$LS1
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$42
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$23
	call	_print_int
	addl	$4, %esp
# End print
# Begin Var 
	movl	$42, 0(%esp)
# End Var 
# Begin ByVal 
	movl	0(%esp), %eax
	movl	%eax, 4(%esp)
# End ByVal 
# Begin print
	pushl	$LS2
	call	_print_string
	addl	$4, %esp
# End print
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
# Begin Var 
	movl	$4, 8(%esp)
# End Var 
# Begin Var 
	movl	$2, 12(%esp)
# End Var 
# Begin print
	pushl	$LS3
	call	_print_string
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
	pushl	$LS4
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin MulOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	imull	0(%esp), %eax
	addl	$4, %esp
# End MulOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin NumExpr 
	movl	$25, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$5, %eax
# End NumExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
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
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS5
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
	movl	%eax, 16(%esp)
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
	movl	%eax, 20(%esp)
# End Var 
# Begin Var 
# Begin SubOp 
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
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	movl	%eax, 24(%esp)
# End Var 
# Begin Var 
# Begin MulOp 
# Begin SubOp 
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
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
	movl	%eax, 28(%esp)
# End Var 
# Begin print
# Begin VarExpr 
	movl	16(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	20(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	24(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	28(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS6
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	20(%esp), %eax
# End VarExpr 
	addl	16(%esp), %eax
# End AddOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	16(%esp), %eax
# End VarExpr 
	addl	20(%esp), %eax
# End AddOp 
	pushl	%eax
	call	_print_int
	addl	$4, %esp
# End print
	addl	$32, %esp
	popl	%ebp
	ret
.data
	LS1:	.ascii "Base test\0"
	LS2:	.ascii "First variables\0"
	LS3:	.ascii "Reassigned variables\0"
	LS4:	.ascii "Math. prints\0"
	LS5:	.ascii "Math. variable\0"
	LS6:	.ascii "Math. prints with variables\0"
