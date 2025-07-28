cmake_minimum_required(VERSION 3.14)
project(ImGuiProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- External Libraries via FetchContent ---
include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.90.4
)
FetchContent_MakeAvailable(imgui)

# --- Source Files ---
file(GLOB_RECURSE CLASS_SOURCES
    ${CMAKE_SOURCE_DIR}/classes/*.cpp
    ${CMAKE_SOURCE_DIR}/classes/*.h
)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# --- ImGui Static Library ---
add_library(imgui_lib STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glfw_SOURCE_DIR}/include
)

# --- Main Executable ---
add_executable(ImGuiProject
    main.cpp
    ${CLASS_SOURCES}
)

target_include_directories(ImGuiProject PRIVATE
    ${CMAKE_SOURCE_DIR}/classes
)

# --- Link Libraries ---
find_package(OpenGL REQUIRED)

target_link_libraries(ImGuiProject
    imgui_lib
    glfw
    OpenGL::GL
    ws2_32  # Windows-specific socket lib
)
