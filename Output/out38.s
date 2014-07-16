.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$8, %esp
movl	$5, 0(%esp)
movl	$6, 4(%esp)
addl	$8, %esp
popl	%ebp
ret
