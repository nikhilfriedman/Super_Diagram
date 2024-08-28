#ifndef FILE_EXPLORER_HPP
#define FILE_EXPLORER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include "ImGuiFileDialog.h"

#include "imgui_helpers.hpp"

#include <iostream>

void draw_file_explorer(Window_Neighbor_Info * wni, std::string path);

#endif