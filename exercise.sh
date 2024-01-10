#!/bin/bash

make -f Makefile_x86_64 clean
make -f Makefile_x86_64
./main

make -f Makefile_A32 clean
make -f Makefile_A32
./main

make -f Makefile_A64 clean
make -f Makefile_A64
./main

