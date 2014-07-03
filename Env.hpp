#ifndef ENV_HPP
#define ENV_HPP

struct VarManager;
struct CommandManager;

struct Env {
	VarManager* vm = nullptr;
	CommandManager* cm = nullptr;
};

#endif