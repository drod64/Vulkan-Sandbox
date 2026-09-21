#include <conduit/backend/glfw/input/GLFWInput.hpp>
#include <conduit/backend/glfw/input/GLFWInputMapping.hpp>
#include <conduit/backend/glfw/window/GLFWWindow.hpp>
#include <conduit/input/Input.hpp>
#include <conduit/input/gamepad/GamepadStates.hpp>
#include <conduit/input/keyboard/KeyboardState.hpp>
#include <conduit/input/mouse/MouseState.hpp>

namespace {
    double scroll_x = 0;
    double scroll_y = 0;

    /**
     * GLFW dependent callback for mouse scroll/wheel accumulation.
     * 
     * @param window a pointer to the GLFWWindow
     * @param xOffset the x offset
     * @param yOffset the y offset
     */
    void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
    {
        scroll_x += xOffset;
        scroll_y += yOffset;
    }

    /**
     * Focuses on polling the keyboard.
     * 
     * @param glfwWindow the native GLFWwindow type
     * @param keyboardState the keyboard state to store the results in
     */
    void pollKeyboard(GLFWwindow *glfwWindow, conduit::KeyboardState &keyboardState)
    {
        // Update previous button state of keyboard
        keyboardState.updatePrevious();

        // Update current button state of keyboard
        for (conduit::sizet key = 0; key < static_cast<conduit::sizet>(conduit::Key::MAX_COUNT); ++key)
        {
            conduit::Key conduit_key = static_cast<conduit::Key>(key);
            conduit::glfw::input::glfwKey glfw_key = conduit::glfw::input::toGLFWKeyButton(conduit_key);

            keyboardState.setKey(conduit_key, glfwGetKey(glfwWindow, glfw_key) == GLFW_PRESS);
        }
    }

    /**
     * Focuses on polling the mouse.
     * 
     * @param glfwWindow the native GLFWwindow type
     * @param mouseState the mouse state to store the results in
     */
    void pollMouse(GLFWwindow *glfwWindow, conduit::MouseState &mouseState)
    {
        // Update previous button state of mouse
        mouseState.updatePrevious();

        // Update current button state of mouse
        for (conduit::sizet button = 0; button < static_cast<conduit::sizet>(conduit::MouseButton::MAX_COUNT); ++button)
        {
            conduit::MouseButton conduit_button = static_cast<conduit::MouseButton>(button);
            conduit::glfw::input::glfwMouseButton glfw_button = conduit::glfw::input::toGLFWMouseButton(conduit_button);

            mouseState.setButton(conduit_button, glfwGetMouseButton(glfwWindow, glfw_button) == GLFW_PRESS);
        }

        // Update mouse axes
        double xPos, yPos;
        glfwGetCursorPos(glfwWindow, &xPos, &yPos);

        sm::Vec2 current_pos(static_cast<conduit::real>(xPos), static_cast<conduit::real>(yPos));

        // Translate to sm::Vec2
        mouseState.updateDelta(current_pos - mouseState.position());
        mouseState.updatePosition(current_pos);
        mouseState.updateWheel(sm::Vec2(static_cast<conduit::real>(scroll_x), static_cast<conduit::real>(scroll_y)));
        
        scroll_x = 0;
        scroll_y = 0;
    }

    /**
     * Helper function that focuses on polling a gamepad's connection.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollConnection(int gamepad, conduit::GamepadState &state)
    {
        const int jid = GLFW_JOYSTICK_1 + gamepad;

        const bool connected =
        glfwJoystickPresent(jid) == GLFW_TRUE &&
        glfwJoystickIsGamepad(jid) == GLFW_TRUE;

        // Disconnected controller
        if (!connected)
        {
            state.reset();
            state.setConnection(false);
            return;
        }

        // Newly connected controller
        if (!state.isConnected())
        {
            state.reset();
        }

        state.setConnection(true);
    }

    /**
     * Helper function that focuses on polling a gamepad's axes and buttons.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollAxesAndButtons(int gamepad, conduit::GamepadState &state)
    {
        const int jid = GLFW_JOYSTICK_1 + gamepad;

        GLFWgamepadstate glfw_state{};

        // Gamepad isn't available or disconnected here.
        if (glfwGetGamepadState(jid, &glfw_state) == GLFW_FALSE)
        {
            state.reset();
            state.setConnection(false);
            return;
        }

        // Poll axes.
        for (conduit::sizet axis = 0; axis < static_cast<conduit::sizet>(conduit::GamepadAxis::MAX_COUNT); ++axis)
        {   
            conduit::GamepadAxis conduit_axis = static_cast<conduit::GamepadAxis>(axis);
            conduit::glfw::input::glfwGamepadAxis glfw_axis = conduit::glfw::input::toGLFWGamepadAxis(conduit_axis);

            state.setAxis(conduit_axis, glfw_state.axes[glfw_axis]);
        }

        // Poll buttons.
        for (conduit::sizet button = 0; button < static_cast<conduit::sizet>(conduit::GamepadButton::MAX_COUNT); ++button)
        {
            conduit::GamepadButton conduit_button = static_cast<conduit::GamepadButton>(button);
            conduit::glfw::input::glfwGamepadButton glfw_button = conduit::glfw::input::toGLFWGamepadButton(conduit_button);

            state.setButton(conduit_button, glfw_state.buttons[glfw_button] == GLFW_PRESS);
        }
    }

    /**
     * Focuses on polling the gamepads.
     * 
     * @param glfwWindow the native GLFWwindow type
     * @param gamepadStates the gamepad states to store the results in
     */
    void pollGamepads(conduit::GamepadStates &gamepadStates)
    {
        for (conduit::sizet gamepad = 0; gamepad < gamepadStates.size(); ++gamepad)
        {
            conduit::GamepadState &gamepad_state = gamepadStates[gamepad];
        
            pollConnection(static_cast<int>(gamepad), gamepad_state);
            if (!gamepad_state.isConnected()) continue;

            pollAxesAndButtons(static_cast<int>(gamepad), gamepad_state);
        }
    }
}

void conduit::glfw::input::poll(const conduit::glfw::window::GLFWWindow &platformWindow, conduit::Input &input)
{
    pollGamepads(input.gamepads());
    pollKeyboard(platformWindow.nativeHandle(), input.keyboard());
    pollMouse(platformWindow.nativeHandle(), input.mouse());
}

void conduit::glfw::input::detail::registerGLFWCallbacks(GLFWwindow *glfwWindow)
{
    glfwSetScrollCallback(glfwWindow, scrollCallback);
}