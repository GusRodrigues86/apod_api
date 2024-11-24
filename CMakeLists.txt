cmake_minimum_required(VERSION 3.16)
project(apod_api)

# vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(GTest_DIR D:/vcpkg/vcpkg/packages)

# Executable target
add_executable(${PROJECT_NAME} main.cpp)

# Add testing package
# find_package(GTest CONFIG REQUIRED)
# enable_testing()

# Test executables
# add_executable(${PROJECT_NAME}_tests test.cpp)

# target_link_libraries(apod_api_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)