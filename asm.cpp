#include "asm.hpp"

#include <sstream>

Offset::Offset(i32_t the_offset, Ptr ptr) {
    std::stringstream buf;
    buf << the_offset << '(' << Pointer[ptr] << ')';

    _ident = buf.str();
}

Offset::Offset(i32_t the_offset, Reg reg) {
    std::stringstream buf;
    buf << the_offset << '(' << Register[reg] << ')';

    _ident = buf.str();
}

namespace gas {
    // push
    void push(std::ostream& out, int num) {
        out << "\tpush" << SUFFIX << "\t$" << num << std::endl; 
    }

    void push(std::ostream& out, Reg r) {
        out << "\tpush" << SUFFIX << "\t" << Register[r] << std::endl; 
    }

    void push(std::ostream& out, Offset o) {
        out << "\tpush" << SUFFIX << "\t" << o.getIdent() << std::endl; 
    }

    void push(std::ostream& out, Ptr p) {
        out << "\tpush" << SUFFIX << "\t" << Pointer[p] << std::endl; 
    }

    void push(std::ostream& out, const std::string& label) {
        out << "\tpush" << SUFFIX << "\t$" << label << std::endl;
    }

    // pop
    void pop(std::ostream& out, Reg r) {
        out << "\tpop" << SUFFIX << "\t" << Register[r] << std::endl; 
    }

    void pop(std::ostream& out, Offset o) {
        out << "\tpop" << SUFFIX << "\t" << o.getIdent() << std::endl; 
    }

    void pop(std::ostream& out, Ptr p) {
        out << "\tpop" << SUFFIX << "\t" << Pointer[p] << std::endl; 
    }

    // inc
    void inc(std::ostream& out, Reg r) {
        out << "\tinc" << SUFFIX << "\t" << Register[r] << std::endl; 
    }

    void inc(std::ostream& out, Offset o) {
        out << "\tinc" << SUFFIX << "\t" << o.getIdent() << std::endl; 
    }

    // dec
    void dec(std::ostream& out, Reg r) {
        out << "\tdec" << SUFFIX << "\t" << Register[r] << std::endl; 
    }

    void dec(std::ostream& out, Offset o) {
        out << "\tdec" << SUFFIX << "\t" << o.getIdent() << std::endl; 
    }

    // mov
    void mov(std::ostream& out, int num, Reg r) {
        out << "\tmov" << SUFFIX << "\t$" << num << ", " << Register[r] << std::endl; 
    }

    void mov(std::ostream& out, int num, Offset o) {
        out << "\tmov" << SUFFIX << "\t$" << num << ", " << o.getIdent() << std::endl; 
    }

    void mov(std::ostream& out, const std::string& label, Reg r) {
        out << "\tmovl" << SUFFIX << "\t$" << label <<", " << Register[r] << std::endl;
    }

    void mov(std::ostream& out, const std::string& label, Offset o) {
        out << "\tmovl" << SUFFIX << "\t$" << label <<", " << o.getIdent() << std::endl;
    }

    void mov(std::ostream& out, Reg r1, Reg r2) {
        out << "\tmov" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl; 
    }

    void mov(std::ostream& out, Reg r, Offset o) {
        out << "\tmov" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl; 
    }

    void mov(std::ostream& out, Offset o, Reg r) {
        out << "\tmov" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl; 
    }

    void mov(std::ostream& out, Ptr p1, Ptr p2) {
        out << "\tmov" << SUFFIX << "\t" << Pointer[p1] << ", " << Pointer[p2] << std::endl; 
    }

    // add
    void add(std::ostream& out, int num, Ptr p) {
        out << "\tadd" << SUFFIX << "\t$" << num << ", " << Pointer[p] << std::endl;
    }

    void add(std::ostream& out, int num, Reg r) {
        out << "\tadd" << SUFFIX << "\t$" << num << ", " << Register[r] << std::endl;
    }

    void add(std::ostream& out, int num, Offset o) {
        out << "\tadd" << SUFFIX << "\t$" << num << ", " << o.getIdent() << std::endl;
    }

