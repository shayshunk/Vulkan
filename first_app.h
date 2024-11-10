#pragma once

#include "lve_device.h"
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
    LveDevice lveDevice{lveWindow};
    LvePipeline lvePipeline{lveDevice,
                            "shaders/simple_shader.vert.spv",
                            "shaders/simple_shader.frag.spv",
                            LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};
}  // namespace lve