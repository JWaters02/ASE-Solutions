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

add_executable(Dominoes_Solutions
        main.cpp
        DominoUtils.h
        DominoesInterface.h
        DominoesWorstCase.cpp DominoesWorstCase.h
        DominoesAverageCase.cpp DominoesAverageCase.h)

add_executable(Dominoes_Tests
        DominoesTests.cpp
        DominoUtils.h
        DominoesInterface.h
        DominoesWorstCase.cpp DominoesWorstCase.h
        DominoesAverageCase.cpp DominoesAverageCase.h)

add_executable(Dominoes_Benchmarks
        DominoBenchmark.cpp
        DominoUtils.h
        DominoesInterface.h
        DominoesWorstCase.cpp DominoesWorstCase.h
        DominoesAverageCase.cpp DominoesAverageCase.h)

target_link_libraries(Dominoes_Tests PRIVATE GTest::gtest_main)
target_link_libraries(Dominoes_Benchmarks PRIVATE Python3::Python)

configure_file(benchmarkGraphGen.py ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/benchmarkGraphGen.py COPYONLY)