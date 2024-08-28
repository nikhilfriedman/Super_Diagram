#define IMGUI_DEFINE_MATH_OPERATORS true

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes/imnodes.h"
#include "imnodes/imnodes_internal.h"

#include "ImGuiColorTextEdit/TextEditor.h"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include <iostream>

#include "imgui_helpers.hpp"

#include "code_preview.hpp"

void draw_text_editor(TextEditor * editor, Window_Neighbor_Info * wni)
{
    ImVec2 window_pos = ImVec2(
        wni -> vert_sep_2,
        (wni -> size_menu_bar).y
    );

    ImVec2 window_size = ImVec2(
        ImGui::GetIO().DisplaySize.x - wni -> vert_sep_2,
        wni -> horiz_sep_1 - (wni -> size_menu_bar).y
    );

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Editor", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Code Preview");

    (* editor).Render("Text Editor");

    wni -> size_code_preview = ImGui::GetWindowSize();
    wni -> pos_code_preview = ImGui::GetWindowPos();

    ImGui::End();
}