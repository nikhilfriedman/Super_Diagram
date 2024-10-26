#include "FolderSelector.h"

bool FolderSelector::enabled = false;
bool FolderSelector::folder_selected = false;;
std::string FolderSelector::selected_folder_path = "";
std::string FolderSelector::selected_folder_name = "";
GLFWwindow* FolderSelector::window = nullptr;

ImVec2 FolderSelector::window_pos = ImVec2(0, 0);
ImVec2 FolderSelector::window_size = ImVec2(0, 0);

extern bool no_resizing;
extern std::string window_title;

FolderSelector::FolderSelector(ImVec2 ws, ImVec2 wp, std::string path, GLFWwindow * w) {
    enabled = false;

    window_size = ws;
    window_pos = wp;

    selected_folder_path = path;
    selected_folder_name = "[no folder selected]";

    folder_selected = false;

    window = w;
}

void FolderSelector::drawDirectory(std::string const& current_path) {
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
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);

        ImGui::Text("Error: %s", e.what());
        selected_folder_name = "[no folder selected]";
        
        ImGui::PopTextWrapPos();
    }
}

void FolderSelector::render() {
    // if(enabled) {
    //     // TODO : update to make more accurate
    //     float menu_size = ImGui::GetFrameHeight();
    //     ImVec2 display_size = ImGui::GetIO().DisplaySize;

    //     ImGui::SetNextWindowPos(ImVec2((int) (display_size.x - window_size.x) >> 1, (int) (display_size.y - menu_size - window_size.y) >> 1), ImGuiCond_Appearing);
    //     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y), ImGuiCond_Appearing);

    //     ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoTitleBar);

    //     ImGui::Text("%s", selected_folder_path.c_str());
    //     ImGui::Text("%s", selected_folder_name.c_str());

    //     ImGui::BeginChild("TreeScrollArea", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);

    //     if((selected_folder_path).size() != 0) {
    //         drawDirectory(selected_folder_path);
    //     } else {
    //         ImGui::BulletText("No directory selected.");
    //     }

    //     ImGui::EndChild();

    //     if(ImGui::Button("Test")) {
    //         enabled = false;

    //         no_resizing = false;
    //     }

    //     window_pos  = ImGui::GetWindowPos();
    //     window_size = ImGui::GetWindowSize();

    //     ImGui::End();
    // }

    if(enabled) {
        ImGui::OpenPopup("FolderSelector");
        enabled = false;
    }

    float menu_size = ImGui::GetFrameHeight();
    ImVec2 display_size = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowPos(ImVec2((int) (display_size.x - window_size.x) >> 1, (int) (display_size.y - menu_size - window_size.y) >> 1), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y), ImGuiCond_Appearing);

    if(ImGui::BeginPopupModal("FolderSelector", NULL, ImGuiWindowFlags_NoTitleBar)) {
        ImGui::Text("%s", selected_folder_path.c_str());
        ImGui::Text("%s", selected_folder_name.c_str());

        ImGui::BeginChild("TreeScrollArea", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);

        if((selected_folder_path).size() != 0) {
            drawDirectory(selected_folder_path);
        } else {
            ImGui::BulletText("No directory selected.");
        }

        ImGui::EndChild();

        if(ImGui::Button("Test")) {
            enabled = false;

            no_resizing = false;

            folder_selected = true;

            window_title = selected_folder_name + " - superdiagram";

            ImGui::CloseCurrentPopup();
        }

        window_pos  = ImGui::GetWindowPos();
        window_size = ImGui::GetWindowSize();

        ImGui::EndPopup();
    }
}

void FolderSelector::enable() {
    enabled = true;
}

void FolderSelector::disable() {
    enabled = false;
}

std::string FolderSelector::getFolderPath() {
    return selected_folder_path;
}

std::string FolderSelector::getFolderName() {
    return selected_folder_name;
}

bool FolderSelector::isEnabled() {
    return enabled;
}

bool FolderSelector::isFolderSelected() {
    return folder_selected;
}

ImVec2 FolderSelector::getWindowSize() {
    return window_size;
}

ImVec2 FolderSelector::getWindowPos() {
    return window_pos;
}

FolderSelector::~FolderSelector() {

}