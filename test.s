.text
.globl  _alpha_main
.def    _alpha_main

_alpha_main:
        pushl   %ebp
        movl    %esp, %ebp
        subl    $16, %esp
# Begin print
        pushl   $42
        call    _print
        addl    $4, %esp
# End print
# Begin print
        pushl   $23
        call    _print
        addl    $4, %esp
# End print
# Begin Var
        movl    $42, 0(%esp)
# End Var
# Begin ByVal
        movl    0(%esp), %eax
        movl    %eax, 4(%esp)
# End ByVal
# Begin print
# Begin VarExpr
        movl    0(%esp), %eax
# End VarExpr
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin VarExpr
        movl    4(%esp), %eax
# End VarExpr
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin Var
        movl    $4, 8(%esp)
# End Var
# Begin Var
        movl    $2, 12(%esp)
# End Var
# Begin print
# Begin VarExpr
        movl    8(%esp), %eax
# End VarExpr
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin VarExpr
        movl    12(%esp), %eax
# End VarExpr
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin MulOp
# Begin NumExpr
        movl    $2, %eax
# End NumExpr
        pushl   %eax
# Begin NumExpr
        movl    $2, %eax
# End NumExpr
        imull   0(%esp), %eax
        addl    $4, %esp
# End MulOp
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin AddOp
# Begin NumExpr
        movl    $25, %eax
# End NumExpr
        pushl   %eax
# Begin NumExpr
        movl    $5, %eax
# End NumExpr
        addl    0(%esp), %eax
        addl    $4, %esp
# End AddOp
        pushl   %eax
        call    _print
        addl    $4, %esp
# End print
# Begin print
# Begin AddOp
# Begin NumExpr
        movl    $1, %eax
# End NumExpr
        pushl   %eax
# Begin MulOp
# Begin NumExpr
        movl    $2, %eax
# End NumExpr
        pushl   %eax
# Begin NumExpr
        movl    $3, %eax
# End NumExpr
        imull   0(%esp), %eax
        addl    $4, %esp
# End MulOp
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
