.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
movl	$4, %eax
movl	$2, %ebx
movl	$0, %edx
idiv	%ebx
pushl	%eax
call	_println_int
addl	$4, %esp
popl	%ebp
ret
