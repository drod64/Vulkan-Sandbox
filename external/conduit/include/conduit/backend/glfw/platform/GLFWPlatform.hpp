#ifndef CONDUIT_GLFW_PLATFORM_HPP
#define CONDUIT_GLFW_PLATFORM_HPP
#include <cassert>
#include <glfw/glfw3.h>
#include <conduit/backend/glfw/window/GLFWWindow.hpp>
#include <conduit/backend/glfw/input/GLFWInput.hpp>

namespace conduit::glfw {
    using Window = window::GLFWWindow;

    /**
     * Initializes the glfw library.
     */
    void initialize();

    /**
     * Shutdowns the glfw library.
     */
    void shutdown();
} // namespace conduit::glfw

#endif // CONDUIT_GLFW_PLATFORM_HPP