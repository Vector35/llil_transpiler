#all: gcd_test

NDK = $(HOME)/android-ndk-r15c
SYSR = $(NDK)/platforms/android-23/arch-arm
GCC = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc

arm:
	$(HOME)/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc -march=armv7-a -O0 -c tests.c -o tests.o
	ildump2cpp.py tests.o arm > tests_il.cpp
	g++ -g -O0 --std=c++11 -DARCH_ARM -DARCH_32BIT tests_il.cpp main.cpp runtime.cpp -o main

z80:
	sdcc -mz80 -DARCH_Z80 tests.c
	sdcc2elf.py tests.ihx tests.map
	ildump2cpp.py tests.elf z80 > tests_il.cpp
	g++ -g -O0 --std=c++11 -DARCH_Z80 -DARCH_16BIT -DLEADING_UNDERSCORE tests_il.cpp main.cpp runtime.cpp -o main

# get ndk-r21d from https://developer.android.com/ndk/downloads
# unzip, cd to android/build/tools
# ./make_standalone_toolchain.py --arch arm64 --api 21 --install-dir ~/android_a64_api21_toolchain
BUILT_TOOLCHAIN = $(HOME)/android_a64_api21_toolchain
GCC = $(BUILT_TOOLCHAIN)/bin/aarch64-linux-android-gcc

tests.o: tests.c
	$(GCC) tests.c -c -o tests.o

tests_il.cpp: tests.o
	ildump2cpp.py tests.o a64 > tests_il.cpp

main: tests_il.cpp runtime.cpp main.cpp
	g++ -g -O0 --std=c++11 -DARCH_A64 -DARCH_64BIT tests_il.cpp main.cpp runtime.cpp -o main

a64: tests.o tests_il.cpp main

clean:
	rm -f *.o main tests_il.cpp
