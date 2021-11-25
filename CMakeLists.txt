cmake_minimum_required (VERSION 3.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project (StudentProgramInstrumentation)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER /usr/bin/clang-10 CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-10 CACHE PATH "" FORCE)

include_directories("/usr/include/llvm-10/")
include_directories("/usr/include/llvm-c-10/")
include_directories("/usr/include/clang/10/include/")
include_directories("include")


link_directories("/usr/lib/llvm-10/lib/")
