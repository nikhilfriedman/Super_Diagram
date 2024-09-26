#include "menu_bar.h"

void draw_menu(IGFD::FileDialogConfig * config, bool * quit, Window_Neighbor_Info * wni)
{
    ImGui::BeginMainMenuBar();

    bool open_about_popup = false;

    if(ImGui::BeginMenu("File"))
    {
        if(ImGui::MenuItem("Open", "Ctrl-O"))
        {
            wni -> no_resizing = true;
            ImGuiFileDialog::Instance() -> OpenDialog("ChooseFolderKey", "Select project file", ".sd", * config);
        }

        if(ImGui::MenuItem("Save", "Ctrl-S"))
        {
        }

        if(ImGui::MenuItem("Quit", "Ctrl-Q"))
        {
            * quit = true;
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

    if(ImGui::BeginMenu("View"))
    {
        if(ImGui::MenuItem("Explorer", NULL, &(wni -> viewing_file_explorer)))
        {
        }

        if(ImGui::MenuItem("Score", NULL, &(wni -> viewing_score)))
        {
        }

        // if(ImGui::MenuItem("Node Editor", NULL, &(wni -> viewing_node_editor)))
        // {
        // }

        if(ImGui::MenuItem("Code Preview", NULL, &(wni -> viewing_code_preview)))
        {
        }

        ImGui::EndMenu();
    }

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

    if(open_about_popup)
    {
        ImGui::OpenPopup("About superdiagram");
        open_about_popup = false;
    }

    float menu_size = ImGui::GetFrameHeight();
    ImVec2 window_size = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowPos(ImVec2((int) (window_size.x - FILE_DIALOG_WINDOW_WIDTH) >> 1, (int) (window_size.y - menu_size - FILE_DIALOG_WINDOW_HEIGHT) >> 1), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(FILE_DIALOG_WINDOW_WIDTH, FILE_DIALOG_WINDOW_HEIGHT), ImGuiCond_Appearing);

    if(ImGui::BeginPopupModal("About superdiagram"))
    {
        wni -> no_resizing = true;

        ImGui::Text("Some text about the program.");

        if(ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();

            wni -> no_resizing = false;
        }
        ImGui::EndPopup();
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("superdiagram ").x - ImGui::GetStyle().ItemSpacing.x);
    ImGui::Text("superdiagram");

    wni -> size_menu_bar = ImGui::GetWindowSize();
    wni -> pos_menu_bar = ImGui::GetWindowPos();

    ImGui::EndMainMenuBar();


}