project(Week2Solutions)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Week2Solutions
        main.cpp
        Dictionary.h)

add_executable(Week2Tests
        Dictionary.h
        DictionaryTests.cpp)
target_link_libraries(Week2Tests PRIVATE GTest::gtest_main)