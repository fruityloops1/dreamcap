cmake_minimum_required(VERSION 3.5)
project(dreamcap)

add_subdirectory(lib/raylib)

add_library(imgui STATIC
    lib/imgui/imgui.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
    lib/imgui/misc/cpp/imgui_stdlib.cpp
    lib/imgui_raylib/imgui_impl_raylib.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(lib/inih)
include_directories(lib/raylib/src)
include_directories(lib/imgui_raylib)
include_directories(lib/imgui)
include_directories(lib/imgui/backends)
include_directories(lib/imgui/misc/cpp)

add_executable(dreamcap src/dreamcap.cpp src/dreamcap/ui_root.cpp src/dreamcap/ui/window.cpp)
target_link_libraries(dreamcap PUBLIC raylib)
target_link_libraries(dreamcap PUBLIC imgui)