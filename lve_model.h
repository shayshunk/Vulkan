#pragma once

// C++ includes
#include <vector>

// Custom includes
#include "lve_device.h"

// Vulkan
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace lve
{
class LveModel
{
  public:
    struct Vertex
    {
        glm::vec2 position;

        static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
    };

    LveModel(LveDevice& device, std::vector<Vertex> const& vertices);
    ~LveModel();

    LveModel(LveModel const&) = delete;
    LveModel& operator=(LveModel const&) = delete;

    void Bind(VkCommandBuffer commandBuffer);
    void Draw(VkCommandBuffer commandBuffer);

  private:
    void CreateVertexBuffers(std::vector<Vertex> const& vertices);

    LveDevice& lveDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
};
}  // namespace lve
