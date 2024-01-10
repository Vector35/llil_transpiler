# LLIL Transpiler

Convert LLIL to compileable and executable C++.

**GOALS**:

* test lifting: accurate LLIL should compute like native code
* provide LLIL semantics - [runtime.cpp](./runtime.cpp) contains a C/C++ implementation for many LLIL operations

**QUICK START**: `make -f Makefile_x86_x64` `./main`

**EXAMPLE**: [transpiled A64](./assets/tests_il_A64.cpp)

## How does it work?

The LLIL gets mapped to C/C++ code:

| LLIL         | C/C++                                      |
| ------------ | ------------------------------------------ |
| LLIL_IF      | if                                         |
| LLIL_GOTO    | goto, with labels generated at every block |
| LLIL_CALL    | function call                              |
| LLIL_JUMP_TO | switch                                     |
| LLIL_REG     | `REG16()`, `REG32()`, `REG64()`, etc.      |
| LLIL_ADD     | `ADD16()`, `ADD32()`, `ADD64()`, etc.      |
| LLIL_XXX     | `XXX()`                                    |

See [ildump2cpp.py](./ildump2cpp.py) for the mapper, and [runtime.cpp](./runtime.cpp) for the C/C++ implementation of the LLIL operations.

## Workflow

1. compile tests.cpp into tests.o with the architecture you want to lift
2. extract the llil into tests\_il.cpp using ildump2cpp.py
3. compile tests\_il.cpp with runtime.cpp and main.cpp to main
4. `./main`

Using make: `make x64` or `make arm` then `./main`

## How can I test my own architecture?

1. atop runtime.h, do an `#ifdef ARCH_XXX` and inside define your arch's register types, etc.
2. in main.cpp, do an `#ifdef ARCH_XXX` and inside define `vm_init_stack()`, `vm_set_arg0()`, etc.
3. create a Makefile, being sure to pass `-DARCH_XXX`
4. run `./main`

## What else?

You could compile a routine in one architecture, transpile it's LLIL to C++, then compile the result to a new architecture.

You could do the above many times, even with the same architecture, increasing code size and obfuscation.
