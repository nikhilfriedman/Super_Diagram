#ifndef FOLDER_SELECTION_H
#define FOLDER_SELECTION_H

#define IMGUI_DEFINE_MATH_OPERATORS true

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imgui_helpers.h"

#include <iostream>
#include <filesystem>

class FolderSelector {
    public:
        FolderSelector(int width, int height);
        ~FolderSelector();
        
        void enable_folder_select();
        void draw_folder_select(GLFWwindow * window, std::string * path);
    private:
        // window size
        int window_width;
        int window_height;

        // drawing? 
        bool enabled;
};

#endif