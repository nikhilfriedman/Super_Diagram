#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#define IMGUI_DEFINE_MATH_OPERATORS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imnodes.h"
#include "imnodes_internal.h"

#include <iostream>
#include <regex>
#include <vector>

#include "imgui_helpers.h"

#include "MenuBar.h"
#include "TextEditor.h"

class NodeEditor {
    public:
        NodeEditor(ImVec2 window_size, ImVec2 window_pos, GLFWwindow * window);
        ~NodeEditor();

        static void render();
        static void enable();
        static void disable();

        static bool isEnabled();

        static ImVec2 getWindowSize();
        static ImVec2 getWindowPos();

    private:
        static std::vector<std::string> getFunctionsFromFile(std::string file);

        static GLFWwindow * window;

        static ImVec2 window_size;
        static ImVec2 window_pos;

        static bool enabled;

};

#endif