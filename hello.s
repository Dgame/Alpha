.text
.globl	_alpha_main
_alpha_main:
	pushl	%ebp
	movl	%esp, %ebp
# Begin Scope
# Begin print
	pushl	$L_0_STR
	call	_print_str
	addl	$4, %esp
	call	_print_ln
# End print
# End Scope
	popl	%ebp
ret
L_0_STR:
	.ascii	"Hallo Welt\0"
