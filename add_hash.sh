#!/bin/bash

set -e

# Ensure paths are relative to the working directory set in CMake (CMAKE_BINARY_DIR)
INPUT_BIN="scratch_drm"
TEXT_BIN="text.txt"
HASH_TXT="hash.txt"
HASH_OBJ="hash.o"

# Extract .text section
objcopy -O binary -j .text "$INPUT_BIN" "$TEXT_BIN"

# Generate SHA-256 hash
sha256sum "$TEXT_BIN" | cut -d' ' -f1 | tr -d '\n'> "$HASH_TXT"

# Convert hash.txt into linkable object
objcopy --input binary --output elf64-x86-64 --binary-architecture i386:x86-64 "$HASH_TXT" "$HASH_OBJ"