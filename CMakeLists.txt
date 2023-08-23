cmake_minimum_required(VERSION 3.23)
project(6502)

set(CMAKE_CXX_STANDARD 17)

add_executable(6502 6502.cpp 6502.h cpu_6502.cpp cpu_6502.h mem_6502.cpp mem_6502.h)
