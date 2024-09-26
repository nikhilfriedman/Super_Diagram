#ifndef MENU_BAR_H
#define MENU_BAR_H

#define FILE_DIALOG_WINDOW_WIDTH 600
#define FILE_DIALOG_WINDOW_HEIGHT 400

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

#include "imgui_helpers.h"

#include <iostream>

void draw_menu(IGFD::FileDialogConfig * config, bool * quit, Window_Neighbor_Info * wni);

#endif