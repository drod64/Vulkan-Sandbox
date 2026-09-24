#include <iostream>
#include <vulkan-triangle/App.hpp>
#include <conduit/Input/Input.hpp>
#include <conduit/window/Window.hpp>

VKAPI_ATTR vk::Bool32 VKAPI_CALL vtapp::App::debugCallback(
        vk::DebugUtilsMessageSeverityFlagBitsEXT        severity,
        vk::DebugUtilsMessageTypeFlagsEXT               type,
        const vk::DebugUtilsMessengerCallbackDataEXT   *pCallbackData,
        void                                           *pUserData
    )
{
    std::cerr << "validation layer: type " << to_string(type) << " msg: " << pCallbackData->pMessage << '\n';
    return vk::False;
}

void vtapp::App::setupDebugMessenger()
{
    if (!vtapp::enableValidationLayers) return;

    // State which severity flags we would like the callback to be activated on.
    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose  |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo     |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning  |
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
        
    // State which type flags we would like the callback to be activated on.
    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral      | 
        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance  |
        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

    vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT {
        .messageSeverity    = severityFlags,
        .messageType        = messageTypeFlags,
        .pfnUserCallback    =&debugCallback
    };

    m_debugMessenger = m_instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
}

conduit::vector<char const*> vtapp::App::getRequiredInstanceLayers()
{
    conduit::vector<char const*> requiredLayers;

    if (enableValidationLayers)
    {
        requiredLayers.assign(vtapp::validationLayers.begin(),vtapp::validationLayers.end());
    }

    auto layerProperties = m_context.enumerateInstanceLayerProperties();
    auto unsupportedLayerIt = std::ranges::find_if(requiredLayers, [&layerProperties](auto const &requiredLayer){
        return std::ranges::none_of(layerProperties, [requiredLayer](auto const &layerProperty){
            return strcmp(layerProperty.layerName, requiredLayer) == 0;
        });
    });

    if (unsupportedLayerIt != requiredLayers.end())
    {
        throw std::runtime_error("Required layer not supported: " + std::string(*unsupportedLayerIt));
    }

    return requiredLayers;
}

conduit::vector<const char*> vtapp::App::getRequiredInstanceExtensions()
{
    uint32_t glfwExtensionCount = 0;

    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    conduit::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (vtapp::enableValidationLayers)
    {
        extensions.push_back(vk::EXTDebugUtilsExtensionName);
    }

    return extensions;
}

void vtapp::App::createVkInstance()
{
    // vk::ApplicationInfo
    // vk::InstanceCreateInfo
    // vk::raii::Instance

    // 1. Create app info.
    constexpr vk::ApplicationInfo appInfo{
        .pApplicationName   = "Vulkan Triangle",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = vk::ApiVersion14
    };

    // 2. Get extensions and layers.
    auto requiredLayers = getRequiredInstanceLayers();
    auto requiredExtensions = getRequiredInstanceExtensions();
    
    // Check if extensions are supported.
    auto extensionProperties = m_context.enumerateInstanceExtensionProperties();
    auto unsupportedPropertyIt = std::ranges::find_if(requiredExtensions, [&extensionProperties] (auto const &requiredExtension) {
        return std::ranges::none_of(extensionProperties, [requiredExtension] (auto const &extensionProperty) {
            return strcmp(extensionProperty.extensionName, requiredExtension) == 0;
        });
    });
    if (unsupportedPropertyIt != requiredExtensions.end())
    {
        throw std::runtime_error("Required extension not supported: " + std::string(*unsupportedPropertyIt));
    }

    // 3. Create info struct
    vk::InstanceCreateInfo createInfo {
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(requiredLayers.size()),
        .ppEnabledLayerNames = requiredLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data()
    };

    // 4. Create instance object.
    m_instance = vk::raii::Instance(m_context, createInfo);
}

void vtapp::App::initialize()
{
    conduit::platform::initialize();

    createVkInstance();
    setupDebugMessenger();
}


void vtapp::App::shutdown()
{
    conduit::platform::shutdown();
}

vtapp::App::App()
{
    initialize();
}

vtapp::App::~App()
{
    shutdown();
}

void vtapp::App::run()
{
    conduit::Window window(App::WIDTH, App::HEIGHT, "Vulkan Triangle");
    conduit::Input input(window);

    while (!window.shouldClose())
    {
        window.pollEvents();
        input.poll();

        if (input.keyboard().wasReleased(conduit::Key::ESCAPE))
        {
            window.close();
        }
    }
}