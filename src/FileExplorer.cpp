#include "FileExplorer.h"

GLFWwindow * FileExplorer::window = nullptr;

ImVec2 FileExplorer::window_size = ImVec2(0, 0);
ImVec2 FileExplorer::window_pos = ImVec2(0, 0);

bool FileExplorer::enabled = true;

extern float vert_sep_1;
extern float vert_sep_2;
extern float horiz_sep_1;

FileExplorer::FileExplorer(ImVec2 ws, ImVec2 wp, GLFWwindow * w) {
    window_size = ws;
    window_pos = wp;
    window = w;

    enabled = true;
}

void drawDirectory(const std::filesystem::path& path_to_display) {
    try {
        for(const auto& entry : std::filesystem::directory_iterator(path_to_display))
        {
            const auto& path = entry.path();
            std::string filename = path.filename().string();

            if(std::filesystem::is_directory(entry.status()))
            {
                if(ImGui::TreeNode(filename.c_str()))
                {
                    drawDirectory(path);
                    ImGui::TreePop();
                }
            } else {
                ImGui::BulletText("%s", filename.c_str());
            }
        }
    } catch(const std::filesystem::filesystem_error& e) {
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);

        ImGui::Text("Error: %s", e.what());
        
        ImGui::PopTextWrapPos();
    }
}

void FileExplorer::render() {
    if(enabled) {
        window_pos = ImVec2(0, MenuBar::getWindowSize().y);
        window_size = ImVec2(vert_sep_1, 
            ImGui::GetIO().DisplaySize.y - MenuBar::getWindowSize().y);


        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

        ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        ImGui::Text("Explorer");

        if(FolderSelector::getFolderPath().size() != 0)
        {
            drawDirectory(std::filesystem::path(FolderSelector::getFolderPath()));
        } else {
            ImGui::BulletText("No directory selected.");
        }


        window_size = ImGui::GetWindowSize();
        window_pos  = ImGui::GetWindowPos();

        ImGui::End();
    }
}

void FileExplorer::enable() {
    enabled = true;
}

void FileExplorer::disable() {
    enabled = false;
}

bool FileExplorer::isEnabled() {
    return enabled;
}

ImVec2 FileExplorer::getWindowSize() {
    return window_size;
}

ImVec2 FileExplorer::getWindowPos() {
    return window_pos;
}

FileExplorer::~FileExplorer() {

}