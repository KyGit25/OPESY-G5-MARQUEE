cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OS_Emulator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(os_emulator
    src/main.cpp
    src/command_interpreter.cpp
    src/display.cpp
    src/marquee.cpp
    src/menu.cpp
    src/utils.cpp
)

# Include directories
include_directories(src)