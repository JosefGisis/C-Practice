cmake_minimum_required(VERSION 3.20)
project(practice)

include_directories(include src)

# Recursively get ALL .c files from src/ and subdirectories
file(GLOB_RECURSE SOURCES "src/*.c")

# Create ONE executable with all the source files
add_executable(practice ${SOURCES})
