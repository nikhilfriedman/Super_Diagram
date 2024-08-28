#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#define IMGUI_DEFINE_MATH_OPERATORS true

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include "ImGuiFileDialog.h"

#include <iostream>

void draw_file_dialog(GLFWwindow * window, Window_Neighbor_Info * wni, std::string * path, std::string * file);

#endif