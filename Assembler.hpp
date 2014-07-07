#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "patch.hpp"

namespace as {
	enum class Reg : char {
		// Accu
		AX,
		AH,
		AL,
		// Base
		BX,
		BH,
		BL,
		// Counter
		CX,
		CH,
		CL,
		// Data
		DX,
		DH,
		DL
	};

	enum class Index : char {
		SI,
		BI
	};

	enum class Pointer : char {
		BP,
		SP,
		IP
	};

	enum class Control : char {
		OF,
		DF,
		IF,
		TF,
		SF,
		ZF,
		AF,
		PF,
		CF
	};

	enum class Cond : char {
		Always,
		Zero,
		Equal,
		NotZero,
		NotEqual,
		Greater,
		GreaterEqual,
		Less,
		LessEqual,
		Above,
		AboveEqual,
		NotAbove,
		Below,
		BelowEqual,
		NotBelow,
		Carry,
		NotCarry,
		Overflow,
		NotOverflow,
		Parity,
		ParityEven,
		NotParity,
		ParityOdd,
		Sign,
		NotSign
	};

	static const std::map<Cond, const std::string> ConditionStr = {
		{Cond::Always, "mp"},
		{Cond::Zero, "z"},
		{Cond::Equal, "e"},
		{Cond::NotZero, "nz"},
		{Cond::NotEqual, "ne"},
		{Cond::Greater, "g"},
		{Cond::GreaterEqual, "ge"},
		{Cond::Less, "l"},
		{Cond::LessEqual, "le"},
		{Cond::Above, "a"},
		{Cond::AboveEqual, "ae"},
		{Cond::NotAbove, "na"},
		{Cond::Below, "b"},
		{Cond::BelowEqual, "be"},
		{Cond::NotBelow, "nb"},
		{Cond::Carry, "c"},
		{Cond::NotCarry, "nc"},
		{Cond::Overflow, "o"},
		{Cond::NotOverflow, "no"},
		{Cond::Parity, "p"},
		{Cond::ParityEven, "pe"},
		{Cond::NotParity, "np"},
		{Cond::ParityOdd, "po"},
		{Cond::Sign, "s"},
		{Cond::NotSign, "ns"}
	};

	enum AsCommand {
		Push,
		Pop,
		Move,
		Add,
		Sub,
		Mul,
		Div,
		Neg,
		Comp,
		Call,
		Ret,
		And,
		Or,
		Xor,
		Not,
		Jump,
		Inc,
		Dec
	};

	static const std::vector<std::string> CommandStr = {
		"pushl",
		"popl",
		"movl",
		"addl",
		"subl",
		"imull",
		"idiv",
		"negl",
		"cmpl",
		"call",
		"ret",
		"and",
		"or",
		"xor",
		"not",
		"j",
		"inc",
		"dec"
	};

	enum class Operand : char {
		String,
		Numeric,
		Register,
		Index,
		Pointer,
		AddrOf,
		Flag
	};

	enum class OpPair : char {
		NR, // Numeric;Register
		RN, // Register;Numeric
		RR, // Register;Register
		PP, // Pointer;Pointer
		AA, // AddrOf;AddrOf
		RA, // Register;AddrOf
		AR, // AddrOf;Register
		NA, // Numeric;AddrOf
		AN, // AddrOf;Numeric
		PN, // Pointer;Numeric
		NP  // Numeric;Pointer
	};

	static const std::map<OpPair, const std::pair<Operand, Operand>> Accept = {
		{OpPair::NR, std::make_pair(Operand::Numeric, Operand::Register)},
		{OpPair::RR, std::make_pair(Operand::Register, Operand::Register)},
		{OpPair::PP, std::make_pair(Operand::Pointer, Operand::Pointer)},
		{OpPair::AA, std::make_pair(Operand::AddrOf, Operand::AddrOf)},
		{OpPair::RA, std::make_pair(Operand::Register, Operand::AddrOf)},
		{OpPair::AR, std::make_pair(Operand::AddrOf, Operand::Register)},
		{OpPair::NA, std::make_pair(Operand::Numeric, Operand::AddrOf)},
		{OpPair::PN, std::make_pair(Operand::Pointer, Operand::Numeric)},
		{OpPair::NP, std::make_pair(Operand::Numeric, Operand::Pointer)},
	};

