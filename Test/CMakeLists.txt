cmake_minimum_required(VERSION 3.0)
project(DiskRateTest)

include_directories(../include)
file(GLOB SOURCES "../src/linux_parser.cpp")


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(DiskRateTest DiskRateTest.cpp ${SOURCES})


target_link_libraries(DiskRateTest ${GTEST_LIBRARIES} pthread)



# TODO: Run -Werror in CI.
target_compile_options(DiskRateTest PRIVATE -Wall -Wextra)


