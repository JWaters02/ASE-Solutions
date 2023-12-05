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

set(COMMON_SRC DominoUtils.h DominoesInterface.h)
set(COMMON_SRC_TYPES
        ${COMMON_SRC}
        DominoesWorstCase.cpp DominoesWorstCase.h
        DominoesAverageCase.cpp DominoesAverageCase.h
        DominoesConvoluted.cpp DominoesConvoluted.h)

add_executable(Dominoes_CLI_B1
        DominoesCLI-B1.cpp
        ${COMMON_SRC}
        DominoesAverageCase.cpp DominoesAverageCase.h)

add_executable(Dominoes_CLI_B2
        DominoesCLI-B2.cpp
        ${COMMON_SRC}
        DominoesWorstCase.cpp DominoesWorstCase.h)

add_executable(Dominoes_CLI_C1
        DominoesCLI-C1.cpp
        ${COMMON_SRC}
        DominoesConvoluted.cpp DominoesConvoluted.h)

add_executable(Dominoes_Solutions
        main.cpp
        ${COMMON_SRC}
        ${COMMON_SRC_TYPES})

add_executable(Dominoes_Tests
        DominoesTests.cpp
        ${COMMON_SRC}
        ${COMMON_SRC_TYPES})

add_executable(Dominoes_Benchmarks
        DominoBenchmark.cpp
        ${COMMON_SRC}
        ${COMMON_SRC_TYPES})

target_link_libraries(Dominoes_Tests PRIVATE GTest::gtest_main)
target_link_libraries(Dominoes_Benchmarks PRIVATE Python3::Python)

configure_file(benchmarkGraphGen.py ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/benchmarkGraphGen.py COPYONLY)