	static inline bool checkPair(OpPair op, Operand o1, Operand o2) {
		auto& pair = Accept.at(op);

		return pair.first == o1 && pair.second == o2;
	}

#define		BIT_16		0
#define		BIT_32		1
#define		BIT_64		0
#define		GAS			1

#if GAS
	static const std::string RegPrefix = "%";
	static const char NumPrefix = '$';
#endif

#if BIT_16
	static const std::string Prefix = RegPrefix;
#elif BIT_32
	static const std::string Prefix = RegPrefix + "e";
#elif BIT_64
	static const std::string Prefix = RegPrefix + "r";
#endif

	static const std::map<Reg, const std::string> RegisterStr = {
		{Reg::AX, Prefix 	+ "ax"},
		{Reg::AH, RegPrefix + "ah"},
		{Reg::AL, RegPrefix + "al"},

		{Reg::BX, Prefix 	+ "bx"},
		{Reg::BH, RegPrefix + "bh"},
		{Reg::BL, RegPrefix + "bx"},

		{Reg::CX, Prefix 	+ "cx"},
		{Reg::CH, RegPrefix + "ch"},
		{Reg::CL, RegPrefix + "cl"},

		{Reg::DX, Prefix 	+ "dx"},
		{Reg::DH, RegPrefix + "dh"},
		{Reg::DL, RegPrefix + "dl"}
	};

	static const std::map<Index, const std::string> IndexStr = {
		{Index::SI, Prefix + "si"},
		{Index::BI, Prefix + "bi"}
	};

	static const std::map<Pointer, const std::string> PointerStr = {
		{Pointer::BP, Prefix + "bp"},
		{Pointer::SP, Prefix + "sp"},
		{Pointer::IP, Prefix + "ip"}
	};

	static inline std::string addrOf(Pointer ptr, int offset) {
		return patch::to_string(offset) + '(' + PointerStr.at(ptr) + ')';
	}

	struct Assembler {
		std::ostream* out = nullptr;
		AsCommand cmd;

		explicit Assembler(std::ostream& out, AsCommand cmd);

		// ret
		virtual void visit();
		// push
		virtual void visit(int num);
		// push, pop
		virtual void visit(Reg reg);
		// move
		virtual void visit(int num, Reg reg);
		// compare
		virtual void visit(Reg reg, int num);
		// move
		virtual void visit(Reg r1, Reg r2);
		// move
		virtual void visit(Reg reg, Pointer ptr, int offset);
		// move
		virtual void visit(Pointer ptr, int offset, Reg reg);
		// push, pop
		virtual void visit(Pointer ptr);
		// push, pop
		virtual void visit(Pointer ptr, int offset);
		// move
		virtual void visit(Pointer p1, Pointer p2);
		// move
		virtual void visit(int num, Pointer ptr, int offset);
		// add, sub
		virtual void visit(int num, Pointer ptr);
		// move
		virtual void visit(Pointer p1, int off1, Pointer p2, int off2);
		// call, jump
		virtual void visit(const std::string& label) const;
		// jump
		virtual void visit(Cond cond, const std::string& label) const;

		virtual bool accept() const {
			return false;
		}

		virtual bool accept(Operand) const {
			return false;
		}

		virtual bool accept(Operand, Operand) const {
			return false;
		}

		virtual void error() const {
			std::cerr << "Error: Invalid use of operands." << std::endl;
		}
	};

	struct AsPush : public Assembler {
		explicit AsPush(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Numeric || o1 == Operand::Pointer 
				|| o1 == Operand::Register || o1 == Operand::AddrOf;
		}
	};

	struct AsPop : public Assembler {
		explicit AsPop(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Pointer || o1 == Operand::Register || o1 == Operand::AddrOf;
		}
	};

