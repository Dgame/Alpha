.text
.globl _prog
_prog:

pushl	%ebp
movl	%esp, %ebp
subl	$8, %esp
movl	$99, 0(%esp)
movl	$87, 4(%esp)
movl	0(%esp), %ebx
movl	$99, %eax
cmpl	%eax, %ebx
jne	L2
movl	4(%esp), %ebx
movl	$88, %eax
cmpl	%eax, %ebx
jne	L2
je	L1
L2:
movl	0(%esp), %eax
movl	%eax, 4(%esp)
jmp	L1H
L1:
movl	4(%esp), %eax
movl	%eax, 0(%esp)
L1H:
pushl	0(%esp)
call	_println_int
addl	$4, %esp
addl	$8, %esp
popl	%ebp
ret
