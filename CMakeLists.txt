cmake_minimum_required(VERSION 3.14)
project(block_craft_3d CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_library(glad STATIC glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	src/application.cpp
	src/window.cpp
	
	# OpenGL
	src/shader_program.cpp
	src/vertex_buffer.cpp
	src/index_buffer.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw glad)

