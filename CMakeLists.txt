cmake_minimum_required(VERSION 3.16)
project(apod_api)

set(BUILD_DIR_NAME "build/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/${BUILD_DIR_NAME}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add logging and testing package
find_package(glog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(oatpp CONFIG REQUIRED)

# Executable target
add_executable(${PROJECT_NAME} src/app.cpp)

# Include all source files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src) 

# Link libs
target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE  
	GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
	glog::glog
	oatpp::oatpp oatpp::oatpp-test
	)

add_test(NAME apod_test COMMAND apod_api_tests)