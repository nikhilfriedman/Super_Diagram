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

std::vector<std::string> NodeEditor::getFunctionsFromFile(std::string file) {
    std::regex function_names_regex(R"(\b(\w+)\s*\(\)\s*;)");

    std::vector<std::string> functions;
    std::smatch match;

    std::string::const_iterator search(file.cbegin());
    while(std::regex_search(search, file.cend(), match, function_names_regex)) {
        functions.push_back(match[1]);
        search = match.suffix().first;
    }

    return functions;
}

void NodeEditor::render() {
    if(enabled) {
        window_pos  = ImVec2(vert_sep_1, MenuBar::getWindowSize().y);
        window_size = ImVec2(vert_sep_2 - vert_sep_1,
            horiz_sep_1 - MenuBar::getWindowSize().y);

        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

        ImGui::Begin("Nodes", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        ImGui::Text("Node Editor");

        ImNodes::BeginNodeEditor();

        std::vector<std::string> functions = getFunctionsFromFile(CodePreview::getText());

        int ct = 0;
        for(std::string s : functions) {
            ImNodes::BeginNode(ct);
            ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(s.c_str());
            ImNodes::EndNodeTitleBar();
            ImGui::Dummy(ImVec2(80.0f, 45.0f));
            ImNodes::EndNode();

            ImNodes::SetNodeEditorSpacePos(ct, ImVec2(ct * 150, 0));
            ct++;
        }

        // ImNodes::BeginNode(2); // TODO : FIX LATER
        // ImNodes::BeginNodeTitleBar();
        // ImGui::TextUnformatted("test node");
        // ImNodes::EndNodeTitleBar();

        // ImGui::Dummy(ImVec2(80.0f, 45.0f));

        // ImNodes::EndNode();

        ImNodes::EndNodeEditor();

        window_size = ImGui::GetWindowSize();
        window_pos  = ImGui::GetWindowPos();

        ImGui::End();
    }
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