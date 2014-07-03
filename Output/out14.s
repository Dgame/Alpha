.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$4, %esp
movl	$2, 0(%esp)
movl	$4, %eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$4, %esp
popl	%ebp
ret
