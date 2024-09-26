#include "folder_selection.h"

FolderSelector::FolderSelector(int width, int height) {
    enabled = false;

    window_width = width;
    window_height = height;
}

void FolderSelector::enable_folder_select() {
    enabled = true;
}

static void draw_directory(const std::filesystem::path& dir_path) {
    for(const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        const auto& path = entry.path();
        std::string filename = path.filename().string();

        if(std::filesystem::is_directory(entry.status())) {
            if(ImGui::TreeNode(filename.c_str())) {
                if(ImGui::IsItemToggledOpen()) {
                    std::cout << filename.c_str();
                }

                draw_directory(path);
                ImGui::TreePop();
            }
        } else {
            ImGui::BulletText("%s", filename.c_str());
        }
    }
}

void FolderSelector::draw_folder_select(GLFWwindow * window, std::string * path) {
    if(enabled) {
        // TODO : update to make more accurate
        float menu_size = ImGui::GetFrameHeight();
        ImVec2 window_size = ImGui::GetIO().DisplaySize;

        ImGui::SetNextWindowPos(ImVec2((int) (window_size.x - window_width) >> 1, (int) (window_size.y - menu_size - window_height) >> 1), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiCond_Appearing);

        // good stuff lol

        ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoTitleBar);

        if((* path).size() != 0) {
            draw_directory(std::filesystem::path(* path));
        } else {
            ImGui::BulletText("No directory selected.");
        }

        ImGui::End();
    }
}

FolderSelector::~FolderSelector() {

}