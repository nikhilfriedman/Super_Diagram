#include "CodePreview.h"

bool CodePreview::enabled = false;

ImVec2 CodePreview::window_size = ImVec2(0, 0);
ImVec2 CodePreview::window_pos = ImVec2(0, 0);

TextEditor * CodePreview::editor = nullptr;

GLFWwindow * CodePreview::window = nullptr;

extern float vert_sep_1;
extern float vert_sep_2;
extern float horiz_sep_1;

extern ImFont * cousine;

CodePreview::CodePreview(ImVec2 ws, ImVec2 wp, TextEditor * e, GLFWwindow * w) {
    window_size = ws;
    window_pos  = wp;
    editor      = e;
    window      = w;

    enabled = true;
}

void CodePreview::render() {
    if(enabled) {
        window_pos  = ImVec2(vert_sep_2, MenuBar::getWindowSize().y);
        window_size = ImVec2(ImGui::GetIO().DisplaySize.x - vert_sep_2,
            horiz_sep_1 - MenuBar::getWindowSize().y);

        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

        ImGui::Begin("Editor", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        
        ImGui::Text("Code Preview");

        ImGui::PushFont(cousine);

        (* editor).Render("Text Editor");

        ImGui::PopFont();

        window_size = ImGui::GetWindowSize();
        window_pos  = ImGui::GetWindowPos();

        ImGui::End();
    }
}

std::string CodePreview::readFileToString(const std::string& filepath) {
    std::ifstream file(filepath);

    if(!file.is_open()) {
        return "";
    }

    std::string file_content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    file.close();
    return file_content;
}

void CodePreview::loadFile(const std::string& filepath) {
    try {
        editor->SetText(readFileToString(filepath));
    } catch(const std::exception& e) {
        editor->SetText(e.what());
    }
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