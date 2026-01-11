cmake_minimum_required(VERSION 3.10)
project(arg-parser C)

set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(include)

# Source files
set(SOURCES
        src/main.c
        src/parse-args.c
)

# Create executable
add_executable(arg-parser ${SOURCES})