# LLIL Transpiler

Convert LLIL to C++ so that it can be compiled and executed.

quick start: `make x64` `./main`

The main motivation is to run tests that, when passed, increase confidence that lifting is accurate.

* run tests to increase confidence in lifting accuracy
* just an idea: convert routines between architectures
* just an idea: obfuscation

## How does it work?

* LLIL operations become function calls, like LLIL\_REG becomes REG(), LLIL\_PUSH becomes PUSH()
* LLIL_IF becomes C++'s if
* LLIL_GOTO becomes C++'s goto, and labels are generated for every block
* LLIL_CALL becomes a C++ function invocation
* LLIL_JUMP_TO becomes a C++ switch statement
* return is generated architecture dependent, like LLIL_RET in X64 LLIL_JUMP(LLIL_REG('lr')) in ARM
* all functions implementing LLIL ops are in runtime.cpp

So how do you actually do it?

1. compile tests.cpp into tests.o with the architecture want to lift
2. extract the llil into tests\_il.cpp using ildump2cpp.py
3. compile tests\_il.cpp with runtime.cpp and main\_x64.cpp (or your corresponding architecture)

See Makefile for all of this.

## What makes this difficult?

* PUSH() needs to reach into binja's knowledge and find what the stack pointer is, how much it should be decremented
* ADD() can take different types, and return different types
* REG() and SET\_REG() need architecture-specific knowledge, eg setting "eax" should affect "rax" too

## What else?

You could compile a routine in one architecture, transpile it's LLIL to C++, then compile the result to a new architecture.

You could do the above many times, even with the same architecture, increasing code size and obfuscation.
