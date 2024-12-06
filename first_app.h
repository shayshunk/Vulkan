#pragma once

// Custom includes
#include "lve_device.h"
#include "lve_model.h"
#include "lve_pipeline.h"
#include "lve_swap_chain.h"
#include "lve_window.h"

// C++ includes
#include <memory>
#include <vector>

namespace lve
{
class FirstApp
{
  public:
    // Window size
    static constexpr int WIDTH = 1200;
    static constexpr int HEIGHT = 1200;

    FirstApp();
    ~FirstApp();

    FirstApp(FirstApp const&) = delete;
    FirstApp& operator=(FirstApp const&) = delete;

    void Run();

  private:
    // Functions
    void LoadModels();
    std::vector<LveModel::Vertex> SierpinskiTriangle(int depth);
    std::vector<LveModel::Vertex> SplitTriangle(int depth, std::vector<glm::vec2> bounds);
    void CreatePipelineLayout();
    void CreatePipeline();
    void CreateCommandBuffers();
    void DrawFrame();

    LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
    LveDevice lveDevice{lveWindow};
    LveSwapChain lveSwapChain{lveDevice, lveWindow.GetExtent()};

    // Smart pointer for the pipeline
    std::unique_ptr<LvePipeline> lvePipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;

    std::unique_ptr<LveModel> lveModel;
};
}  // namespace lve