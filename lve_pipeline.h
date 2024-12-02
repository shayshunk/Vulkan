#pragma once

// Custom includes
#include "lve_device.h"

// C++ includes
#include <cassert>
#include <string>
#include <vector>

namespace lve
{

struct PipelineConfigInfo
{
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;

    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;

    uint32_t subpass = 0;
};

class LvePipeline
{
  public:
    LvePipeline(LveDevice& device,
                std::string const& vertFilepath,
                std::string const& fragFilepath,
                PipelineConfigInfo const& configInfo);

    ~LvePipeline();

    LvePipeline(LvePipeline const&) = delete;
    void operator=(LvePipeline const&) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);

  private:
    static std::vector<char> ReadFile(std::string const& filepath);

    void CreateGraphicsPipeline(std::string const& vertFilepath,
                                std::string const& fragFilepath,
                                PipelineConfigInfo const& configInfo);

    void CreateShaderModule(std::vector<char> const& code, VkShaderModule* shaderModule);

    LveDevice& lveDevice;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};
}  // namespace lve