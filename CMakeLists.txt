cmake_minimum_required(VERSION 3.10)
project(IMageCov)

set(CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(tools SHARED
        ${PROJECT_SOURCE_DIR}/include/tools.cpp)
add_executable(IMageCov main.cpp)
target_link_libraries(
        IMageCov tools
)