cmake_minimum_required(VERSION 3.30)
project(Flare)

set(CMAKE_CXX_STANDARD 20)

# Build Flare as a static library
add_library(${PROJECT_NAME} STATIC src/libflare.cpp
        src/vertex.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_STATIC)

# Option to enable/disable building examples
option(BUILD_EXAMPLES "Build example applications" OFF)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
