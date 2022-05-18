cmake_minimum_required(VERSION 3.5)
project(dreamcap)

add_subdirectory(lib/raylib)
add_subdirectory(lib/nativefiledialog-extended)
add_subdirectory(lib/nlzss11/src)

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

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(include)
include_directories(lib/raylib/src)
include_directories(lib/imgui_raylib)
include_directories(lib/imgui)
include_directories(lib/imgui/backends)
include_directories(lib/imgui/misc/cpp)
include_directories(lib/nativefiledialog-extended/src/include)
include_directories(lib/nlzss11/src)

add_executable(dreamcap
    src/dreamcap.cpp
    src/dreamcap/config.cpp
    src/dreamcap/ui_root.cpp
    src/dreamcap/ui/menubar.cpp
    src/dreamcap/ui/fmap_extract_dialog.cpp
    src/dreamcap/ui/preferences.cpp 
    src/dreamcap/util.cpp
    src/dreamcap/core/fmap.cpp
    src/dreamcap/core/io/bio.cpp
)

target_link_libraries(dreamcap PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(dreamcap PUBLIC raylib)
target_link_libraries(dreamcap PUBLIC imgui)
target_link_libraries(dreamcap PUBLIC nlzss11)
target_link_libraries(dreamcap PRIVATE nfd)

file(COPY res DESTINATION .)