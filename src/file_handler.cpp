#include "file_handler.h"

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