#ifndef ENV_HPP
#define ENV_HPP

struct VarManager;
struct CommandManager;
struct ScopeManager;

struct Env {
	VarManager* vm = nullptr;
	CommandManager* cm = nullptr;
	ScopeManager* sm = nullptr;
};

#endif