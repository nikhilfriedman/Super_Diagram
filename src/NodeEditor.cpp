#include "NodeEditor.h"

bool NodeEditor::enabled = false;

ImVec2 NodeEditor::window_size = ImVec2(0, 0);
ImVec2 NodeEditor::window_pos = ImVec2(0, 0);

GLFWwindow * NodeEditor::window = nullptr;

extern float vert_sep_1;
extern float vert_sep_2;
extern float horiz_sep_1;

NodeEditor::NodeEditor(ImVec2 ws, ImVec2 wp, GLFWwindow * w) {
    window_size = ws;
    window_pos = wp;
    window = w;

    enabled = true;
}

void NodeEditor::render() {
    window_pos  = ImVec2(vert_sep_1, MenuBar::getWindowSize().y);
    window_size = ImVec2(vert_sep_2 - vert_sep_1,
        horiz_sep_1 - MenuBar::getWindowSize().y);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Nodes", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImGui::Text("Node Editor");

    ImNodes::BeginNodeEditor();

    ImNodes::BeginNode(2); // TODO : FIX LATER
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("test node");
    ImNodes::EndNodeTitleBar();

    ImGui::Dummy(ImVec2(80.0f, 45.0f));

    ImNodes::EndNode();

    ImNodes::EndNodeEditor();

    window_size = ImGui::GetWindowSize();
    window_pos  = ImGui::GetWindowPos();

    ImGui::End();
}

void NodeEditor::enable() {
    enabled = true;
}

void NodeEditor::disable() {
    enabled = false;
}

bool NodeEditor::isEnabled() {
    return enabled;
}

ImVec2 NodeEditor::getWindowSize() {
    return window_size;
}

ImVec2 NodeEditor::getWindowPos() {
    return window_pos;
}

NodeEditor::~NodeEditor() {

}