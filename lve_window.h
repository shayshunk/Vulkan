#pragma once

#define GLFW_INCLUDE_VULKAN

// External includes
#include <GLFW/glfw3.h>

// C++ includes
#include <string>

namespace lve
{

class LveWindow
{
  public:
    LveWindow(int w, int h, std::string name);
    ~LveWindow();

    bool ShouldClose() { return glfwWindowShouldClose(window); }

    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

  private:
    void InitWindow();

    // Window variables
    int const width;
    int const height;

    std::string windowName;

    GLFWwindow* window;
};
}  // namespace lve