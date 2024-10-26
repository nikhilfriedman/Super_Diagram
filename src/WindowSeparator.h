#ifndef WINDOWSEPARATOR_H
#define WINDOWSEPARATOR_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include <iostream>

typedef enum Separator_Orientation {   
    VERTICAL,
    HORIZONTAL
} Separator_Orientation;

class WindowSeparator {
    public:
        WindowSeparator(Separator_Orientation orientation, float value, int e_size);
        ~WindowSeparator();

        void update(float value_min, float value_max, float hitbox_min, float hitbox_max);
        void setValue(float v);

        void enable();
        void disable();

        bool isEnabled();
        bool isUpdating();

        float getValue();

        float getValueMin();
        float getValueMax();

        float getHitboxMin();
        float getHitboxMax();

    private:
        Separator_Orientation orientation;
        
        float value;

        float hitbox_min;
        float hitbox_max;
        
        float value_min;
        float value_max;

        int edge_size;

        bool enabled;
        bool updating;
};

#endif