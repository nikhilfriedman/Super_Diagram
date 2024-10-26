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
        FolderSelector(ImVec2 window_size, ImVec2 window_pos, std::string path, GLFWwindow * window);
        ~FolderSelector();
        
        static void render();
        static void enable();
        static void disable();

        static std::string getFolderPath();
        static std::string getFolderName();

        static bool isEnabled();

        static bool isFolderSelected();

        static ImVec2 getWindowSize();
        static ImVec2 getWindowPos();

    private:
        static void drawDirectory(std::string const& current_path);


        static GLFWwindow * window;

        static ImVec2 window_size;
        static ImVec2 window_pos;

        static bool enabled;

        static bool folder_selected;

        static std::string selected_folder_path;
        static std::string selected_folder_name;

};

#endif