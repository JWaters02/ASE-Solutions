project(TimingTests)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(TimingTests
        TimingTests.cpp
        KeyItemGenerator.h
        KeyItemGenerator.cpp
        ../BST/Dictionary.h)
target_link_libraries(TimingTests PRIVATE Python3::Python)
configure_file(timingGraphGen.py ${CMAKE_CURRENT_BINARY_DIR}/timingGraphGen.py COPYONLY)