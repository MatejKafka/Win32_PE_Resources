cmake_minimum_required(VERSION 3.15)
project(Win32_PE_Resources)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(UNICODE _UNICODE)
add_compile_definitions(WIN32_LEAN_AND_MEAN)

add_executable(copy_resources copy_resources.cpp)
add_executable(enumerate_resources enumerate_resources.cpp)
add_executable(load_string_resources load_string_resource.cpp)
add_executable(update_resources update_resources.cpp)
