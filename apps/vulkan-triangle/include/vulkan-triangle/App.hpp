#ifndef VT_APP_APP_HPP
#define VT_APP_APP_HPP
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <exception>
#include <vulkan/vulkan_raii.hpp>
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/vector.hpp>

namespace vtapp {
const conduit::vector<char const *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

class App {
private:
    vk::raii::Context                   m_context;
    vk::raii::Instance                  m_instance = nullptr;
    vk::raii::DebugUtilsMessengerEXT    m_debugMessenger = nullptr;

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
     * Sets up the debug messenger.
     */
    void setupDebugMessenger();

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
     * Creates the vulkan instance.
     */
    void createVkInstance();
    
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