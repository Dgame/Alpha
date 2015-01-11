OBJS = main.cpp \
		asm.cpp \
		Expr.cpp \
		VarDecl.cpp \
		Scope.cpp \
		Parser.cpp \
		Func.cpp \
		Decl.cpp \
		Labels.cpp \
		Env.cpp \
		Loc.cpp
	
CC = g++

COMPILER_WARNINGS = -Wall -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wmain -pedantic -Wzero-as-null-pointer-constant -Wextra
COMPILER_FLAGS = -std=c++1y
COMPILER_FLAGS_DEBUG = -g
COMPILER_FLAGS_RELEASE = -O3

OBJ_NAME = main

all:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_DEBUG) -o $(OBJ_NAME)
release:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_RELEASE) -o $(OBJ_NAME)