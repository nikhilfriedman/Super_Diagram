#ifndef MENUBAR_H
#define MENUBAR_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include "TextEditor.h"

#include "imgui_helpers.h"

#include "FolderSelector.h"
#include "FileExplorer.h"
#include "Score.h"
#include "CodePreview.h"

#include <iostream>

class MenuBar {
    public:
        MenuBar(ImVec2 window_size, ImVec2 window_pos, GLFWwindow * window);
        ~MenuBar();

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