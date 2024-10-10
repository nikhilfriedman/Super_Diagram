#include "MenuBar.h"

bool MenuBar::enabled = false;

ImVec2 MenuBar::window_size = ImVec2(0, 0);
ImVec2 MenuBar::window_pos = ImVec2(0, 0);

GLFWwindow * MenuBar::window = nullptr;

extern bool no_resizing;
extern bool quit;

bool tmp1 = true;
bool tmp2 = true;
bool tmp3 = true;

bool open_about = false;

MenuBar::MenuBar(ImVec2 ws, ImVec2 wp, GLFWwindow * w) {
    window_size = ws;
    window_pos = wp;
    window = w;

    enabled = true;
}

void MenuBar::render() {
    ImGui::BeginMainMenuBar();

    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("Open", "Ctrl-O")) {
            no_resizing = true;

            FolderSelector::enable();

            // ImGui::OpenPopup("FolderSelector");
        }

        if(ImGui::MenuItem("Save", "Ctrl-S")) {
        }

        if(ImGui::MenuItem("Quit", "Ctrl-Q")) {
            quit = true;
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Edit")) {
        if(ImGui::MenuItem("Copy" , "Ctrl-C")) {
        }

        if(ImGui::MenuItem("Paste", "Ctrl-V")) {
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("View")) {
        if(ImGui::MenuItem("Explorer", NULL, &tmp1)) {
            if(FileExplorer::isEnabled())   FileExplorer::disable();
            else                            FileExplorer::enable();
        }

        if(ImGui::MenuItem("Score", NULL, &tmp2)) {
            if(Score::isEnabled())          Score::disable();
            else                            Score::enable();
        }

        if(ImGui::MenuItem("Code Preview", NULL, &tmp3)) {
            if(CodePreview::isEnabled())    CodePreview::disable();
            else                            CodePreview::enable();
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Language")) {
        if(ImGui::MenuItem("C++")) {
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Help")) {
        if(ImGui::MenuItem("About")) {
            open_about = true;
        }

        ImGui::EndMenu();
    }

    if(open_about) {
        ImGui::OpenPopup("About superdiagram");
        open_about = false;
    }


    ImGui::SetNextWindowPos(ImVec2((int) (ImGui::GetIO().DisplaySize.x - 400) >> 1, 
        (int) (ImGui::GetIO().DisplaySize.y - MenuBar::getWindowSize().y - 400) >> 1), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(400, 
        400), ImGuiCond_Appearing);

    if(ImGui::BeginPopupModal("About superdiagram"))
    {
        no_resizing = true;

        ImGui::Text("Some text about the program.");

        if(ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();

            no_resizing = false;
        }
        ImGui::EndPopup();
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("superdiagram ").x - ImGui::GetStyle().ItemSpacing.x);
    ImGui::Text("superdiagram");

    window_size = ImGui::GetWindowSize();
    window_pos  = ImGui::GetWindowPos();

    ImGui::EndMainMenuBar();

}

void MenuBar::enable() {
    enabled = true;
}

void MenuBar::disable() {
    enabled = false;
}

bool MenuBar::isEnabled() {
    return enabled;
}

ImVec2 MenuBar::getWindowSize() {
    return window_size;
}

ImVec2 MenuBar::getWindowPos() {
    return window_pos;
}

MenuBar::~MenuBar() {

}