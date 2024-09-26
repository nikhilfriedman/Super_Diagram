#ifndef SCORE_H
#define SCORE_H

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

#include "imgui_helpers.h"

void draw_score(Window_Neighbor_Info * wni);

#endif