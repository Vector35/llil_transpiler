#all: gcd_test

CPPFLAGS = -g -O0 -std=c++11

x64:
	g++ $(CPPFLAGS) -c tests.cpp -o tests.o
	ildump2cpp.py tests.o > tests_il.cpp
	g++ $(CPPFLAGS) tests_il.cpp main_x64.cpp runtime.cpp -o main

NDK = $(HOME)/android-ndk-r15c
SYSR = $(NDK)/platforms/android-23/arch-arm
GCC = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc

arm:
	$(HOME)/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc -march=armv7-a $(CPPFLAGS) -c tests.cpp -o tests.o
	ildump2cpp.py tests.o arm > tests_il.cpp
	g++ $(CPPFLAGS) -DARCH_ARM tests_il.cpp main_arm.cpp runtime.cpp -o main


