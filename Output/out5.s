.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
movl	$6, %eax
pushl	%eax
movl	$4, %eax
pushl	%eax
call	_println_int
addl	$4, %esp
popl	%ebp
ret
