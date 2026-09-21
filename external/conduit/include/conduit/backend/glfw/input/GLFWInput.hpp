#ifndef CONDUIT_GLFW_INPUT_HPP
#define CONDUIT_GLFW_INPUT_HPP
#include <glfw/glfw3.h>

// Forwards
namespace conduit{
    class Input;

    namespace glfw::window {
        class GLFWWindow;
    }
}

namespace conduit::glfw::input {
    /**
     * Polls the input state using glfw specific functions.
     * 
     * @param platformWindow the underlying platform window Conduit is using (which should equate to conduit::glfw::window::GLFWWindow)
     * @param input the input tracker to store the results in
     */
    void poll(const conduit::glfw::window::GLFWWindow &platformWindow, conduit::Input &input);

    namespace detail {
        /**
         * GLFW specific function.
         * Registers any callbacks necessary for input polling.
         */
        void registerGLFWCallbacks(GLFWwindow *glfwWindow);
    }
} // namespace conduit::glfw::input

#endif // CONDUIT_GLFW_INPUT_HPP