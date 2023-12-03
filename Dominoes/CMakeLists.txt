cmake_minimum_required(VERSION 3.25)
project(Dominoes)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(COPY dominoes-test_data DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_executable(Dominoes
        main.cpp
        DominoesInterface.h
        DominoesWorstCase.cpp DominoesWorstCase.h
        DominoesAverageCase.cpp DominoesAverageCase.h)

target_link_libraries(Dominoes PRIVATE GTest::gtest_main Python3::Python)