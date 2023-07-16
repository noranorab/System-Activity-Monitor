cmake_minimum_required(VERSION 3.0)
project(test)

include_directories(../include)
file(GLOB SOURCES "../src/linux_parser.cpp")


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(test test.cpp ${SOURCES})


target_link_libraries(test ${GTEST_LIBRARIES} pthread)



# TODO: Run -Werror in CI.
target_compile_options(test PRIVATE -Wall -Wextra)


