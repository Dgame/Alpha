.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$8, %esp
movl	$2, 0(%esp)
movl	$42, 4(%esp)
movl	0(%esp), %eax
imull	4(%esp), %eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$8, %esp
popl	%ebp
ret
