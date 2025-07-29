cmake_minimum_required(VERSION 3.31)
project(scratch_drm)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# Define path to the generated object file
set(HASH_OBJ ${CMAKE_BINARY_DIR}/hash.o)

# Custom command to generate the object file
add_custom_command(
        OUTPUT ${HASH_OBJ}
        COMMAND /bin/bash ${CMAKE_SOURCE_DIR}/build_resources/add_hash.sh
        DEPENDS ${CMAKE_SOURCE_DIR}/main.cpp
        DEPENDS ${CMAKE_SOURCE_DIR}/drm/drm.cpp
        BYPRODUCTS ${HASH_OBJ}
        COMMENT "Running script to generate hash.o"
)

# Custom target that represents the object file
add_custom_target(generate_hash_obj ALL
        DEPENDS ${HASH_OBJ}
)


add_library(DRM SHARED drm/drm.cpp)
# Define your main executable without hash.o for now
add_executable(scratch_drm main.cpp
#        drm/var_defs.h
        bougus_math.h)

# Ensure the object is built before the executable
add_dependencies(DRM generate_hash_obj)

# Link the object file directly
target_sources(DRM PRIVATE ${HASH_OBJ})
target_link_libraries(DRM OpenSSL::Crypto)