.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
movl	$6, %eax
movl	$4, %ebx
movl	$0, %edx
idiv	%ebx
movl	%edx, %eax
pushl	%eax
call	_println_int
addl	$4, %esp
popl	%ebp
ret
