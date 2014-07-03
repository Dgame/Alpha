.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$4, %esp
movl	$2, 0(%esp)
movl	0(%esp), %eax
pushl	%eax
movl	$4, %eax
subl	%eax, 0(%esp)
popl	%eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$4, %esp
popl	%ebp
ret
