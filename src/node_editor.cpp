#include "node_editor.h"

void draw_node_editor(int hardcoded_node_id, Window_Neighbor_Info * wni)
{
    ImVec2 window_pos = ImVec2(
        wni -> vert_sep_1,
        (wni -> size_menu_bar).y
    );

    ImVec2 window_size = ImVec2(
        wni -> vert_sep_2 - wni -> vert_sep_1,
        wni -> horiz_sep_1 - (wni -> size_menu_bar).y
    );

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

    ImGui::Begin("Nodes", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImGui::Text("Node Editor");

    ImNodes::BeginNodeEditor();

    ImNodes::BeginNode(hardcoded_node_id);
    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("test node");
    ImNodes::EndNodeTitleBar();

    ImGui::Dummy(ImVec2(80.0f, 45.0f));

    ImNodes::EndNode();

    ImNodes::EndNodeEditor();

    wni -> size_node_editor = ImGui::GetWindowSize();
    wni -> pos_node_editor = ImGui::GetWindowPos();

    ImGui::End();
}