#ifndef FOLDER_SELECTION_H
#define FOLDER_SELECTION_H

#define IMGUI_DEFINE_MATH_OPERATORS

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
        FolderSelector(int width, int height, std::string path, GLFWwindow * window);
        ~FolderSelector();
        
        static void enable_folder_select();
        static void draw_folder_select(std::string * path);
    private:
        // window size
        static int window_width;
        static int window_height;

        // drawing? 
        static bool enabled;

        // file system
        static std::string selected_folder_path;
        static std::string selected_folder_name;

        // glfw
        static GLFWwindow * window;
};

#endif