#include "MenuBar.h"

bool MenuBar::enabled = false;

ImVec2 MenuBar::window_size = ImVec2(0, 0);
ImVec2 MenuBar::window_pos = ImVec2(0, 0);

GLFWwindow * MenuBar::window = nullptr;

extern bool no_resizing;
extern bool quit;

MenuBar::MenuBar(ImVec2 ws, ImVec2 wp, GLFWwindow * w) {
    window_size = ws;
    window_pos = wp;
    window = w;

    enabled = true;
}

void MenuBar::render() {
    ImGui::BeginMainMenuBar();

    bool open_about_popup = false;

    if(ImGui::BeginMenu("File"))
    {
        if(ImGui::MenuItem("Open", "Ctrl-O"))
        {
            no_resizing = true;

            FolderSelector::enable();
        }

        if(ImGui::MenuItem("Save", "Ctrl-S"))
        {
        }

        if(ImGui::MenuItem("Quit", "Ctrl-Q"))
        {
            quit = true;
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Edit"))
    {
        if(ImGui::MenuItem("Copy" , "Ctrl-C"))
        {
        }

        if(ImGui::MenuItem("Paste", "Ctrl-V"))
        {
        }

        ImGui::EndMenu();
    }

    // if(ImGui::BeginMenu("View"))
    // {
    //     if(ImGui::MenuItem("Explorer", NULL, &(wni -> viewing_file_explorer)))
    //     {
    //     }

    //     if(ImGui::MenuItem("Score", NULL, &(wni -> viewing_score)))
    //     {
    //     }

    //     if(ImGui::MenuItem("Code Preview", NULL, &(wni -> viewing_code_preview)))
    //     {
    //     }

    //     ImGui::EndMenu();
    // }

    if(ImGui::BeginMenu("Language"))
    {
        if(ImGui::MenuItem("C++"))
        {
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Help"))
    {
        if(ImGui::MenuItem("About"))
        {
            open_about_popup = true;
        }

        ImGui::EndMenu();
    }

    // if(open_about_popup)
    // {
    //     ImGui::OpenPopup("About superdiagram");
    //     open_about_popup = false;
    // }

    // float menu_size = ImGui::GetFrameHeight();
    // ImVec2 window_size = ImGui::GetIO().DisplaySize;

    // ImGui::SetNextWindowPos(ImVec2((int) (window_size.x - FILE_DIALOG_WINDOW_WIDTH) >> 1, (int) (window_size.y - menu_size - FILE_DIALOG_WINDOW_HEIGHT) >> 1), ImGuiCond_Appearing);
    // ImGui::SetNextWindowSize(ImVec2(FILE_DIALOG_WINDOW_WIDTH, FILE_DIALOG_WINDOW_HEIGHT), ImGuiCond_Appearing);

    // if(ImGui::BeginPopupModal("About superdiagram"))
    // {
    //     no_resizing = true;

    //     ImGui::Text("Some text about the program.");

    //     if(ImGui::Button("Close"))
    //     {
    //         ImGui::CloseCurrentPopup();

    //         no_resizing = false;
    //     }
    //     ImGui::EndPopup();
    // }

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