cmake_minimum_required(VERSION 3.14)
project(block_craft_3d CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.4
)

FetchContent_Declare(glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 1.0.1
)

FetchContent_Declare(spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog
	GIT_TAG v1.14.1
)

FetchContent_Declare(imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG v1.91.4
)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
	# General imgui sources
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp

	# Backend-specific files
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw)

add_library(glad STATIC glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_library(stb_image STATIC src/stb_image.c)
target_include_directories(stb_image PUBLIC include)

add_executable(${CMAKE_PROJECT_NAME}
	src/main.cpp
	src/application.cpp
	src/window.cpp
	
	# OpenGL
	src/shader_program.cpp
	src/vertex_buffer.cpp
	src/index_buffer.cpp
	src/texture.cpp
	src/camera.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui glad glm spdlog stb_image)

