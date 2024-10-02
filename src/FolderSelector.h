#ifndef FOLDERSELECTOR_H
#define FOLDERSELECTOR_H

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
        
        static void enable();
        static void render();


    private:

        static void draw_directory(std::string const& current_path);

        static int window_width;
        static int window_height;

        static bool enabled;

        static std::string selected_folder_path;
        static std::string selected_folder_name;

        static GLFWwindow * window;
};

#endif