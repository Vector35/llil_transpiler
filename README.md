# LLIL Transpiler

Convert LLIL to C++ so that it can be compiled and executed.

quick start: `make x64` `./main`

The main motivation is to run tests that, when passed, increase confidence that lifting is accurate.

## How does it work?

* LLIL operations become function calls, like LLIL\_REG becomes REG(), LLIL\_PUSH becomes PUSH()
* LLIL_IF becomes C++'s if
* LLIL_GOTO becomes C++'s goto, and labels are generated for every block
* LLIL_CALL becomes a C++ function invocation
* LLIL_JUMP_TO becomes a C++ switch statement
* return is generated architecture dependent, like LLIL_RET in X64 LLIL_JUMP(LLIL_REG('lr')) in ARM
* all functions implementing LLIL ops are in runtime.cpp

So how do you actually do it?

1. compile tests.cpp into tests.o with the architecture you want to lift
2. extract the llil into tests\_il.cpp using ildump2cpp.py
3. compile tests\_il.cpp with runtime.cpp and main.cpp to main
4. `./main`

Using make: `make x64` or `make arm` then `./main`

## How can I test my own architecture?

1. atop runtime.h, do an `#ifdef ARCH_XXX` and inside define your arch's register types, etc.
2. in main.cpp, do an `#ifdef ARCH_XXX` and inside define `vm_init_stack()`, `vm_set_arg0()`, etc.
3. in the Makefile, create a new target that calls your arch's compiler to produce tests.o and passes -DARCH\_XXX
4. run `./main`

## What else?

You could compile a routine in one architecture, transpile it's LLIL to C++, then compile the result to a new architecture.

You could do the above many times, even with the same architecture, increasing code size and obfuscation.
