cmake_minimum_required(VERSION 3.20)

set(project_name APOD_CPP) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/component.hpp
        src/client/remote_client.cpp
        src/client/remote_client.hpp
        src/controller/api_controller.cpp
        src/controller/api_controller.hpp
        src/dto/dtos.hpp
)

## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED)


target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui static resources folder
add_definitions(
	-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res"
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe src/app.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)