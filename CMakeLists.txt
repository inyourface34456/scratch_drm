cmake_minimum_required(VERSION 3.31)
project(scratch_drm)

set(CMAKE_CXX_STANDARD 20)

add_executable(scratch_drm main.cpp
        drm.cpp)

add_custom_command(
        TARGET scratch_drm
        POST_BUILD
        COMMAND /bin/bash ${CMAKE_SOURCE_DIR}/add_hash.sh # Path to your script
        COMMENT "Running post-build script..."
)

