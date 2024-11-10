#include "lve_window.h"

namespace lve
{

LveWindow::LveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName(name)
{
    InitWindow();
}

LveWindow::~LveWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void LveWindow::InitWindow()
{
    // Initilizaing GLFW
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Creating window
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

}  // namespace lve