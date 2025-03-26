cmake_minimum_required(VERSION 3.30)
project(Flare)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

add_library(Flare SHARED src/library.cpp
)
target_include_directories(Flare PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Flare PUBLIC glfw vulkan glm::glm)

# Option to enable/disable building examples
option(BUILD_EXAMPLES "Build example applications" OFF)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
