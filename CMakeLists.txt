cmake_minimum_required(VERSION 3.21)
project(cpp_project_template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(project_lib src/parse_uint.cpp)
target_include_directories(project_lib PUBLIC include)

add_executable(hello src/main.cpp)
target_link_libraries(hello PRIVATE project_lib)

include(CTest)
if(BUILD_TESTING)
    add_executable(project_tests tests/test_parse_uint.cpp)
    target_link_libraries(project_tests PRIVATE project_lib)
    add_test(NAME project_tests COMMAND project_tests)
endif()

set(project_targets project_lib hello)
if(BUILD_TESTING)
    list(APPEND project_targets project_tests)
endif()

foreach(target IN LISTS project_targets)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_compile_options(${target} PRIVATE -g -fno-omit-frame-pointer)
        endif()
        if(ENABLE_SANITIZERS)
            target_compile_options(${target} PRIVATE -O1 -fsanitize=address,undefined)
            target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        endif()
    endif()
endforeach()
