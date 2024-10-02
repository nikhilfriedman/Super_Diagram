#include "FolderSelector.h"

bool FolderSelector::enabled = false;
int FolderSelector::window_width = 0;
int FolderSelector::window_height = 0;
std::string FolderSelector::selected_folder_path = ""; // You need to define this even if it's a std::string
std::string FolderSelector::selected_folder_name = "";
GLFWwindow* FolderSelector::window = nullptr; // Pointer to GLFWwindow

FolderSelector::FolderSelector(int width, int height, std::string path, GLFWwindow * window) {
    enabled = false;

    window_width = width;
    window_height = height;

    selected_folder_path = path;
    selected_folder_name = "[no folder selected]";

    window = window;
}

void FolderSelector::enable() {
    enabled = true;
}

void FolderSelector::draw_directory(std::string const& current_path) {
    try {

        if(ImGui::Selectable("..")) {
            selected_folder_path = std::filesystem::path(current_path).parent_path().string();
            selected_folder_name = std::filesystem::path(selected_folder_path).filename().string();
        }

        for(const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(current_path))) {
            const auto& path = entry.path();
            std::string filename = path.filename().string();

            if(std::filesystem::is_directory(entry.status())) {
                if(ImGui::Selectable(filename.c_str())) {
                        selected_folder_name = filename;
                        selected_folder_path = path.string();   
                }
            } else {
                ImGui::Text("%s", filename.c_str());
            }
        }

    } catch(const std::filesystem::filesystem_error& e) {
        // TODO : add error window

        // ImGui::Begin("Error :(", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
        ImGui::Text("Error: %s", e.what());
        selected_folder_name = "[no folder selected]";

        ImGui::PopTextWrapPos();

        // ImGui::End();
    }
}

void FolderSelector::render() {
    if(enabled) {
        // TODO : update to make more accurate
        float menu_size = ImGui::GetFrameHeight();
        ImVec2 window_size = ImGui::GetIO().DisplaySize;

        ImGui::SetNextWindowPos(ImVec2((int) (window_size.x - window_width) >> 1, (int) (window_size.y - menu_size - window_height) >> 1), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiCond_Appearing);

        // good stuff lol

        ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoTitleBar);

        ImGui::Text("%s", selected_folder_path.c_str());
        ImGui::Text("%s", selected_folder_name.c_str());

        ImGui::BeginChild("TreeScrollArea", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);

        if((selected_folder_path).size() != 0) {
            draw_directory(selected_folder_path);
        } else {
            ImGui::BulletText("No directory selected.");
        }

        ImGui::EndChild();

        if(ImGui::Button("Test")) {
            enabled = false;
        }

        ImGui::End();
    }
}

FolderSelector::~FolderSelector() {

}