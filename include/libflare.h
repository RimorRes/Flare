#ifndef FLARE_LIBRARY_H
#define FLARE_LIBRARY_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vertex.h"

#include <vector>
#include <optional>
#include <string>

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif


constexpr uint32_t WIDTH = 2560;// 800;
constexpr uint32_t HEIGHT = 1440;// 600;

const std::string MODEL_PATH = "data/models/viking_room.obj";
const std::string TEXTURE_PATH = "data/textures/viking_room.png";

constexpr int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_MULTIVIEW_EXTENSION_NAME
};

const std::vector<const char*> instanceExtensions = {
    VK_KHR_DISPLAY_EXTENSION_NAME,
    VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME
};


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    [[nodiscard]] bool isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

std::vector<char> readFile(const std::string& filename);

bool checkValidationLayerSupport();

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);


class TriangleApp {

public:
    bool interrupt = false;
    void run();

private:
    GLFWwindow* window = nullptr;

    VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

    VkSurfaceKHR surface = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;

    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;  // TODO: dedicated queue family for transfer if supported on dGPU

    VkSwapchainKHR swapChain = VK_NULL_HANDLE;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
    VkExtent2D swapChainExtent = {};
    std::vector<VkImageView> swapChainImageViews;

    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkCommandPool commandPool = VK_NULL_HANDLE; // TODO: add dedicated transfer command pool (VK_COMMAND_POOL_CREATE_TRANSIENT_BIT flag)

    VkImage depthImage = VK_NULL_HANDLE;
    VkDeviceMemory depthImageMemory = VK_NULL_HANDLE;
    VkImageView depthImageView = VK_NULL_HANDLE;

    VkImage textureImage = VK_NULL_HANDLE;
    VkDeviceMemory textureImageMemory = VK_NULL_HANDLE;
    VkImageView textureImageView = VK_NULL_HANDLE;
    VkSampler textureSampler = VK_NULL_HANDLE;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
    VkBuffer indexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

    std::vector<VkBuffer> uniformBuffers = std::vector<VkBuffer>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);
    std::vector<VkDeviceMemory> uniformBuffersMemory = std::vector<VkDeviceMemory>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);
    std::vector<void*> uniformBuffersMapped = std::vector<void*>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);

    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    std::vector<VkDescriptorSet> descriptorSets = std::vector<VkDescriptorSet>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);

    std::vector<VkCommandBuffer> commandBuffers = std::vector<VkCommandBuffer>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);

    std::vector<VkSemaphore> imageAvailableSemaphores = std::vector<VkSemaphore>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);
    std::vector<VkSemaphore> renderFinishedSemaphores = std::vector<VkSemaphore>();
    std::vector<VkFence> inFlightFences = std::vector<VkFence>(MAX_FRAMES_IN_FLIGHT, VK_NULL_HANDLE);
    uint32_t currentFrame = 0;

    bool framebufferResized = false;


    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanupSwapChain() const;
    void cleanup() const;

    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void selectPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void recreateSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createDepthResources();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void loadModel();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();

    void updateUniformBuffer(uint32_t currentImage) const;
    void drawFrame();

    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static std::vector<const char*> getRequiredInstanceExtensions();
    static bool checkInstanceExtensionSupport(const std::vector<const char*>& requiredExtensions);
    [[nodiscard]] static bool checkDeviceExtensionSupport(VkPhysicalDevice phyDev);
    [[nodiscard]] QueueFamilyIndices findQueueFamilies(VkPhysicalDevice phyDev) const;
    [[nodiscard]] bool isDeviceSuitable(VkPhysicalDevice phyDev) const;
    [[nodiscard]] SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice phyDev) const;
    static VkSurfaceFormatKHR selectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR selectSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    [[nodiscard]] VkExtent2D selectSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) const;
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) const;
    [[nodiscard]] VkShaderModule createShaderModule(const std::vector<char>& code) const;
    [[nodiscard]] uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
        VkBuffer& buffer, VkDeviceMemory& bufferMemory) const;
    VkCommandBuffer beginSingleTimeCommands() const;
    void endSingleTimeCommands(VkCommandBuffer commandBuffer) const;
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
        VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) const;
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) const;
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) const;
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) const;
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling,
        VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    static bool hasStencilComponent(VkFormat format);
};

#endif //FLARE_LIBRARY_H