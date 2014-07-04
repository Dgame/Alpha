.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$12, %esp
movl	$4, 0(%esp)
movl	$2, 4(%esp)
movl	0(%esp), %eax
movl	$0, %edx
movl	4(%esp), %ebx
idiv	%ebx
movl	%eax, 8(%esp)
movl	8(%esp), %eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$12, %esp
popl	%ebp
ret
