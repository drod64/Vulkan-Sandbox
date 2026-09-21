#include <iostream>
#include <conduit/tests/vulkan/VulkanTester.hpp>
#include <conduit/Input/Input.hpp>
#include <conduit/window/Window.hpp>

void conduit::VulkanTester::initialize()
{
    conduit::platform::initialize();
}

void conduit::VulkanTester::shutdown()
{
    conduit::platform::shutdown();
}

conduit::VulkanTester::VulkanTester()
{
    initialize();
}

conduit::VulkanTester::~VulkanTester()
{
    shutdown();
}

void conduit::VulkanTester::run()
{
    conduit::Window window(VulkanTester::WIDTH, VulkanTester::HEIGHT, "Conduit Vulkan Tester");
    conduit::Input input(window);

    while (!window.shouldClose())
    {
        window.pollEvents();
        input.poll();

        if (input.keyboard().wasPressed(conduit::Key::ESCAPE))
        {
            window.close();
        }
    }
}