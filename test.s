.text
.globl	_alpha_main
.def	_alpha_main

_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$60, %esp
# Begin print
	pushl	$LS_00001
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
	pushl	$LS_00002
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
	pushl	$LS_00003
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
	pushl	$LS_00004
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
	pushl	$LS_00005
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
	pushl	$LS_00006
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
	pushl	$LS_00007
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
	pushl	$LS_00008
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
	pushl	$LS_00009
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
	pushl	$LS_00010
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
	pushl	$LS_00011
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_00012
	call	_println_string
	addl	$4, %esp
# End print
# Begin print
	pushl	$LS_00013
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
	je		LE_00015
LI_00014:
# Begin print
	pushl	$LS_00016
	call	_println_string
	addl	$4, %esp
# End print
LE_00015:
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
	je		LE_00018
LI_00017:
# Begin print
	pushl	$LS_00019
	call	_println_string
	addl	$4, %esp
# End print
LE_00018:
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
	jne		LE_00021
LI_00020:
# Begin print
	pushl	$LS_00022
	call	_println_string
	addl	$4, %esp
# End print
LE_00021:
# End if
# Begin print
	pushl	$LS_00023
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
	jne		LE_00025
LI_00024:
# Begin print
	pushl	$LS_00026
	call	_println_string
	addl	$4, %esp
# End print
LE_00025:
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
	je		LE_00028
LI_00027:
# Begin print
	pushl	$LS_00029
	call	_println_string
	addl	$4, %esp
# End print
LE_00028:
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
	jle		LE_00031
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$3, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jge		LE_00031
LI_00030:
# Begin print
	pushl	$LS_00032
	call	_println_string
	addl	$4, %esp
# End print
LE_00031:
# End if
# Begin print
	pushl	$LS_00033
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
	pushl	$LS_00034
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
	jge		LE_00036
LI_00035:
# Begin print
	pushl	$LS_00037
	call	_println_string
	addl	$4, %esp
# End print
LE_00036:
# Begin else
# Begin print
	pushl	$LS_00039
	call	_println_string
	addl	$4, %esp
# End print
LEND_00038:
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
	jle		LE_00041
LI_00040:
# Begin print
	pushl	$LS_00042
	call	_println_string
	addl	$4, %esp
# End print
LE_00041:
# Begin else
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$2, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LEND_00043
# Begin print
	pushl	$LS_00044
	call	_println_string
	addl	$4, %esp
# End print
LEND_00043:
# End else
# End if
# Begin print
	pushl	$LS_00045
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
	movl	$4, 32(%esp)
