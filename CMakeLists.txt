cmake_minimum_required(VERSION 3.16)
project(apod_api)

set(BUILD_DIR_NAME "build/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/${BUILD_DIR_NAME}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add logging and testing package
find_package(glog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Link libs
target_link_libraries(${PROJECT_NAME} PRIVATE  GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main glog::glog)
add_test(NAME apod_test COMMAND apod_api_tests)