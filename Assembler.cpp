#include "Assembler.hpp"

namespace as {
	Assembler::Assembler(std::ostream& out, AsCommand cmd) {
		this->out = &out;
		this->cmd = cmd;
	}

	// ret
	void Assembler::visit() {
		if (!this->accept())
			return this->error();

		*out << CommandStr.at(this->cmd) << std::endl;
	}

	// push
	void Assembler::visit(int num) {
		if (!this->accept(Operand::Numeric))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << NumPrefix << patch::to_string(num) << std::endl;
	}

	// push, pop
	void Assembler::visit(Reg reg) {
		if (!this->accept(Operand::Register))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << RegisterStr.at(reg) << std::endl;
	}

	// move
	void Assembler::visit(int num, Reg reg) {
		if (!this->accept(Operand::Numeric, Operand::Register))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << NumPrefix << patch::to_string(num) << ", " << RegisterStr.at(reg) << std::endl;
	}

	// move
	void Assembler::visit(Reg r1, Reg r2) {
		if (!this->accept(Operand::Register, Operand::Register))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << RegisterStr.at(r1) << ", " << RegisterStr.at(r2) << std::endl;
	}

	// move
	void Assembler::visit(Reg reg, Pointer ptr, int offset) {
		if (!this->accept(Operand::Register, Operand::AddrOf))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << RegisterStr.at(reg) << ", " << addrOf(ptr, offset) << std::endl;
	}

	void Assembler::visit(Pointer ptr, int offset, Reg reg) {
		if (!this->accept(Operand::AddrOf, Operand::Register))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << addrOf(ptr, offset) << ", " << RegisterStr.at(reg) << std::endl;
	}

	// push, pop
	void Assembler::visit(Pointer ptr) {
		if (!this->accept(Operand::Pointer))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << PointerStr.at(ptr) << std::endl;
	}

	// push, pop
	void Assembler::visit(Pointer ptr, int offset) {
		if (!this->accept(Operand::AddrOf))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << addrOf(ptr, offset) << std::endl;
	}

	void Assembler::visit(Pointer p1, Pointer p2) {
		if (!this->accept(Operand::Pointer, Operand::Pointer))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << PointerStr.at(p1) << ", " << PointerStr.at(p2) << std::endl;
	}

	// move
	void Assembler::visit(int num, Pointer ptr, int offset) {
		if (!this->accept(Operand::Numeric, Operand::AddrOf))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << NumPrefix << patch::to_string(num) << ", " << addrOf(ptr, offset) << std::endl;
	}

	void Assembler::visit(int num, Pointer ptr) {
		if (!this->accept(Operand::Numeric, Operand::Pointer))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << NumPrefix << patch::to_string(num) << ", " << PointerStr.at(ptr) << std::endl;
	}

	void Assembler::visit(Pointer p1, int off1, Pointer p2, int off2) {
		if (!this->accept(Operand::AddrOf, Operand::AddrOf))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << addrOf(p1, off1) << ", " << addrOf(p2, off2) << std::endl;
	}

	void Assembler::visit(const std::string& label) const {
		if (!this->accept(Operand::String))
			return this->error();

		*out << CommandStr.at(this->cmd) << "\t" << label << std::endl;
	}

	void Assembler::visit(Cond cond, const std::string& label) const {
		if (!this->accept(Operand::Flag, Operand::String))
			return this->error();

		*out << CommandStr.at(this->cmd) << ConditionStr.at(cond) << "\t" << label << std::endl;
	}

	AsPush::AsPush(std::ostream& out) : Assembler(out, AsCommand::Push) {

	}

	AsPop::AsPop(std::ostream& out) : Assembler(out, AsCommand::Pop) {

	}

	AsMove::AsMove(std::ostream& out) : Assembler(out, AsCommand::Move) {

	}

	AsAdd::AsAdd(std::ostream& out) : Assembler(out, AsCommand::Add) {

	}

	AsSub::AsSub(std::ostream& out) : Assembler(out, AsCommand::Sub) {

	}

	AsMul::AsMul(std::ostream& out) : Assembler(out, AsCommand::Mul) {

	}

	AsDiv::AsDiv(std::ostream& out) : Assembler(out, AsCommand::Div) {

	}

	AsNeg::AsNeg(std::ostream& out) : Assembler(out, AsCommand::Neg) {

	}

	AsCompare::AsCompare(std::ostream& out) : Assembler(out, AsCommand::Comp) {

	}

	AsCall::AsCall(std::ostream& out) : Assembler(out, AsCommand::Call) {

	}

	AsRet::AsRet(std::ostream& out) : Assembler(out, AsCommand::Ret) {

	}

	AsAnd::AsAnd(std::ostream& out) : Assembler(out, AsCommand::And) {

	}

	AsOr::AsOr(std::ostream& out) : Assembler(out, AsCommand::Or) {

	}

	AsXor::AsXor(std::ostream& out) : Assembler(out, AsCommand::Xor) {

	}

	AsNot::AsNot(std::ostream& out) : Assembler(out, AsCommand::Not) {

	}

	AsJump::AsJump(std::ostream& out) : Assembler(out, AsCommand::Jump) {

	}

	AsInc::AsInc(std::ostream& out) : Assembler(out, AsCommand::Inc) {

	}

	AsDec::AsDec(std::ostream& out) : Assembler(out, AsCommand::Dec) {
		
	}
}