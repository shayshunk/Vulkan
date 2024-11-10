#pragma once

// Custom includes
#include "lve_device.h"

// C++ includes
#include <string>
#include <vector>

namespace lve
{

struct PipelineConfigInfo
{
};

class LvePipeline
{
  public:
    LvePipeline(LveDevice& device,
                std::string const& vertFilepath,
                std::string const& fragFilepath,
                PipelineConfigInfo const& configInfo);

    ~LvePipeline() {};

    LvePipeline(LvePipeline const&) = delete;
    void operator=(LvePipeline const&) = delete;

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

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