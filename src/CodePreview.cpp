#include "CodePreview.h"

bool CodePreview::enabled = false;

ImVec2 CodePreview::window_size = ImVec2(0, 0);
ImVec2 CodePreview::window_pos = ImVec2(0, 0);

TextEditor * CodePreview::editor = nullptr;

GLFWwindow * CodePreview::window = nullptr;

extern float vert_sep_1;
extern float vert_sep_2;
extern float horiz_sep_1;

CodePreview::CodePreview(ImVec2 ws, ImVec2 wp, TextEditor * e, GLFWwindow * w) {
    window_size = ws;
    window_pos  = wp;
    editor      = e;
    window      = w;

    enabled = true;
}

void CodePreview::render() {
    window_pos  = ImVec2(vert_sep_2, MenuBar::getWindowSize().y);
    window_size = ImVec2(ImGui::GetIO().DisplaySize.x - vert_sep_2,
        horiz_sep_1 - MenuBar::getWindowSize().y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Editor", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Code Preview");

    (* editor).Render("Text Editor");

    window_size = ImGui::GetWindowSize();
    window_pos  = ImGui::GetWindowPos();

    ImGui::End();
}

void CodePreview::enable() {
    enabled = true;
}

void CodePreview::disable() {
    enabled = false;
}

bool CodePreview::isEnabled() {
    return enabled;
}

ImVec2 CodePreview::getWindowSize() {
    return window_size;
}

ImVec2 CodePreview::getWindowPos() {
    return window_pos;
}

CodePreview::~CodePreview() {

}