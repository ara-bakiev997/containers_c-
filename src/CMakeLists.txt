# 'Google_test' is the subproject name
cmake_minimum_required(VERSION 3.21.1)
project(Google_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Google_Tests_run
        tests/tests_array.cc
        tests/tests_list.cc
        tests/tests_map.cc
        tests/tests_multiset.cc
        tests/tests_queue.cc
        tests/tests_set.cc
        tests/tests_stack.cc
        tests/tests_vector.cc
        )
target_link_libraries(Google_Tests_run gtest gtest_main)
