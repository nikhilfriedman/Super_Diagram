#include "imgui_helpers.h"

extern ImFont * sans_bold;
extern ImFont * cousine;

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

ImGuiIO& create_imgui_context(GLFWwindow * window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();

    io.Fonts -> Clear();
    // io.Fonts -> AddFontFromFileTTF("../external/fonts/WorkSans-Bold.ttf", 16.0f);
    // io.Fonts -> AddFontFromFileTTF("../external/fonts/Cousine-Bold.ttf", 16.0f);

    sans_bold  = io.Fonts->AddFontFromFileTTF("../external/fonts/WorkSans-Bold.ttf", 16.0f);
    cousine    = io.Fonts->AddFontFromFileTTF("../external/fonts/Cousine-Bold.ttf", 16.0f);

    io.Fonts -> Build();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImNodes::CreateContext();

    return io;
}

void graphics_cleanup(GLFWwindow * window)
{
    ImNodes::DestroyContext();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void imgui_init_render()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_render_frame(GLFWwindow * window, int * display_w, int * display_h)
{
    ImGui::Render();
    glfwGetFramebufferSize(window, display_w, display_h);
    glViewport(0, 0, * display_w, * display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void check_window_resize(int display_w, int display_h, int * prev_display_w, int * prev_display_h, bool * window_resize)
{
    * window_resize = (display_w != * prev_display_w || display_h != * prev_display_h) ? true : false;

    * prev_display_w = display_w;
    * prev_display_h = display_h;
}

bool on_edge_of_window(Window_Edge edge, ImVec2 * window_pos, ImVec2 * window_size)
{
    ImVec2 mouse_pos = ImGui::GetMousePos();

    switch(edge)
    {
        case NORTH:
            if(mouse_pos.x >= window_pos -> x && mouse_pos.x <= (window_pos -> x + window_size -> x))
            {
                if(abs(mouse_pos.y - window_pos -> y) <= EDGE_SIZE)
                {
                    return true;
                }
            }
            break;
        case EAST:
            if(mouse_pos.y >= window_pos -> y && mouse_pos.y <= (window_pos -> y + window_size -> y))
            {
                if(abs(mouse_pos.x - (window_pos -> x + window_size -> x)) <= EDGE_SIZE)
                {
                    return true;
                }
            }
            break;
        case SOUTH:
            if(mouse_pos.x >= window_pos -> x && mouse_pos.x <= (window_pos -> x + window_size -> x))
            {
                if(abs(mouse_pos.y - (window_pos -> y + window_size -> y)) <= EDGE_SIZE)
                {
                    return true;
                }
            }
            break;
        case WEST:
            if(mouse_pos.y >= window_pos -> y && mouse_pos.y <= (window_pos -> y + window_size -> y))
            {
                if(abs(mouse_pos.x - window_pos -> x) <= EDGE_SIZE)
                {
                    return true;
                }
            }
            break;
        default:
            return false;
    }

    return false;
}

void update_vert_sep(float * value, float y_min, float y_max, bool * changing, float min, float max)
{
    if(* changing) * value = ImClamp(* value + ImGui::GetIO().MouseDelta.x, min, max);

    ImVec2 mouse_pos = ImGui::GetMousePos();

    if(abs(mouse_pos.x - (* value)) <= EDGE_SIZE && mouse_pos.y >= y_min && mouse_pos.y <= y_max)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        if(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            * changing = true;
        }
    }

    if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)) * changing = false;
}

void update_horiz_sep(float * value, float x_min, float x_max, bool * changing, float min, float max)
{
    if(* changing) * value = ImClamp(* value + ImGui::GetIO().MouseDelta.y, min, max);

    ImVec2 mouse_pos = ImGui::GetMousePos();

    if(abs(mouse_pos.y - (* value)) <= EDGE_SIZE && mouse_pos.x >= x_min && mouse_pos.x <= x_max)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        if(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            * changing = true;
        }
    }

    if(!ImGui::IsMouseDown(ImGuiMouseButton_Left)) * changing = false;
}