.text
.globl	_alpha_main
.def	_alpha_main

_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
# Begin print
	pushl	$LS_01
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
	pushl	$LS_02
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
	movl	$4, 0(%esp)
# End Var 
# Begin Var 
	movl	$2, 4(%esp)
# End Var 
# Begin print
	pushl	$LS_03
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
# Begin print
	pushl	$LS_04
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin AddOp 
# Begin AddOp 
# Begin NumExpr 
	movl	$2, %eax
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
	movl	$2, %eax
# End NumExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	addl	0(%esp), %eax
	addl	$4, %esp
# End AddOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin SubOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin SubOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin SubOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	pushl	%eax
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	subl	0(%esp), %eax
	addl	$4, %esp
# End SubOp 
	pushl	%eax
	call	_println_int
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
	call	_println_int
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
	call	_println_int
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
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_05
	call	_println_string
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
	movl	%eax, 8(%esp)
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
	movl	%eax, 12(%esp)
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
	movl	%eax, 16(%esp)
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
	movl	%eax, 20(%esp)
# End Var 
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
# Begin VarExpr 
	movl	16(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	20(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_06
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	12(%esp), %eax
# End VarExpr 
	addl	8(%esp), %eax
# End AddOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin AddOp 
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	addl	12(%esp), %eax
# End AddOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_07
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
# Begin AddOp 
# Begin VarExpr 
	movl	12(%esp), %eax
# End VarExpr 
	addl	8(%esp), %eax
# End AddOp 
	movl	%eax, 8(%esp)
# End Var 
# Begin print
	pushl	$LS_08
	call	_print_string
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
	pushl	$LS_09
	call	_print_string
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
	pushl	$LS_10
	call	_println_string
	addl	$4, %esp
# End print
# Begin EnRef 
	leal	4(%esp), %eax
	movl	%eax, 24(%esp)
# End EnRef 
# Begin DeRef 
	movl	24(%esp), %eax
	movl	0(%eax), %eax
	movl	%eax, 28(%esp)
# End DeRef 
# Begin print
# Begin VarExpr 
	movl	24(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	28(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_11
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_12
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_13
	call	_println_string
	addl	$4, %esp
# End print
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	je		LE_15
LI_14:
# Begin print
	pushl	$LS_16
	call	_println_string
	addl	$4, %esp
# End print
LE_15:
# End if
# Begin Var 
	movl	$0, 0(%esp)
# End Var 
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	je		LE_18
LI_17:
# Begin print
	pushl	$LS_19
	call	_println_string
	addl	$4, %esp
# End print
LE_18:
# End if
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LE_21
LI_20:
# Begin print
	pushl	$LS_22
	call	_println_string
	addl	$4, %esp
# End print
LE_21:
# End if
# Begin print
	pushl	$LS_23
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
# Begin AddOp 
# Begin NumExpr 
	movl	$1, %eax
# End NumExpr 
	addl	0(%esp), %eax
# End AddOp 
	movl	%eax, 0(%esp)
# End Var 
# Begin Var 
# Begin MulOp 
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	imull	0(%esp), %eax
# End MulOp 
	movl	%eax, 0(%esp)
# End Var 
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LE_25
LI_24:
# Begin print
	pushl	$LS_26
	call	_println_string
	addl	$4, %esp
# End print
LE_25:
# End if
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	je		LE_28
LI_27:
# Begin print
	pushl	$LS_29
	call	_println_string
	addl	$4, %esp
# End print
LE_28:
# End if
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$1, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jle		LE_31
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jge		LE_31
LI_30:
# Begin print
	pushl	$LS_32
	call	_println_string
	addl	$4, %esp
# End print
LE_31:
# End if
# Begin print
	pushl	$LS_33
	call	_print_string
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
	pushl	$LS_34
	call	_println_string
	addl	$4, %esp
# End print
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jge		LE_36
LI_35:
# Begin print
	pushl	$LS_37
	call	_println_string
	addl	$4, %esp
# End print
LE_36:
# Begin else
# Begin print
	pushl	$LS_39
	call	_println_string
	addl	$4, %esp
# End print
LEND_38:
# End else
# End if
# Begin if
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jle		LE_41
LI_40:
# Begin print
	pushl	$LS_42
	call	_println_string
	addl	$4, %esp
# End print
LE_41:
# Begin else
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LEND_43
# Begin print
	pushl	$LS_44
	call	_println_string
	addl	$4, %esp
# End print
LEND_43:
# End else
# End if
# Begin print
	pushl	$LS_45
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
	movl	$4, 32(%esp)
# End Var 
# Begin while
LWL_46:
# Begin VarExpr 
	movl	32(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jle		LLE_48
LLB_47:
# Begin Loop
	decl	32(%esp)
# Begin print
	pushl	$LS_49
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	32(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# End Loop
	jmp		LWL_46
LLE_48:
# End while
# Begin print
	pushl	$LS_50
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	32(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
	addl	$36, %esp
	popl	%ebp
	ret
.data
	LS_01:	.ascii " :: Base test:\0"
	LS_02:	.ascii " :: First variables:\0"
	LS_03:	.ascii " :: Reassigned variables:\0"
	LS_04:	.ascii " :: Math. prints:\0"
	LS_05:	.ascii " :: Math. variables:\0"
	LS_06:	.ascii " :: Math. prints with variables:\0"
	LS_07:	.ascii " :: Math. with variables and stored into variables:\0"
	LS_08:	.ascii " > c is now \0"
	LS_09:	.ascii " > But d is still \0"
	LS_10:	.ascii " :: Pointer Arithmetik:\0"
	LS_11:	.ascii "Hallo,\0"
	LS_12:	.ascii "Welt\0"
	LS_13:	.ascii " :: If Test ohne else aber mit Klammern:\0"
	LS_16:	.ascii "A ist valide\0"
	LS_19:	.ascii "A ist immer noch valide\0"
	LS_22:	.ascii "A ist 0\0"
	LS_23:	.ascii " :: If Test ohne else und ohne Klammern:\0"
	LS_26:	.ascii "a ist 2\0"
	LS_29:	.ascii "a ist nicht 3\0"
	LS_32:	.ascii "a muss 2 sein\0"
	LS_33:	.ascii "a = \0"
	LS_34:	.ascii " :: If Test mit Else: \0"
	LS_37:	.ascii "a ist kleiner als 2\0"
	LS_39:	.ascii "a ist nicht kleiner als 2\0"
	LS_42:	.ascii "a ist mehr als 2\0"
	LS_44:	.ascii "a ist nicht mehr als 2, sondern genau 2!\0"
	LS_45:	.ascii " :: While Loop Test\0"
	LS_49:	.ascii "i ist jetzt \0"
	LS_50:	.ascii "Und nun ist i = \0"
