#ifndef CONDUIT_GLFW_INPUT_MAPPING_HPP
#define CONDUIT_GLFW_INPUT_MAPPING_HPP
#include <cassert>
#include <cstdlib>
#include <glfw/glfw3.h>
#include <conduit/input/keyboard/Key.hpp>
#include <conduit/input/mouse/MouseButton.hpp>
#include <conduit/input/gamepad/GamepadButton.hpp>
#include <conduit/input/gamepad/GamepadAxis.hpp>

namespace conduit::glfw::input {
    using glfwKey = int;
    using glfwMouseButton = int;
    using glfwGamepadButton = int;
    using glfwGamepadAxis = int;

    /**
     * Converts a conduit::Key to a glfw key.
     * 
     * @param key the key to convert
     * 
     * @return the glfw key value
     */
    glfwKey toGLFWKeyButton(conduit::Key key);

    /**
     * Converts a conduit::MouseButton to a glfw mouse button.
     * 
     * @param mouseButton the mouse button to convert
     * 
     * @return the glfw mouse button value
     */
    glfwMouseButton toGLFWMouseButton(conduit::MouseButton mouseButton);

    /**
     * Converts a conduit::GamepadButton to a glfw gamepad button.
     * 
     * @param gamepadButton the gamepad button to convert
     * 
     * @return the glfw gamepad button value
     */
    glfwGamepadButton toGLFWGamepadButton(conduit::GamepadButton gamepadButton);

    /**
     * Converts a conduit::GamedpadAxis to a glfw gamepad axis.
     * 
     * @param gamepadAxis
     * 
     * @return the glfw GamepadAxis value
     */
    glfwGamepadAxis toGLFWGamepadAxis(conduit::GamepadAxis gamepadAxis);
} // namespace conduit::glfw::input

#endif // CONDUIT_GLFW_INPUT_MAPPING_HPP