	struct AsMove : public Assembler {
		explicit AsMove(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::NR, o1, o2)
				|| checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::PP, o1, o2)
				|| checkPair(OpPair::NA, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AR, o1, o2);
		}
	};

	struct AsAdd : public Assembler {
		explicit AsAdd(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AR, o1, o2)
				|| checkPair(OpPair::NA, o1, o2)
				|| checkPair(OpPair::PN, o1, o2)
				|| checkPair(OpPair::NP, o1, o2);
		}
	};

	struct AsSub : public Assembler {
		explicit AsSub(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AR, o1, o2)
				|| checkPair(OpPair::NA, o1, o2)
				|| checkPair(OpPair::PN, o1, o2)
				|| checkPair(OpPair::NP, o1, o2);
		}
	};

	struct AsMul : public Assembler {
		explicit AsMul(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::NR, o1, o2)
				|| checkPair(OpPair::NA, o1, o2)
				|| checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AR, o1, o2)
				|| checkPair(OpPair::AA, o1, o2);
		}
	};

	struct AsDiv : public Assembler {
		explicit AsDiv(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Register;
		}
	};

	struct AsNeg : public Assembler {
		explicit AsNeg(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Register || o1 == Operand::AddrOf;
		}
	};

	struct AsCompare : public Assembler {
		explicit AsCompare(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::RN, o1, o2)
				|| checkPair(OpPair::AN, o1, o2)
				|| checkPair(OpPair::AA, o1, o2);
		}
	};

	struct AsCall : public Assembler {
		explicit AsCall(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::String;
		}
	};

	struct AsRet : public Assembler {
		explicit AsRet(std::ostream& out);

		bool accept() const override {
			return true;
		}
	};

	struct AsAnd : public Assembler {
		explicit AsAnd(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AA, o1, o2);
		}
	};

	struct AsOr : public Assembler {
		explicit AsOr(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AA, o1, o2);
		}
	};

	struct AsXor : public Assembler {
		explicit AsXor(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return checkPair(OpPair::RR, o1, o2)
				|| checkPair(OpPair::RA, o1, o2)
				|| checkPair(OpPair::AA, o1, o2);
		}
	};

	struct AsNot : public Assembler {
		explicit AsNot(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Register || o1 == Operand::AddrOf;
		}
	};

	struct AsJump : public Assembler {
		explicit AsJump(std::ostream& out);

		bool accept(Operand o1, Operand o2) const override {
			return o1 == Operand::Flag && o2 == Operand::String;
		}
	};

	struct AsInc : public Assembler {
		explicit AsInc(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Register;
		}
	};

	struct AsDec : public Assembler {
		explicit AsDec(std::ostream& out);

		bool accept(Operand o1) const override {
			return o1 == Operand::Register;
		}
	};

	static std::ostream& output = std::cout;

	//TODO: In Composite kapseln?
	static const std::vector<std::shared_ptr<Assembler>> AsCommands = {
		std::make_shared<AsPush>(output),
		std::make_shared<AsPop>(output),
		std::make_shared<AsMove>(output),
		std::make_shared<AsAdd>(output),
		std::make_shared<AsSub>(output),
		std::make_shared<AsMul>(output),
		std::make_shared<AsDiv>(output),
		std::make_shared<AsNeg>(output),
		std::make_shared<AsCompare>(output),
		std::make_shared<AsCall>(output),
		std::make_shared<AsRet>(output),
		std::make_shared<AsAnd>(output),
		std::make_shared<AsOr>(output),
		std::make_shared<AsXor>(output),
		std::make_shared<AsNot>(output),
		std::make_shared<AsJump>(output),
		std::make_shared<AsInc>(output),
		std::make_shared<AsDec>(output)
	};

	template <typename... Args>
	inline void build(AsCommand as_cmd, Args&&... args) {
		AsCommands.at(as_cmd)->visit(std::forward<Args>(args)...);
	}

	inline void start(const std::string& label) {
		output << ".text\n.globl " << label << "\n" << label << ":\n" << std::endl;
	}

	inline void label(const std::string& label) {
		output << label << ':' << std::endl;
	}
}