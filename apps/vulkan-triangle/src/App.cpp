#include <iostream>
#include <vulkan-triangle/App.hpp>
#include <vulkan-triangle/util.hpp>
#include <conduit/Input/Input.hpp>

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

void vtapp::App::createWindow()
{
    m_window = conduit::Window(App::WIDTH, App::HEIGHT, "Vulkan Triangle");
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

void vtapp::App::createSurface()
{
    // vk::raii::SurfaceKHR

    // Attempt to make window surface through glfw API.
    VkSurfaceKHR surface;
    if (glfwCreateWindowSurface(*m_instance, m_window.platformWindow().nativeHandle(), nullptr, &surface) != 0)
    {
        throw std::runtime_error("failed to create window surface.");
    }

    // Create window surface.
    m_surface = vk::raii::SurfaceKHR(m_instance, surface);
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

    // Query the queue family with the desired capability (graphics and presentation on created surface).
    uint32_t queueIndex = ~0;
    for (uint32_t qfpIndex = 0; qfpIndex < queueFamilyProperties.size(); ++qfpIndex)
    {
        if (queueFamilyProperties[qfpIndex].queueFlags & vk::QueueFlagBits::eGraphics &&
            m_physical_device.getSurfaceSupportKHR(qfpIndex, *m_surface))
        {
            queueIndex = qfpIndex;
            break;
        }
    }

    // Throw error if no queue is found.
    if (queueIndex == ~0)
    {
        throw std::runtime_error("no suitable queue found that supports graphics and presentation");
    }
    
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

    // Create queue info.
    float queuePriority = 0.5f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo = {
        .queueFamilyIndex = queueIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
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
    m_graphics_queue = vk::raii::Queue(m_logical_device, queueIndex, 0);

}

vk::SurfaceFormatKHR vtapp::App::chooseSwapSurfaceFormat(const conduit::vector<vk::SurfaceFormatKHR> &availableFormats)
{
    const auto formatIt = std::ranges::find_if(availableFormats, [] (const auto &format) -> bool {
        return format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
    });

    return (formatIt != availableFormats.end()) ? *formatIt : availableFormats[0];
}

vk::PresentModeKHR vtapp::App::chooseSwapPresentMode(const conduit::vector<vk::PresentModeKHR> &availablePresentMode)
{
    // Specify desired mode for app.
    const vk::PresentModeKHR DESIRED_MODE = vk::PresentModeKHR::eMailbox;

    // Ensure a default eFifo mode is available.
    assert(std::ranges::any_of(availablePresentMode, [] (const auto &presentMode) {
        return presentMode == vk::PresentModeKHR::eFifo;
    }));

    // Check if desired mode is available.
    bool modeFound = std::ranges::any_of(availablePresentMode, [] (const vk::PresentModeKHR &value) -> bool {
        return value == DESIRED_MODE;
    });
    
    // Return mode (dependent on result).
    return (modeFound) ? DESIRED_MODE : vk::PresentModeKHR::eFifo;
}

vk::Extent2D vtapp::App::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities)
{
    if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return surfaceCapabilities.currentExtent;
    }

    int width, height;
    glfwGetFramebufferSize(m_window.platformWindow().nativeHandle(), &width, &height);

    return {
        std::clamp<uint32_t>(width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width),
        std::clamp<uint32_t>(height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height)
    };
}

uint32_t vtapp::App::chooseSwapMinImageCount(const vk::SurfaceCapabilitiesKHR &surfaceCapabilities)
{
    auto minImageCount = std::max(3u, surfaceCapabilities.minImageCount);

    if ((surfaceCapabilities.maxImageCount > 0) && (surfaceCapabilities.maxImageCount < minImageCount))
    {
        minImageCount = surfaceCapabilities.maxImageCount;
    }

    return minImageCount;
}

void vtapp::App::createSwapChain()
{
    // Get containers to query.
    vk::SurfaceCapabilitiesKHR              surfaceCapabilities     = m_physical_device.getSurfaceCapabilitiesKHR(*m_surface);
    conduit::vector<vk::SurfaceFormatKHR>   availableFormats        = m_physical_device.getSurfaceFormatsKHR(*m_surface);
    conduit::vector<vk::PresentModeKHR>     availablePresentModes   = m_physical_device.getSurfacePresentModesKHR(*m_surface);

    // Get required settings for swap chain.
    m_swap_chain_extent             = chooseSwapExtent(surfaceCapabilities);
    uint32_t minImageCount          = chooseSwapMinImageCount(surfaceCapabilities);
    m_swap_chain_surface_format     = chooseSwapSurfaceFormat(availableFormats);

    // Create swap chain create info.
    vk::SwapchainCreateInfoKHR swapChainCreateInfo {
        .surface            = *m_surface,
        .minImageCount      = minImageCount,
        .imageFormat        = m_swap_chain_surface_format.format,
        .imageColorSpace    = m_swap_chain_surface_format.colorSpace,
        .imageExtent        = m_swap_chain_extent,
        .imageArrayLayers   = 1,
        .imageUsage         = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode   = vk::SharingMode::eExclusive,
        .preTransform       = surfaceCapabilities.currentTransform,
        .compositeAlpha     = vk::CompositeAlphaFlagBitsKHR::eOpaque,
        .presentMode        = chooseSwapPresentMode(availablePresentModes),
        .clipped            = true,
        .oldSwapchain       = nullptr
    };

    // Create the swap chain (and get the images).
    m_swap_chain = vk::raii::SwapchainKHR(m_logical_device, swapChainCreateInfo);
    m_swap_chain_images = m_swap_chain.getImages();
}

void vtapp::App::createImageViews()
{
    assert(m_swap_chain_image_views.empty());

    vk::ImageViewCreateInfo imageViewCreateInfo {
        .viewType           = vk::ImageViewType::e2D,
        .format             = m_swap_chain_surface_format.format,
        .subresourceRange   = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 } 
    };

    for (auto &image : m_swap_chain_images)
    {
        imageViewCreateInfo.image = image;
        m_swap_chain_image_views.emplace_back(m_logical_device, imageViewCreateInfo);
    }
}

vk::raii::ShaderModule vtapp::App::createShaderModule(const conduit::vector<char> &code) const
{
    vk::ShaderModuleCreateInfo createInfo {
        .codeSize   = code.size() * sizeof(char),
        .pCode      = reinterpret_cast<const uint32_t*>(code.data())
    };
    vk::raii::ShaderModule shaderModule(m_logical_device, createInfo);

    return shaderModule;
}

void vtapp::App::createGraphicsPipeline()
{
    vk::raii::ShaderModule shaderModule = createShaderModule(vtapp::readFile("apps//vulkan-triangle//shaders//slang.spv"));

    vk::PipelineShaderStageCreateInfo vertShaderStageInfo {
        .stage  = vk::ShaderStageFlagBits::eVertex,
        .module = shaderModule,
        .pName  = "vertMain"
    };

    vk::PipelineShaderStageCreateInfo fragShaderStageInfo {
        .stage  = vk::ShaderStageFlagBits::eFragment,
        .module = shaderModule,
        .pName  = "fragMain"
    };

    vk::PipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};
}

void vtapp::App::initVulkan()
{
    createVkInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createGraphicsPipeline();
}

void vtapp::App::initialize()
{
    conduit::platform::initialize();
    
    createWindow();

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
    conduit::Input input(m_window);

    while (!m_window.shouldClose())
    {
        m_window.pollEvents();
        input.poll();

        if (input.keyboard().wasReleased(conduit::Key::ESCAPE))
        {
            m_window.close();
        }
    }
}