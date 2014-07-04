.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
pushl	$42
call	_println_int
addl	$4, %esp
popl	%ebp
ret
