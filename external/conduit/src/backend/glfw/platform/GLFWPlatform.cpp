#include <conduit/backend/glfw/platform/GLFWPlatform.hpp>

void conduit::glfw::initialize()
{
    assert(glfwInit() && "[conduit::glfw::GLFWPlatform] - Failed to initialize glfw.");
}

void conduit::glfw::shutdown()
{
    glfwTerminate();
}