.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$16, %esp
addl	$16, %esp
popl	%ebp
ret
