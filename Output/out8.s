.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
movl	$2, %eax
pushl	%eax
movl	$3, %eax
imull	0(%esp), %eax
addl	$4, %esp
pushl	%eax
movl	$4, %eax
subl	%eax, 0(%esp)
popl	%eax
pushl	%eax
movl	$6, %eax
pushl	%eax
movl	$2, %eax
imull	0(%esp), %eax
addl	$4, %esp
addl	0(%esp), %eax
addl	$4, %esp
pushl	%eax
call	_println_int
addl	$4, %esp
popl	%ebp
ret
