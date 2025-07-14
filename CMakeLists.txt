cmake_minimum_required(VERSION 3.31)
project(scratch_drm)

set(CMAKE_CXX_STANDARD 20)

# Define path to the generated object file
set(HASH_OBJ ${CMAKE_BINARY_DIR}/hash.o)

# Custom command to generate the object file
add_custom_command(
        OUTPUT ${HASH_OBJ}
        COMMAND /bin/bash ${CMAKE_SOURCE_DIR}/add_hash.sh
        DEPENDS ${CMAKE_SOURCE_DIR}/add_hash.sh
        COMMENT "Running script to generate hash.o"
)

# Custom target that represents the object file
add_custom_target(generate_hash_obj ALL
        DEPENDS ${HASH_OBJ}
)

# Define your main executable without hash.o for now
add_executable(scratch_drm main.cpp drm.cpp)

# Ensure the object is built before the executable
add_dependencies(scratch_drm generate_hash_obj)

# Link the object file directly
target_link_libraries(scratch_drm PRIVATE ${HASH_OBJ})
