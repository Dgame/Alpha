#ifndef ENV_HPP
#define ENV_HPP

struct VarManager;
struct CommandManager;
struct Scopes;

struct Env {
	VarManager* vm = nullptr;
	CommandManager* cm = nullptr;
	Scopes* scope = nullptr;
};

#endif