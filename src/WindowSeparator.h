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
        WindowSeparator(Separator_Orientation orientation, float value, 
            float hb_min, float hb_max, float v_min, float v_max);
        ~WindowSeparator();

        void update();

        void enable();
        void disable();

        bool isEnabled();

        float getValue();

        float getValueMin();
        float getValueMax();

        float getHitboxMin();
        float getHitboxMax();

    private:
        Separator_Orientation   orientation;
        
        float value;

        float hitbox_min;
        float hitbox_max;
        
        float value_min;
        float value_max;

        bool enabled;
        bool updating;
};

#endif