cmake_minimum_required(VERSION 3.30)
project(Flare)

set(CMAKE_CXX_STANDARD 20)

# Option to build shared or static library
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(${PROJECT_NAME} src/libflare.cpp src/vertex.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

# Define GLFW_STATIC only for static builds
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_STATIC)
endif()

# Option to enable/disable building examples
option(BUILD_EXAMPLES "Build example applications" OFF)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
