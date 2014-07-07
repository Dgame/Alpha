.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$4, %esp
movl	$7, 0(%esp)
movl	0(%esp), %ebx
movl	$8, %eax
cmpl	%ebx, %eax
je	L1
L2:
movl	0(%esp), %eax
pushl	%eax
movl	$1, %eax
subl	%eax, 0(%esp)
popl	%eax
movl	%eax, 0(%esp)
jmp	L1H
L1:
movl	0(%esp), %eax
pushl	%eax
movl	$1, %eax
addl	0(%esp), %eax
addl	$4, %esp
movl	%eax, 0(%esp)
L1H:
pushl	0(%esp)
call	_println_int
addl	$4, %esp
addl	$4, %esp
popl	%ebp
ret
