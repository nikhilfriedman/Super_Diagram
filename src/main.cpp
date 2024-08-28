#define IMGUI_DEFINE_MATH_OPERATORS true
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes/imnodes.h"
#include "imnodes/imnodes_internal.h"

#include "ImGuiColorTextEdit/TextEditor.h"

#include "ImGuiFileDialog/ImGuiFileDialog.h"

#include <iostream>

#include "menu_bar.hpp"
#include "file_explorer.hpp"
#include "code_preview.hpp"
#include "node_editor.hpp"
#include "imgui_helpers.hpp"
#include "file_handler.hpp"
#include "score.hpp"

#include "ImGuiFileDialog/stb/stb_image.h"

void set_window_icon(GLFWwindow * window, const char * path)
{
    GLFWimage images[1];

    images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);

    if(images[0].pixels)
    {
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(images[0].pixels);
    } else {
        std::cout << "Failed to load icon\n"; 
    }
}

int main(int, char**)
{
    // Setup graphics
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return EXIT_FAILURE;

    // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "[no file selected] - superdiagram", NULL, NULL);
    if (window == NULL) return EXIT_FAILURE;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return EXIT_FAILURE;

    ImGuiIO& io = create_imgui_context(window);

    set_window_icon(window, "../external/textures/mushroom.png");

    // Window
    bool window_resize = false;
    int display_w, display_h = 0;
    int prev_display_w, prev_display_h = 0;
    ImVec2 window_pos = ImVec2(0,0);
    Window_Neighbor_Info wni = {
        false,          // resizing file explorer
        false,          // resizing score
        false,          // resizing node editor

        false,          // no resizing

        true,           // viewing file explorer
        true,           // viewing score
        true,           // viewing code preview

        ImVec2(0,0),    // menu bar initial size
        ImVec2(300,0),    // file explorer initial size
        ImVec2(0,200),    // score initial size
        ImVec2(600,0),    // node editor initial size
        ImVec2(0,0),    // code preview initial size

        ImVec2(0,0),    // menu bar initial position
        ImVec2(0,0),    // file explorer initial position
        ImVec2(0,0),    // score initial position
        ImVec2(0,0),    // node editor initial position
        ImVec2(0,0),     // code preview initial position

        400.0f,
        800.0f,
        600.0f
    };
    
    // Text Editor
    TextEditor editor;
    const char * start_text = "No file selected.";
    editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
    editor.SetShowWhitespaces(false);
    editor.SetText(start_text);

    // Nodes
    const int hardcoded_node_id = 1;

    // File Explorer
    float curr_mouse_delta_x;

    // File Dialog
    IGFD::FileDialogConfig config;
    config.flags |= ImGuiFileDialogFlags_Modal;
    config.path = "";
    std::string path = "";
    std::string file = "";

    // Main menu
    bool quit = false;

    while (!glfwWindowShouldClose(window))
    {
        if(quit) break;

        imgui_init_render();

        check_window_resize(display_w, display_h, &prev_display_w, &prev_display_h, &window_resize);

        wni.vert_sep_1 = ImClamp(wni.vert_sep_1, 0.0f, ImGui::GetIO().DisplaySize.x - MIN_WH * 2);
        wni.vert_sep_2 = ImClamp(wni.vert_sep_2, wni.vert_sep_1 + MIN_WH, ImGui::GetIO(). DisplaySize.x - MIN_WH);
        wni.horiz_sep_1 = ImClamp(wni.horiz_sep_1, wni.pos_menu_bar.y + wni.size_menu_bar.y + MIN_WH, ImGui::GetIO().DisplaySize.y - MIN_WH);

        if(wni.viewing_file_explorer) 
        {
            wni.vert_sep_1 = (wni.vert_sep_1 >= MIN_WH) ?
                wni.vert_sep_1 : MIN_WH;
            if (!wni.resize_horiz_sep_1 && !wni.resize_vert_sep_2 && !wni.no_resizing) update_vert_sep(&(wni.vert_sep_1),
                wni.pos_menu_bar.y + wni.size_menu_bar.y,
                ImGui::GetIO().DisplaySize.y,
                &(wni.resize_vert_sep_1), 
                MIN_WH, 
                wni.vert_sep_2 - MIN_WH);
        }
        else wni.vert_sep_1 = 0;

        if(wni.viewing_code_preview) 
        {
            wni.vert_sep_2 = (wni.vert_sep_2 >= wni.vert_sep_1 + MIN_WH && wni.vert_sep_2 <= ImGui::GetIO().DisplaySize.x - MIN_WH) ? 
                wni.vert_sep_2 : ImClamp((ImGui::GetIO().DisplaySize.x - wni.vert_sep_1) / 2, wni.vert_sep_1 + MIN_WH, ImGui::GetIO().DisplaySize.x - MIN_WH);
            if(!wni.resize_horiz_sep_1 && !wni.resize_vert_sep_1 && !wni.no_resizing) update_vert_sep(&(wni.vert_sep_2), 
                wni.pos_menu_bar.y + wni.size_menu_bar.y,
                wni.pos_score.y,
                &(wni.resize_vert_sep_2), 
                wni.vert_sep_1 + MIN_WH, 
                ImGui::GetIO().DisplaySize.x - MIN_WH);
        }
        else wni.vert_sep_2 = ImGui::GetIO().DisplaySize.x;

        if(wni.viewing_score) 
        {
            wni.horiz_sep_1 = (wni.horiz_sep_1 < ImGui::GetIO().DisplaySize.y - MIN_WH) ? 
                wni.horiz_sep_1 : ImGui::GetIO().DisplaySize.y - MIN_WH;
            if(!wni.resize_vert_sep_1 && !wni.resize_vert_sep_2 && !wni.no_resizing) update_horiz_sep(&(wni.horiz_sep_1),
                wni.pos_score.x,
                ImGui::GetIO().DisplaySize.x,
                &(wni.resize_horiz_sep_1),
                wni.size_menu_bar.y + MIN_WH,
                ImGui::GetIO().DisplaySize.y - MIN_WH);
        }
        else wni.horiz_sep_1 = ImGui::GetIO().DisplaySize.y;

        draw_file_dialog(window, &wni, &path, &file);

        draw_menu(&config, &quit, &wni);

        if(wni.viewing_file_explorer) draw_file_explorer(&wni, path);

        if(wni.viewing_score) draw_score(&wni);

        draw_node_editor(hardcoded_node_id, &wni);

        if(wni.viewing_code_preview) draw_text_editor(&editor, &wni);

        imgui_render_frame(window, &display_w, &display_h);
    }

    graphics_cleanup(window);

    return EXIT_SUCCESS;
}