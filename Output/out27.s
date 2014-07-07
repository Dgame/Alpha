.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$4, %esp
movl	$7, 0(%esp)
movl	0(%esp), %ebx
movl	$7, %eax
cmpl	%eax, %ebx
je	L1
jmp	L1H
L1:
movl	$1, %eax
addl	0(%esp), %eax
movl	%eax, 0(%esp)
L1H:
pushl	0(%esp)
call	_println_int
addl	$4, %esp
addl	$4, %esp
popl	%ebp
ret
