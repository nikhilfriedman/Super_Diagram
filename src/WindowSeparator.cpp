#include "WindowSeparator.h"

WindowSeparator::WindowSeparator(Separator_Orientation o,
    float v, float hb_min, float hb_max, float v_min, float v_max) {

    orientation = o;
    value       = v;
    hitbox_min  = hb_min;
    hitbox_max  = hb_max;
    value_min   = v_min;
    value_max   = v_max;

    enabled     = true;
    updating    = false;
}


/*
void update_vert_sep(float * value, float y_min, float y_max, bool * changing, float min, float max)
{
    if(* changing) * value = ImClamp(* value + ImGui::GetIO().MouseDelta.x, min, max);

    ImVec2 mouse_pos = ImGui::GetMousePos();

    if(abs(mouse_pos.x - (* value)) <= EDGE_SIZE && mouse_pos.y >= y_min && mouse_pos.y <= y_max)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        if(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            * changing = true;
        }
    }

    if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)) * changing = false;
}

                    ^
                    |
implement this lol  |
*/
void WindowSeparator::update() {
    if(enabled) {
        if(orientation == VERTICAL) {
            if(updating) value = 0; //TODO : FINISH
        } else {

        }     
    }
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