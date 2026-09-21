#include <conduit/window/Window.hpp>

conduit::Window::Window(uint32 width, uint32 height, const char *title) :
m_platform_window(width, height, title)
{}

bool conduit::Window::shouldClose() const
{
    return m_platform_window.shouldClose();
}

void conduit::Window::close()
{
    return m_platform_window.close();
}

void conduit::Window::pollEvents()
{
    m_platform_window.pollEvents();
}

void conduit::Window::swapBuffers()
{
    m_platform_window.swapBuffers();
}

conduit::uint32 conduit::Window::width() const
{
    return m_platform_window.width();
}

conduit::uint32 conduit::Window::height() const
{
    return m_platform_window.height();
}

void conduit::Window::setTitle(const char *title)
{
    m_platform_window.setTitle(title);
}

bool conduit::Window::isFocused() const
{
    return m_platform_window.isFocused();
}

bool conduit::Window::isMinimized() const
{
    return m_platform_window.isMinimized();
}