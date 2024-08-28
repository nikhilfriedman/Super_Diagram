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

#include "imgui_helpers.hpp"

#include "score.hpp"

void draw_score(Window_Neighbor_Info * wni)
{
    ImVec2 window_pos = ImVec2(
        wni -> vert_sep_1,
        wni -> horiz_sep_1
    );

    ImVec2 window_size = ImVec2(
        ImGui::GetIO().DisplaySize.x - wni -> vert_sep_1,
        ImGui::GetIO().DisplaySize.y - wni -> horiz_sep_1
    );

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Score", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Score");

    wni -> size_score = ImGui::GetWindowSize();
    wni -> pos_score = ImGui::GetWindowPos();

    ImGui::End();
}