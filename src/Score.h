#ifndef SCORE_H
#define SCORE_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include "ImGuiFileDialog.h"

#include <iostream>

#include "imgui_helpers.h"

class Score {
    public:
        Score(ImVec2 window_size, ImVec2 window_pos, GLFWwindow * window);
        ~Score();

        static void render();
        static void enable();
        static void disable();

        static bool isEnabled();

        static ImVec2 getWindowSize();
        static ImVec2 getWindowPos();
    
    private:
        static GLFWwindow * window;

        static ImVec2 window_size;
        static ImVec2 window_pos;

        static bool enabled;

};

#endif