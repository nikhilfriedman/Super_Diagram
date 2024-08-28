#define IMGUI_DEFINE_MATH_OPERATORS true

#define FILE_DIALOG_WINDOW_WIDTH 600
#define FILE_DIALOG_WINDOW_HEIGHT 400

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

#include "file_handler.hpp"

void draw_file_dialog(GLFWwindow * window, Window_Neighbor_Info * wni, std::string * path, std::string * file)
{
    float menu_size = ImGui::GetFrameHeight();
    ImVec2 window_size = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowPos(ImVec2((int) (window_size.x - FILE_DIALOG_WINDOW_WIDTH) >> 1, (int) (window_size.y - menu_size - FILE_DIALOG_WINDOW_HEIGHT) >> 1), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(FILE_DIALOG_WINDOW_WIDTH, FILE_DIALOG_WINDOW_HEIGHT), ImGuiCond_Appearing);

    if(ImGuiFileDialog::Instance() -> Display("ChooseFolderKey"))
    {
        if(ImGuiFileDialog::Instance() -> IsOk())
        {            
            * path = ImGuiFileDialog::Instance()->GetCurrentPath();
            
            std::string open = "[";
            std::string close = "] - superdiagram";
            std::string new_title = open + ImGuiFileDialog::Instance()->GetFilePathName() + close;

            glfwSetWindowTitle(window, new_title.c_str());
        }

        wni -> no_resizing = false;

        ImGuiFileDialog::Instance() -> Close();
    }
}