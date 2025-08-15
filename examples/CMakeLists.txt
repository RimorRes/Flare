cmake_minimum_required(VERSION 3.30)
project(FlareExample)

set(CMAKE_CXX_STANDARD 20)

add_executable(FlareExample main.cpp)

target_link_libraries(FlareExample PRIVATE Flare)
target_include_directories(FlareExample PRIVATE ${CMAKE_SOURCE_DIR}/examples)

target_compile_definitions(FlareExample PRIVATE GLFW_STATIC)
