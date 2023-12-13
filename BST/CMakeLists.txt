cmake_minimum_required(VERSION 3.25)
project(BST_Solutions)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(BST_Solutions
        main.cpp
        Dictionary.h)

add_executable(BST_Tests
        Dictionary.h
        DictionaryTests.cpp)
target_link_libraries(BST_Tests PRIVATE GTest::gtest_main)