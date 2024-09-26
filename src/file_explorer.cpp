#include "file_explorer.h"

void display_directory_tree(const std::filesystem::path& path_to_display)
{
    for(const auto& entry : std::filesystem::directory_iterator(path_to_display))
    {
        const auto& path = entry.path();
        std::string filename = path.filename().string();

        if(std::filesystem::is_directory(entry.status()))
        {
            if(ImGui::TreeNode(filename.c_str()))
            {
                display_directory_tree(path);
                ImGui::TreePop();
            }
        } else {
            ImGui::BulletText("%s", filename.c_str());
        }
    }
}

void draw_file_explorer(Window_Neighbor_Info * wni, std::string path)
{
    ImVec2 window_pos = ImVec2(
        0,
        (wni -> size_menu_bar).y
    );

    ImVec2 window_size = ImVec2(
        wni -> vert_sep_1,
        ImGui::GetIO().DisplaySize.y - (wni -> size_menu_bar).y
    );

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("Explorer");

    if(path.size() != 0)
    {
        display_directory_tree(std::filesystem::path(path));
    } else {
        ImGui::BulletText("No directory selected.");
    }


    wni -> size_file_explorer = ImGui::GetWindowSize();
    wni -> pos_file_explorer = ImGui::GetWindowPos();

    ImGui::End();
}