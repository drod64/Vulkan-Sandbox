#include <conduit/backend/glfw/platform/GLFWPlatform.hpp>

void conduit::glfw::initialize()
{
    assert(glfwInit() && "[conduit::glfw::GLFWPlatform] - Failed to initialize glfw.");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void conduit::glfw::shutdown()
{
    glfwTerminate();
}