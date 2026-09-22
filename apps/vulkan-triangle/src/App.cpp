#include <iostream>
#include <vulkan-triangle/App.hpp>
#include <conduit/Input/Input.hpp>
#include <conduit/window/Window.hpp>

void vtapp::App::initialize()
{
    conduit::platform::initialize();
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