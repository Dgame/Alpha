.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$8, %esp
movl	$3, 0(%esp)
movl	$41, 4(%esp)
movl	4(%esp), %eax
movl	$0, %edx
movl	0(%esp), %ebx
idiv	%ebx
movl	%edx, %eax
pushl	%eax
call	_println_int
addl	$4, %esp
addl	$8, %esp
popl	%ebp
ret
