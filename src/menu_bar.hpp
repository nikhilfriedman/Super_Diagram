#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

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

void draw_menu(IGFD::FileDialogConfig * config, bool * quit, Window_Neighbor_Info * wni);

#endif