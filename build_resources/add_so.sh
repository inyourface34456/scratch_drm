#!/bin/bash

set -e

# Ensure paths are relative to the working directory set in CMake (CMAKE_BINARY_DIR)

SO_TXT="libDRM.so"
SO_OBJ="libDRM.o"

# Convert hash.txt into linkable object
objcopy --rename-section .data=.rodata,alloc,load,readonly,data,contents --input binary --output elf64-x86-64 --binary-architecture i386:x86-64 "$SO_TXT" "$SO_OBJ"
