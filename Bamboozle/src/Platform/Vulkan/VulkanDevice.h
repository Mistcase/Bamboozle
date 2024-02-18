#pragma once

#include "Bamboozle/Renderer/Device.h"
#include "Bamboozle/Window.h"

#include "Platform/Vulkan/VulkanContext.h"
#include "VulkanSwapChain.h"

namespace bbzl
{
    class VulkanDevice : public VidDeviceInterface
    {
    public:
        struct SwapChainSupportDetails
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        struct QueueFamilyIndices
        {
            uint32_t graphicsFamily;
            uint32_t presentFamily;
            bool graphicsFamilyHasValue = false;
            bool presentFamilyHasValue = false;
            bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
        };

    public:
        VulkanDevice(Window& window);
        ~VulkanDevice();

        VulkanDevice(const VulkanDevice&) = delete;
        VulkanDevice(VulkanDevice&&) = delete;
        VulkanDevice& operator=(const VulkanDevice&) = delete;
        VulkanDevice& operator=(VulkanDevice&&) = delete;

        VulkanSwapChain& getSwapChain() const { ASSERT(m_swapChain, "Swap chain is null!"); return *m_swapChain; }
        VkCommandPool getCommandPool() const { return commandPool; }
        VkDevice getNativeDevice() const { return device; }
        VkSurfaceKHR getNativeSurface() const { return surface; }
        VkQueue getNativeGraphicsQueue() const { return graphicsQueue; }
        VkQueue getNativePresentQueue() const { return presentQueue; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;

        // Buffer Helper Functions
        void createBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        void createImageWithInfo( const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

        VkPhysicalDeviceProperties properties;

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();
        void createSwapChain();

        // helper functions
        bool isDeviceSuitable(VkPhysicalDevice VulkanDevice);
        std::vector<const char*> getRequiredExtensions() const;
        bool checkValidationLayerSupport();
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice VulkanDevice);
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void checkGflwRequiredInstanceExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice VulkanDevice);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice VulkanDevice);

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        Window& m_window;
        VkCommandPool commandPool;

        VkDevice device;
        VkSurfaceKHR surface;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

        std::unique_ptr<VulkanSwapChain> m_swapChain;

        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        
#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = false;
#endif
    };

} // namespace bbzl
