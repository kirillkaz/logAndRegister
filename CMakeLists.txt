cmake_minimum_required(VERSION 3.20)
project(logAndRegister)

set(CMAKE_CXX_STANDARD 23)

add_executable(logAndRegister login.cpp)

add_library(AUTHORIZATOR authorizator.cpp authorizator.h key-value/container.cpp key-value/container.h)

add_library(TESTS tests.cpp)

add_library(CONVERTER CSV_container_converter.cpp CSV_container_converter.h)

add_subdirectory(Csv)

add_subdirectory(logger)

add_subdirectory(tests/googletest)
enable_testing()
#include_directories(${STACK_INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(logAndRegister gtest gtest_main TESTS AUTHORIZATOR CONVERTER mainlogger CSV)

