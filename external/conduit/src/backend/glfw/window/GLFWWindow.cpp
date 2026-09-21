#include <conduit/backend/glfw/window/GLFWWindow.hpp>
#include <conduit/backend/glfw/input/GLFWInput.hpp>

conduit::glfw::window::GLFWWindow::GLFWWindow(uint32 width, uint32 height, const char *title)
{
    m_glfw_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    assert(m_glfw_window && "[conduit::glfw::GLFWWindow] - Failed to create glfw window.");

    conduit::glfw::input::detail::registerGLFWCallbacks(m_glfw_window);
}

conduit::glfw::window::GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(m_glfw_window);
}

bool conduit::glfw::window::GLFWWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_glfw_window);
}

void conduit::glfw::window::GLFWWindow::close()
{
    glfwSetWindowShouldClose(m_glfw_window, GLFW_TRUE);
}

void conduit::glfw::window::GLFWWindow::pollEvents()
{
    glfwPollEvents();
}

void conduit::glfw::window::GLFWWindow::swapBuffers()
{
    glfwSwapBuffers(m_glfw_window);
}

conduit::uint32 conduit::glfw::window::GLFWWindow::width() const
{
    int width, height;
    glfwGetWindowSize(m_glfw_window, &width, &height);

    return static_cast<uint32>(width);
}

conduit::uint32 conduit::glfw::window::GLFWWindow::height() const
{
    int width, height;
    glfwGetWindowSize(m_glfw_window, &width, &height);

    return static_cast<uint32>(height);
}

void conduit::glfw::window::GLFWWindow::setTitle(const char *title)
{
    glfwSetWindowTitle(m_glfw_window, title);
}

bool conduit::glfw::window::GLFWWindow::isFocused() const
{
    return glfwGetWindowAttrib(m_glfw_window, GLFW_FOCUSED) == true;
}

bool conduit::glfw::window::GLFWWindow::isMinimized() const
{
    return glfwGetWindowAttrib(m_glfw_window, GLFW_ICONIFIED) == true;
}

GLFWwindow* conduit::glfw::window::GLFWWindow::nativeHandle() const
{
    return m_glfw_window;
}