#include "WindowSeparator.h"

WindowSeparator::WindowSeparator(Separator_Orientation o, float v, int e_size) {
    orientation = o;
    value       = v;
    edge_size   = e_size;

    enabled     = true;
    updating    = false;
}

void WindowSeparator::update(float value_min, float value_max, float hitbox_min, float hitbox_max) {
    if(enabled) {
        ImVec2 mouse_pos = ImGui::GetMousePos();

        if(orientation == VERTICAL) {
            if(updating) value = ImClamp(value + ImGui::GetIO().MouseDelta.x, value_min, value_max);

            if(abs(mouse_pos.x - value) <= edge_size && mouse_pos.y >= hitbox_min && mouse_pos.y <= hitbox_max) {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

                if(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                    updating = true;
                }
            }

            if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)) updating = false;
        } else {
            if(updating) value = ImClamp(value + ImGui::GetIO().MouseDelta.y, value_min, value_max);

            if(abs(mouse_pos.y - value) <= edge_size && mouse_pos.x >= hitbox_min && mouse_pos.x <= hitbox_max) {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

                if(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                    updating = true;
                }
            }

            if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)) updating = false;
        }     
    } else value = 0;
}

void WindowSeparator::setValue(float v) {
    value = v;
}

void WindowSeparator::enable() {
    enabled = true;
}

void WindowSeparator::disable() {
    enabled = false;
}

bool WindowSeparator::isEnabled() {
    return enabled;
}

bool WindowSeparator::isUpdating() {
    return updating;
}

float WindowSeparator::getValue() {
    return value;
}

float WindowSeparator::getValueMin() {
    return value_min;
}

float WindowSeparator::getValueMax() {
    return value_max;
}

float WindowSeparator::getHitboxMin() {
    return hitbox_min;
}

float WindowSeparator::getHitboxMax() {
    return hitbox_max;
}

WindowSeparator::~WindowSeparator() {
    
}