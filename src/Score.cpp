#include "Score.h"

bool Score::enabled = false;

ImVec2 Score::window_size = ImVec2(0, 0);
ImVec2 Score::window_pos = ImVec2(0, 0);

GLFWwindow * Score::window = nullptr;

extern float vert_sep_1;
extern float vert_sep_2;
extern float horiz_sep_1;

Score::Score(ImVec2 ws, ImVec2 wp, GLFWwindow * w) {
    window_size = ws;
    window_pos = wp;
    window = w;

    enabled = true;
}

void Score::render() {
    window_pos = ImVec2(vert_sep_1, horiz_sep_1);
    window_size = ImVec2(
        ImGui::GetIO().DisplaySize.x - vert_sep_1,
        ImGui::GetIO().DisplaySize.y - horiz_sep_1
    );

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Score", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Score");

    window_size = ImGui::GetWindowSize();
    window_pos  = ImGui::GetWindowPos();

    ImGui::End();
}

void Score::enable() {
    enabled = true;
}

void Score::disable() {
    enabled = false;
}

bool Score::isEnabled() {
    return enabled;
}

ImVec2 Score::getWindowSize() {
    return window_size;
}

ImVec2 Score::getWindowPos() {
    return window_pos;
}

Score::~Score() {

}