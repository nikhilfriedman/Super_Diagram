#define IMGUI_DEFINE_MATH_OPERATORS
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include <iostream>

#include "imgui_helpers.h"

#include "FolderSelector.h"
#include "MenuBar.h"
#include "FileExplorer.h"
#include "Score.h"
#include "NodeEditor.h"
#include "CodePreview.h"

bool no_resizing    = false;
bool quit           = false;

float vert_sep_1    = 0.0;
float vert_sep_2    = 0.0;
float horiz_sep_1   = 0.0;

int main(int, char**) {
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

    // Window
    bool window_resize = false;
    int display_w, display_h = 0;
    int prev_display_w, prev_display_h = 0;
    ImVec2 window_pos = ImVec2(0,0);

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

    // Main menu

    FolderSelector fs = FolderSelector(ImVec2(600, 400), ImVec2(0, 0), "/home", window);

    MenuBar mb = MenuBar(ImVec2(0,0), ImVec2(0, 0), window);

    FileExplorer fw = FileExplorer(ImVec2(0, 0), ImVec2(0, 0), window);

    Score sc = Score(ImVec2(0, 0), ImVec2(0, 0), window);

    NodeEditor ne = NodeEditor(ImVec2(0, 0), ImVec2(0, 0), window);

    CodePreview cp = CodePreview(ImVec2(0, 0), ImVec2(0, 0), &editor, window);

    // initialize some values
    bool resize_horiz_sep_1 = false;
    bool resize_vert_sep_1 = false;
    bool resize_vert_sep_2 = false;
    vert_sep_1 = 400;
    vert_sep_2 = 1000;
    horiz_sep_1 = 400;

    while (!glfwWindowShouldClose(window))
    {
        if(quit) break;

        imgui_init_render();

        check_window_resize(display_w, display_h, &prev_display_w, &prev_display_h, &window_resize);

        // vert_sep_1 = ImClamp(vert_sep_1, 0.0f, ImGui::GetIO().DisplaySize.x - MIN_WH * 2);
        // vert_sep_2 = ImClamp(vert_sep_2, vert_sep_1 + MIN_WH, ImGui::GetIO(). DisplaySize.x - MIN_WH);
        // horiz_sep_1 = ImClamp(horiz_sep_1, MenuBar::getWindowPos().y + MenuBar::getWindowSize().y + MIN_WH, ImGui::GetIO().DisplaySize.y - MIN_WH);

        if(FileExplorer::isEnabled()) {
            vert_sep_1 = (vert_sep_1 >= MIN_WH) ? vert_sep_1 : MIN_WH;

            if (!resize_horiz_sep_1 && !resize_vert_sep_2 && !no_resizing) update_vert_sep(&(vert_sep_1),
                MenuBar::getWindowPos().y + MenuBar::getWindowSize().y,
                ImGui::GetIO().DisplaySize.y,
                &(resize_vert_sep_1), 
                MIN_WH, 
                vert_sep_2 - MIN_WH);
        }
        else vert_sep_1 = 0;

        if(CodePreview::isEnabled()) {
            vert_sep_2 = (vert_sep_2 >= vert_sep_1 + MIN_WH && vert_sep_2 <= ImGui::GetIO().DisplaySize.x - MIN_WH) ? 
                vert_sep_2 : ImClamp((ImGui::GetIO().DisplaySize.x - vert_sep_1) / 2, vert_sep_1 + MIN_WH, ImGui::GetIO().DisplaySize.x - MIN_WH);
                
            if(!resize_horiz_sep_1 && !resize_vert_sep_1 && !no_resizing) update_vert_sep(&(vert_sep_2), 
                MenuBar::getWindowPos().y + MenuBar::getWindowSize().y,
                Score::getWindowPos().y,
                &(resize_vert_sep_2), 
                vert_sep_1 + MIN_WH, 
                ImGui::GetIO().DisplaySize.x - MIN_WH);
        }
        else vert_sep_2 = ImGui::GetIO().DisplaySize.x;

        if(Score::isEnabled()) {
            horiz_sep_1 = (horiz_sep_1 < ImGui::GetIO().DisplaySize.y - MIN_WH) ? 
                horiz_sep_1 : ImGui::GetIO().DisplaySize.y - MIN_WH;

            if(!resize_vert_sep_1 && !resize_vert_sep_2 && !no_resizing) update_horiz_sep(&(horiz_sep_1),
                Score::getWindowPos().x,
                ImGui::GetIO().DisplaySize.x,
                &(resize_horiz_sep_1),
                MenuBar::getWindowSize().y + MIN_WH,
                ImGui::GetIO().DisplaySize.y - MIN_WH);
        }
        else horiz_sep_1 = ImGui::GetIO().DisplaySize.y;

        // if(!NodeEditor::isEnabled()) vert_sep_2 = vert_sep_1;

        MenuBar::render();

        FolderSelector::render();

        FileExplorer::render();

        Score::render();

        NodeEditor::render();

        CodePreview::render();

        imgui_render_frame(window, &display_w, &display_h);
    }

    graphics_cleanup(window);

    return EXIT_SUCCESS;
}