.text
.globl	_alpha_main
.def	_alpha_main

_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
# Begin print
	pushl	$L_01
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$42
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$23
	call	_println_int
	addl	$4, %esp
# End print
# Begin Var 
	movl	$42, 0(%esp)
# End Var 
# Begin Var 
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, 4(%esp)
# End Var 
# Begin print
	pushl	$L_02
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin Var 
	movl	$4, 8(%esp)
# End Var 
# Begin Var 
	movl	$2, 12(%esp)
# End Var 
# Begin print
	pushl	$L_03
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	12(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	12(%esp), %eax
# End VarExpr 
	addl	%ebx, %eax
# End AddOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
	addl	$16, %esp
	popl	%ebp
	ret
.data
	L_01:	.ascii " :: Base test:\0"
	L_02:	.ascii " :: First variables:\0"
	L_03:	.ascii " :: Reassigned variables:\0"
