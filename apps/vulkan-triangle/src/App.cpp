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

conduit::vector<char const*> vtapp::App::getRequiredInstanceLayers()
{
    conduit::vector<char const*> requiredLayers;

    if (vtapp::enableValidationLayers)
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

void vtapp::App::setupDebugMessenger()
{
    if (!vtapp::enableValidationLayers) return;

    // State which severity flags we would like the callback to be activated on.
    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
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

bool vtapp::App::isDeviceSuitable(vk::raii::PhysicalDevice const & physicalDevice)
{
    // Check if the device supports Vulkan 1.3 API version.
    bool supportsVulkan1_3 = physicalDevice.getProperties().apiVersion >= vk::ApiVersion13;

    // Check if any of the queue families support graphics operations.
    auto queueFamilies = physicalDevice.getQueueFamilyProperties();
    bool supportsGraphics = std::ranges::any_of(queueFamilies, [] (auto const &qfp) {
        return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics);
    });

    // Check if all required physicalDevice extensions are available.
    auto availableDeviceExtensions = physicalDevice.enumerateDeviceExtensionProperties();
    bool supportsAllRequiredExtensions = std::ranges::all_of(vtapp::requiredDeviceExtension, [&availableDeviceExtensions] (auto const &requiredDeviceExtension) {
        return std::ranges::any_of(availableDeviceExtensions, [requiredDeviceExtension] (const auto &availableDeviceExtension) {
            return strcmp(availableDeviceExtension.extensionName, requiredDeviceExtension) == 0;
        });
    });

    // Check if the physicalDevice supports the required features.
    auto features = physicalDevice.template getFeatures2<vk::PhysicalDeviceFeatures2,
                                                        vk::PhysicalDeviceVulkan11Features,
                                                        vk::PhysicalDeviceVulkan13Features,
                                                        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>();

    bool supportsRequiredFeatures = features.template get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters    &&
                                    features.template get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering        &&
                                    features.template get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState;

    return supportsVulkan1_3 && supportsGraphics && supportsAllRequiredExtensions && supportsRequiredFeatures;
}

void vtapp::App::pickPhysicalDevice()
{
    // vk::raii::PhysicalDevice

    auto physicalDevices = m_instance.enumeratePhysicalDevices();

    auto const devIter = std::ranges::find_if(physicalDevices, [&] (auto const &physicalDevice) {
        return isDeviceSuitable(physicalDevice);
    });

    // Throw an error if no GPUs support Vulkan.
    if (devIter == physicalDevices.end())
    {
        throw std::runtime_error("failed to find a suitable GPU.");
    }

    m_physical_device = *devIter;
}

void vtapp::App::createLogicalDevice()
{
    // vk::DeviceQueueCreateInfo
    // vk::DeviceCreateInfo

    // vk::raii::Device
    // vk::raii::Queue

    // Get queue family properties from physical device.
    conduit::vector<vk::QueueFamilyProperties> queueFamilyProperties = m_physical_device.getQueueFamilyProperties();

    // Query the queue family with the desired capability (graphics).
    auto graphicsQueueFamilyProperty = std::ranges::find_if(queueFamilyProperties, [] (auto const &qfp) {
        return (qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0);
    });
    auto graphicsIndex = static_cast<uint32_t>(std::distance(queueFamilyProperties.begin(), graphicsQueueFamilyProperty));

    // Create queue info.
    float queuePriority = 0.5f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo = {
        .queueFamilyIndex = graphicsIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    // Create feature chain.
    vk::StructureChain <
        vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT
    >
    featureChain = {
        {},                                 // Nothing required from vk::PhysicalDeviceFeatures2
        {.shaderDrawParameters  = true},    // enable shader draw parameters from Vulkan 1.1
        {.dynamicRendering      = true},    // enable shader draw parameters from Vulkan 1.3
        {.extendedDynamicState  = true}     // enable extended dynamic state from the extension
    };

    // Create logical device info.
    vk::DeviceCreateInfo deviceCreateInfo {
        .pNext                      = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount       = 1,
        .pQueueCreateInfos          = &deviceQueueCreateInfo,
        .enabledExtensionCount      = static_cast<uint32_t>(vtapp::requiredDeviceExtension.size()),
        .ppEnabledExtensionNames    = vtapp::requiredDeviceExtension.data()
    };

    // Create the logical device.
    m_logical_device = vk::raii::Device(m_physical_device, deviceCreateInfo);

    // Create queue handle.
    m_graphics_queue = vk::raii::Queue(m_logical_device, graphicsIndex, 0);

}

void vtapp::App::initVulkan()
{
    createVkInstance();
    setupDebugMessenger();
    pickPhysicalDevice();
    createLogicalDevice();
}

void vtapp::App::initialize()
{
    conduit::platform::initialize();

    initVulkan();
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