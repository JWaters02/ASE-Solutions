cmake_minimum_required(VERSION 3.25)
project(ASE_Solutions)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Week1)
add_subdirectory(BST)

add_executable(ASE_Solutions main.cpp)