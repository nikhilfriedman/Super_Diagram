#ifndef CODEPREVIEW_H
#define CODEPREVIEW_H

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

#include "MenuBar.h"

#include <iostream>
#include <fstream>

class CodePreview {
    public:
        CodePreview(ImVec2 window_size, ImVec2 window_pos, TextEditor * editor, GLFWwindow * window);
        ~CodePreview();

        static void render();
        static void enable();
        static void disable();

        static void loadFile(const std::string& filepath);

        static bool isEnabled();

        static std::string getText();

        static ImVec2 getWindowSize();
        static ImVec2 getWindowPos();

        static std::string getCurrentFilepath();

    private:
        static std::string readFileToString(const std::string& filepath);

        static GLFWwindow * window;

        static TextEditor * editor;

        static ImVec2 window_size;
        static ImVec2 window_pos;

        static bool enabled;

        static std::string selected_file_path;

};

#endif