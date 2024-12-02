#pragma once

#include "lve_device.h"

// vulkan headers
#include <vulkan/vulkan.h>

// C++ includes
#include <string>
#include <vector>

namespace lve
{

class LveSwapChain
{
  public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    LveSwapChain(LveDevice& deviceRef, VkExtent2D windowExtent);
    ~LveSwapChain();

    LveSwapChain(LveSwapChain const&) = delete;
    void operator=(LveSwapChain const&) = delete;

    VkFramebuffer GetFrameBuffer(int index) { return swapChainFramebuffers[index]; }
    VkRenderPass GetRenderPass() { return renderPass; }
    VkImageView getImageView(int index) { return swapChainImageViews[index]; }
    size_t ImageCount() { return swapChainImages.size(); }
    VkFormat GetSwapChainImageFormat() { return swapChainImageFormat; }
    VkExtent2D GetSwapChainExtent() { return swapChainExtent; }
    uint32_t width() { return swapChainExtent.width; }
    uint32_t height() { return swapChainExtent.height; }

    float extentAspectRatio() { return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height); }
    VkFormat findDepthFormat();

    VkResult AcquireNextImage(uint32_t* imageIndex);
    VkResult SubmitCommandBuffers(VkCommandBuffer const* buffers, uint32_t* imageIndex);

  private:
    void CreateSwapChain();
    void CreateImageViews();
    void CreateDepthResources();
    void CreateRenderPass();
    void CreateFramebuffers();
    void CreateSyncObjects();

    // Helper functions
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(std::vector<VkPresentModeKHR> const& availablePresentModes);
    VkExtent2D ChooseSwapExtent(VkSurfaceCapabilitiesKHR const& capabilities);

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkRenderPass renderPass;

    std::vector<VkImage> depthImages;
    std::vector<VkDeviceMemory> depthImageMemorys;
    std::vector<VkImageView> depthImageViews;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;

    LveDevice& device;
    VkExtent2D windowExtent;

    VkSwapchainKHR swapChain;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;
};

}  // namespace lve