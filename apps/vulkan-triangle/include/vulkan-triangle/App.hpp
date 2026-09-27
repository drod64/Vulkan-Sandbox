#ifndef VT_APP_APP_HPP
#define VT_APP_APP_HPP
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <exception>
#include <vulkan/vulkan_raii.hpp>
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/window/Window.hpp>

namespace vtapp {
const conduit::vector<char const *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
const conduit::vector<const char*> requiredDeviceExtension = {vk::KHRSwapchainExtensionName};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

class App {
private:
    conduit::Window                     m_window;

    vk::raii::Context                   m_context;
    vk::raii::Instance                  m_instance = nullptr;
    vk::raii::DebugUtilsMessengerEXT    m_debugMessenger = nullptr;

    vk::raii::PhysicalDevice            m_physical_device = nullptr;
    vk::raii::Device                    m_logical_device = nullptr;
    vk::raii::Queue                     m_graphics_queue = nullptr;

    vk::raii::SurfaceKHR                m_surface = nullptr;

    vk::raii::SwapchainKHR                      m_swap_chain = nullptr;
    vk::SurfaceFormatKHR                        m_swap_chain_surface_format;
    vk::Extent2D                                m_swap_chain_extent;
    conduit::vector<vk::Image>                  m_swap_chain_images;
    conduit::vector<vk::raii::ImageView>        m_swap_chain_image_views;

    /**
     * Vulkan callback for debug purposes.
     * 
     * @param severity  ranges from -> eVerbose, eInfo, eWarning, eError (from least to greatest severity)
     * @param type      ranges from eGeneral, eValidation, ePerformance
     * @param pCallbackData
     * @param pUserData
     */
    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT        severity,
        vk::DebugUtilsMessageTypeFlagsEXT               type,
        const vk::DebugUtilsMessengerCallbackDataEXT   *pCallbackData,
        void                                           *pUserData
    );

    /**
     * Retrives the required instance layers.
     * This was introduced as way to have validation layers (error checking).
     * 
     * @return a container with the names of required layers
     */
    conduit::vector<char const*> getRequiredInstanceLayers();
    
    /**
     * Retrieves the required instance extensions.
     * Necessary for all vk::raii::Instance objects
     * 
     * @return a container with the names of required extensions
     */
    conduit::vector<const char*> getRequiredInstanceExtensions();
    
    /**
     * Creates the window of the application.
     */
    void createWindow();

    /**
     * Creates the vulkan instance.
     */
    void createVkInstance();

    /**
    * Sets up the debug messenger.
    */
    void setupDebugMessenger();

    /**
     * Creates a surface for Vulkan.
     */
    void createSurface();

    /**
     *  Helper function that checks if a physical device is suitable for Vulkan use.
     * 
     *  @return true if the physical device is suitable, false otherwise
     */
    bool isDeviceSuitable(vk::raii::PhysicalDevice const & physicalDevice);

    /**
     * Picks a physical device for Vulkan to use.
     */
    void pickPhysicalDevice();

    /**
     * Creates a logical device to interact with the physical device.
     */
    void createLogicalDevice();

    /**
     * Chooses a surface format for the swap chain.
     * 
     * @param availableFormats a container of the available formats to choose from
     */
    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const conduit::vector<vk::SurfaceFormatKHR> &availableFormats);

    /**
     * Chooses a present mode for the swap chain.
     * 
     * @param availablePresentModes a container of the available present modes to choose from
     */
    vk::PresentModeKHR chooseSwapPresentMode(const conduit::vector<vk::PresentModeKHR> &availablePresentModes);

    /**
     * Chooses a swap extent for the swap chain.
     * 
     * @param surfaceCapabilities the available capabilities provided by the surface obj
     */
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities);

    /**
     * Retrieves the amount of minimum images for the swap chain.
     * 
     * @param surfaceCapabilities the available capabilities provided by the surface obj 
     */
    uint32_t chooseSwapMinImageCount(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities);

    /**
     * Creates a swap chain.
     */
    void createSwapChain();

    /**
     * Creates the rendering pipeline's image views.
     */
    void createImageViews();

    /**
     * Initializes the Vulkan library for the application.
     */
    void initVulkan();
    
    /**
     * Starts up the application.
     */
    void initialize();

    /**
     * Shuts down the application and cleans up any resources used during its lifetime.
     */
    void shutdown();

public:
    static constexpr conduit::uint32 WIDTH = 800;
    static constexpr conduit::uint32 HEIGHT = 600;

    /**
     * Default constructor.
     */
    App();

    /**
     * Destructor.
     */
    ~App();

    /**
     * Runs the Vulkan-Triangle app.
     */
    void run();
}; // class App
} // namespace vtapp

#endif // VT_APP_APP_HPP