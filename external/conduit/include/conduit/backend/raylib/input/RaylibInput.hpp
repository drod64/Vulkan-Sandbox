#ifndef CONDUIT_RAYLIB_INPUT_HPP
#define CONDUIT_RAYLIB_INPUT_HPP
#include <conduit/input/Input.hpp>
#include <conduit/backend/raylib/input/RaylibInputMapping.hpp>
#include <conduit/backend/raylib/input/RaylibGamepadInput.hpp>

namespace conduit::raylib {
class RaylibInput {
private:
    RaylibGamepadInput m_gamepad_input;

    /**
     * Helper function that focuses on polling the keyboard.
     * 
     * @param keyboardState the keyboard state to poll and store the results in
     */
    void pollKeyboard(KeyboardState &keyboardState);

    /**
     * Helper function that focuses on polling the mouse.
     * 
     * @param mouseState the mouse state to poll and store the results in
     */
    void pollMouse(MouseState &mouseState);

    /**
     * Helper function that focuses on polling gamepads.
     * 
     * @param gamepadStates the gamepad states to poll and store the results in
     */
    void pollGamepads(GamepadStates &gamepadStates);

public:
    RaylibInput() = default;
    ~RaylibInput() = default;

    /**
     * Polls input sources (keyboard, mouse, gamepads) using raylib specific functions.
     * 
     * @param input an Input class where the polled results will be stored
     */
    void poll(Input &input);
}; // class RaylibInput
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_INPUT_HPP