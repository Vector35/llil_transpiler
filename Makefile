#all: gcd_test

x64:
	gcc -O0 -c tests.c -o tests.o
	ildump2cpp.py tests.o > tests_il.cpp
	g++ -g -O0 --std=c++11 -DARCH_X64 -DLEADING_UNDERSCORE tests_il.cpp main.cpp runtime.cpp -o main

NDK = $(HOME)/android-ndk-r15c
SYSR = $(NDK)/platforms/android-23/arch-arm
GCC = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc

arm:
	$(HOME)/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc -march=armv7-a -O0 -c tests.c -o tests.o
	ildump2cpp.py tests.o arm > tests_il.cpp
	g++ -g -O0 --std=c++11 -DARCH_ARM tests_il.cpp main.cpp runtime.cpp -o main
