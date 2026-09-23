#include <iostream>
#include <vulkan-triangle/App.hpp>
#include <conduit/Input/Input.hpp>
#include <conduit/window/Window.hpp>

void vtapp::App::initialize()
{
    conduit::platform::initialize();

    createVkInstance();
}

void vtapp::App::createVkInstance()
{
    // 1. Create app info.
    constexpr vk::ApplicationInfo appInfo{
        .pApplicationName   = "Vulkan Triangle",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = vk::ApiVersion14
    };

    // 2. Get extension count (and check if extensions are supported).
    uint32_t glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    auto extensionProperties = m_context.enumerateInstanceExtensionProperties();

    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (std::ranges::none_of(extensionProperties, [glfwExtension = glfwExtensions[i]](auto const &extensionProperty)
                                                        {return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
        {
            throw std::runtime_error("Required GLFW extensions not supported: " + std::string(glfwExtensions[i]));
        }
    }

    // 3. Create info struct
    vk::InstanceCreateInfo createInfo {
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions
    };

    // 4. Create instance object.
    m_instance = vk::raii::Instance(m_context, createInfo);
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