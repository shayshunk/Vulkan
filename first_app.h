#pragma once

#include "lve_pipeline.h"
#include "lve_window.h"

namespace lve
{
class FirstApp
{
  public:
    static constexpr int WIDTH = 1600;
    static constexpr int HEIGHT = 900;

    void run();

  private:
    LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
    LvePipeline lvePipeline{"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv"};
};
}  // namespace lve