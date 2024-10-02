cmake_minimum_required(VERSION 3.10)
project(super_diagram)

set(CMAKE_CXX_STANDARD 17)

# Add GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

# Add GLAD
add_library(glad external/glad/src/glad.c)
include_directories(external/glad/include)

include_directories(external/imnodes)
include_directories(external/ImGuiColorTextEdit)
include_directories(external/ImGuiFileDialog)

# Add ImGui
add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/ImGuiColorTextEdit/TextEditor.cpp
    external/imnodes/imnodes.cpp
    external/ImGuiFileDialog/ImGuiFileDialog.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp)
include_directories(external/imgui)
include_directories(external/imgui/backends)

# Add main.cpp

# uncomment for final release
# add_executable(super_diagram WIN32 src/main.cpp)
add_executable(super_diagram 
    src/main.cpp 
    src/menu_bar.cpp 
    src/file_explorer.cpp
    src/code_preview.cpp
    src/node_editor.cpp
    src/imgui_helpers.cpp
    src/FolderSelector.cpp
    src/MenuBar.cpp
    src/FileExplorer.cpp
    src/Score.cpp)

# Link libraries
target_link_libraries(super_diagram glfw glad imgui)
