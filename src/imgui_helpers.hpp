#ifndef IMGUI_HELPERS_HPP
#define IMGUI_HELPERS_HPP

#define IMGUI_DEFINE_MATH_OPERATORS true

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include "ImGuiFileDialog.h"

#include <iostream>

#define MIN_WH 150
#define EDGE_SIZE 5

typedef struct Window_Neighbor_Info
{
    bool resize_vert_sep_1;
    bool resize_vert_sep_2;
    bool resize_horiz_sep_1;

    bool no_resizing;

    bool viewing_file_explorer;
    bool viewing_score;
    bool viewing_code_preview;

    ImVec2 size_menu_bar;
    ImVec2 size_file_explorer;
    ImVec2 size_score;
    ImVec2 size_node_editor;
    ImVec2 size_code_preview;

    ImVec2 pos_menu_bar;
    ImVec2 pos_file_explorer;
    ImVec2 pos_score;
    ImVec2 pos_node_editor;
    ImVec2 pos_code_preview;

    float vert_sep_1;
    float vert_sep_2;
    float horiz_sep_1;
} Window_Neighbor_Info;

typedef enum Window_Edge
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
} Window_Edge;

void glfw_error_callback(int error, const char* description);
ImGuiIO& create_imgui_context(GLFWwindow * window);
void graphics_cleanup(GLFWwindow * window);
void imgui_init_render();
void imgui_render_frame(GLFWwindow * window, int * display_w, int * display_h);
void check_window_resize(int display_w, int display_h, int * prev_display_w, int * prev_display_h, bool * window_resize);
bool on_edge_of_window(Window_Edge edge, ImVec2 * window_pos, ImVec2 * window_size);
void update_vert_sep(float * value, float y_min, float y_max, bool * changing, float min, float max);
void update_horiz_sep(float * value, float x_min, float x_max, bool * changing, float min, float max);

#endif