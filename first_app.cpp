// Custom headers
#include "first_app.h"

// C++ headers
#include <array>
#include <stdexcept>

namespace lve
{

FirstApp::FirstApp()
{
    LoadModels();
    CreatePipelineLayout();
    CreatePipeline();
    CreateCommandBuffers();
}

FirstApp::~FirstApp()
{
    vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
}

void FirstApp::Run()
{
    while (!lveWindow.ShouldClose())
    {
        glfwPollEvents();
        DrawFrame();
    }

    vkDeviceWaitIdle(lveDevice.device());
}

void FirstApp::LoadModels()
{
    std::vector<LveModel::Vertex> vertices{{{0.0f, -0.5f}}, {{0.5f, 0.5f}}, {{-0.5f, 0.5f}}};

    lveModel = std::make_unique<LveModel>(lveDevice, vertices);
}

void FirstApp::CreatePipelineLayout()
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void FirstApp::CreatePipeline()
{
    auto pipelineConfig = LvePipeline::DefaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
    pipelineConfig.renderPass = lveSwapChain.GetRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    lvePipeline = std::make_unique<LvePipeline>(
        lveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
}

void FirstApp::CreateCommandBuffers()
{
    commandBuffers.resize(lveSwapChain.ImageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = lveDevice.GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate command bufffers!");
    }

    for (int i = 0; i < commandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = lveSwapChain.GetRenderPass();
        renderPassInfo.framebuffer = lveSwapChain.GetFrameBuffer(i);
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = lveSwapChain.GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        lvePipeline->Bind(commandBuffers[i]);
        lveModel->Bind(commandBuffers[i]);
        lveModel->Draw(commandBuffers[i]);

        vkCmdEndRenderPass(commandBuffers[i]);
        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }
}

void FirstApp::DrawFrame()
{
    uint32_t imageIndex;
    auto result = lveSwapChain.AcquireNextImage(&imageIndex);

    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Failed to acquire swap chain image!");
    }

    result = lveSwapChain.SubmitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to present swap chain image!");
    }
}

}  // namespace lve