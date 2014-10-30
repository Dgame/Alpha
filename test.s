.text
.globl  _alpha_main
.def    _alpha_main

_alpha_main:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp
# Begin Var
        movl    $42, 0(%esp)
# End Var
# Begin Var
        movl    0(%esp), %eax
        movl    %eax, 4(%esp)
# End Var
# Begin Ptr
        leal    4(%esp), %eax
        movl    %eax, 8(%esp)
# End Ptr
# Begin Ptr
        movl    8(%esp), %eax
        movl    0(%eax), %eax
        movl    %eax, 12(%esp)
# End Ptr
# Begin print
        pushl   0(%esp)
        call    _print
        addl    $4, %esp
# End print
# Begin print
        pushl   4(%esp)
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin MulOp
# Begin NumExpr
        movl    $2, %eax
# End NumExpr
        pushl   %eax
# Begin AddOp
# Begin NumExpr
        movl    $4, %eax
# End NumExpr
        pushl   %eax
# Begin NumExpr
        movl    $8, %eax
# End NumExpr
        addl    0(%esp), %eax
        addl    $4, %esp
# End AddOp
        imull   0(%esp), %eax
        addl    $4, %esp
# End MulOp
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin AddOp
# Begin MulOp
# Begin NumExpr
        movl    $2, %eax
# End NumExpr
        pushl   %eax
# Begin NumExpr
        movl    $4, %eax
# End NumExpr
        imull   0(%esp), %eax
        addl    $4, %esp
# End MulOp
        pushl   %eax
# Begin NumExpr
        movl    $8, %eax
# End NumExpr
        addl    0(%esp), %eax
        addl    $4, %esp
# End AddOp
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
        addl    $16, %esp
        popl    %ebp
        ret
