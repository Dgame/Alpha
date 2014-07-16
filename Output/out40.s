.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$16, %esp
movl	$1, 0(%esp)
movl	$2, 4(%esp)
movl	$3, 8(%esp)
movl	$4, 12(%esp)
movl	$42, 4(%esp)
movl	$23, 12(%esp)
movl	4(%esp), %eax
addl	12(%esp), %eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$16, %esp
popl	%ebp
ret
