cmake_minimum_required(VERSION 3.16)
project(apod_api)

# vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 
# Executable target

# Add testing package
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    )
    
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME apod_test COMMAND apod_api_tests)

# Test executables
# add_executable(${PROJECT_NAME}_tests test.cpp)

# target_link_libraries(apod_api_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)