# End Var 
# Begin while
LWL_00046:
# Begin VarExpr 
	movl	32(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jle		LLE_00048
LLB_00047:
# Begin Loop
	decl	32(%esp)
# Begin print
	pushl	$LS_00049
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
	jmp		LWL_00046
LLE_00048:
# End while
# Begin print
	pushl	$LS_00050
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
# Begin print
	pushl	$LS_00051
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
	movl	$24, 0(%esp)
# End Var 
# Begin Var 
	movl	$4, 4(%esp)
# End Var 
# Begin Var 
	movl	$5, 8(%esp)
# End Var 
# Begin print
# Begin DivOp 
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin ModOp 
# Begin DivOp 
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	movl	%edx, %eax
# End ModOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin print
# Begin MulOp 
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	imull	4(%esp), %eax
# End MulOp 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin Var 
# Begin DivOp 
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	movl	%eax, 36(%esp)
# End Var 
# Begin print
	pushl	$LS_00052
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
	pushl	$LS_00053
	call	_print_string
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
	pushl	$LS_00054
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	36(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin Var 
# Begin ModOp 
# Begin DivOp 
# Begin VarExpr 
	movl	8(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	movl	%edx, %eax
# End ModOp 
	movl	%eax, 40(%esp)
# End Var 
# Begin print
	pushl	$LS_00055
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
	pushl	$LS_00056
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
	pushl	$LS_00057
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	40(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
# Begin if
# Begin ModOp 
# Begin DivOp 
# Begin VarExpr 
	movl	4(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	0(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	movl	%edx, %eax
# End ModOp 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LE_00059
LI_00058:
# Begin print
	pushl	$LS_00060
	call	_println_string
	addl	$4, %esp
# End print
LE_00059:
# End if
# Begin print
	pushl	$LS_00061
	call	_println_string
	addl	$4, %esp
# End print
# Begin Var 
	movl	$2, 44(%esp)
# End Var 
# Begin while
LWL_00062:
# Begin VarExpr 
	movl	44(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$100, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jge		LLE_00064
LLB_00063:
# Begin Loop
# Begin Var 
	movl	$2, 48(%esp)
# End Var 
# Begin Var 
	movl	$1, 52(%esp)
# End Var 
# Begin while
LWL_00065:
# Begin VarExpr 
	movl	48(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	44(%esp), %eax
# End VarExpr 
	cmpl	%eax, %ebx
	jge		LLE_00067
LLB_00066:
# Begin Loop
# Begin if
# Begin ModOp 
# Begin DivOp 
# Begin VarExpr 
	movl	48(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin VarExpr 
	movl	44(%esp), %eax
# End VarExpr 
	movl	$0, %edx
	idivl	%ebx
# End DivOp 
	movl	%edx, %eax
# End ModOp 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	jne		LE_00069
LI_00068:
# Begin Var 
	movl	$0, 52(%esp)
# End Var 
LE_00069:
# End if
	incl	48(%esp)
# End Loop
	jmp		LWL_00065
LLE_00067:
# End while
# Begin if
# Begin VarExpr 
	movl	52(%esp), %eax
# End VarExpr 
	movl	%eax, %ebx
# Begin NumExpr 
	movl	$0, %eax
# End NumExpr 
	cmpl	%eax, %ebx
	je		LE_00071
LI_00070:
# Begin print
	pushl	$LS_00072
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	44(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
LE_00071:
# End if
	incl	44(%esp)
# End Loop
	jmp		LWL_00062
LLE_00064:
# End while
# Begin Var 
	movl	$42, 56(%esp)
# End Var 
# Begin print
	pushl	$LS_00073
	call	_print_string
	addl	$4, %esp
# End print
# Begin print
# Begin VarExpr 
	movl	56(%esp), %eax
# End VarExpr 
	pushl	%eax
	call	_println_int
	addl	$4, %esp
# End print
	addl	$60, %esp
	popl	%ebp
	ret
.data
	LS_00001:	.ascii " :: Base test:\0"
	LS_00002:	.ascii " :: First variables:\0"
	LS_00003:	.ascii " :: Reassigned variables:\0"
	LS_00004:	.ascii " :: Math. prints:\0"
	LS_00005:	.ascii " :: Math. variables:\0"
	LS_00006:	.ascii " :: Math. prints with variables:\0"
	LS_00007:	.ascii " :: Math. with variables and stored into variables:\0"
	LS_00008:	.ascii " > c is now \0"
	LS_00009:	.ascii " > But d is still \0"
	LS_00010:	.ascii " :: Pointer Arithmetik:\0"
	LS_00011:	.ascii "Hallo,\0"
	LS_00012:	.ascii "Welt\0"
	LS_00013:	.ascii " :: If Test ohne else aber mit Klammern:\0"
	LS_00016:	.ascii "A ist valide\0"
	LS_00019:	.ascii "A ist immer noch valide\0"
	LS_00022:	.ascii "A ist 0\0"
	LS_00023:	.ascii " :: If Test ohne else und ohne Klammern:\0"
	LS_00026:	.ascii "a ist 2\0"
	LS_00029:	.ascii "a ist nicht 3\0"
	LS_00032:	.ascii "a muss 2 sein\0"
	LS_00033:	.ascii "a = \0"
	LS_00034:	.ascii " :: If Test mit Else: \0"
	LS_00037:	.ascii "a ist kleiner als 2\0"
	LS_00039:	.ascii "a ist nicht kleiner als 2\0"
	LS_00042:	.ascii "a ist mehr als 2\0"
	LS_00044:	.ascii "a ist nicht mehr als 2, sondern genau 2!\0"
	LS_00045:	.ascii " :: While Loop Test\0"
	LS_00049:	.ascii "i ist jetzt \0"
	LS_00050:	.ascii "Und nun ist i = \0"
	LS_00051:	.ascii " :: Div, Mod und Mul:\0"
	LS_00052:	.ascii "div: a = \0"
	LS_00053:	.ascii ", b = \0"
	LS_00054:	.ascii ", j = \0"
	LS_00055:	.ascii "mod: a = \0"
	LS_00056:	.ascii ", c = \0"
	LS_00057:	.ascii ", k = \0"
	LS_00060:	.ascii "a ist durch b ohne rest teilbar\0"
	LS_00061:	.ascii "Between 1 and 100 the following prime numbers exist:\0"
	LS_00072:	.ascii "Prime: \0"
	LS_00073:	.ascii "l = \0"