    void add(std::ostream& out, Reg r1, Reg r2) {
        out << "\tadd" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void add(std::ostream& out, Reg r, Offset o) {
        out << "\tadd" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    void add(std::ostream& out, Offset o, Reg r) {
        out << "\tadd" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }

    // sub
    void sub(std::ostream& out, int num, Ptr p) {
        out << "\tsub" << SUFFIX << "\t$" << num << ", " << Pointer[p] << std::endl;
    }

    void sub(std::ostream& out, int num, Reg r) {
        out << "\tsub" << SUFFIX << "\t$" << num << ", " << Register[r] << std::endl;
    }

    void sub(std::ostream& out, int num, Offset o) {
        out << "\tsub" << SUFFIX << "\t$" << num << ", " << o.getIdent() << std::endl;
    }

    void sub(std::ostream& out, Reg r1, Reg r2) {
        out << "\tsub" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void sub(std::ostream& out, Reg r, Offset o) {
        out << "\tsub" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    void sub(std::ostream& out, Offset o, Reg r) {
        out << "\tsub" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }

    // imul
    void imul(std::ostream& out, Reg r1, Reg r2) {
        out << "\timul" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl; 
    }

    void imul(std::ostream& out, Offset o, Reg r) {
        out << "\timul" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl; 
    }

    // idiv
    void idiv(std::ostream& out, Reg r) {
        out << "\tidiv" << SUFFIX << "\t" << Register[r] << std::endl; 
    }

    void idiv(std::ostream& out, Offset o) {
        out << "\tidiv" << SUFFIX << "\t" << o.getIdent() << std::endl; 
    }

    // lea
    void lea(std::ostream& out, Offset o, Reg r) {
        out << "\tlea" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl; 
    }

    // ret
    void ret(std::ostream& out) {
        out << "\tret" << std::endl;
    }

    // call
    void call(std::ostream& out, const std::string& label) {
        out << "\tcall\t" << label << std::endl;
    }

    // jmp
    void jmp(std::ostream& out, JCond jc, const std::string& label) {
        out << "\tj" << JumpPostFix[jc] << "\t\t" << label << std::endl;
    }

    // cmp
    void cmp(std::ostream& out, int num, Reg r) {
        out << "\tcmp" << SUFFIX << "\t$" << num << ", " << Register[r] << std::endl;
    }

    void cmp(std::ostream& out, int num, Offset o) {
        out << "\tcmp" << SUFFIX << "\t$" << num << ", " << o.getIdent() << std::endl;
    }

    void cmp(std::ostream& out, Reg r1, Reg r2) {
        out << "\tcmp" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void cmp(std::ostream& out, Offset o, Reg r) {
        out << "\tcmp" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }

    void cmp(std::ostream& out, Reg r, Offset o) {
        out << "\tcmp" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    // neg
    void neg(std::ostream& out, Reg r) {
        out << "\tneg" << SUFFIX << "\t" << Register[r] << std::endl;
    }

    void neg(std::ostream& out, Offset o) {
        out << "\tneg" << SUFFIX << "\t" << o.getIdent() << std::endl;
    }

    // not
    void logic_not(std::ostream& out, Reg r) {
        out << "\tnot" << SUFFIX << "\t" << Register[r] << std::endl;
    }

    void logic_not(std::ostream& out, Offset o) {
        out << "\tnot" << SUFFIX << "\t" << o.getIdent() << std::endl;
    }

    // and
    void logic_and(std::ostream& out, Reg r1, Reg r2) {
        out << "\tand" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void logic_and(std::ostream& out, Reg r, Offset o) {
        out << "\tand" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    void logic_and(std::ostream& out, Offset o, Reg r) {
        out << "\tand" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }

    // or
    void logic_or(std::ostream& out, Reg r1, Reg r2) {
        out << "\tor" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void logic_or(std::ostream& out, Reg r, Offset o) {
        out << "\tor" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    void logic_or(std::ostream& out, Offset o, Reg r) {
        out << "\tor" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }

    // xor
    void logic_xor(std::ostream& out, Reg r1, Reg r2) {
        out << "\txor" << SUFFIX << "\t" << Register[r1] << ", " << Register[r2] << std::endl;
    }

    void logic_xor(std::ostream& out, Reg r, Offset o) {
        out << "\txor" << SUFFIX << "\t" << Register[r] << ", " << o.getIdent() << std::endl;
    }

    void logic_xor(std::ostream& out, Offset o, Reg r) {
        out << "\txor" << SUFFIX << "\t" << o.getIdent() << ", " << Register[r] << std::endl;
    }
}