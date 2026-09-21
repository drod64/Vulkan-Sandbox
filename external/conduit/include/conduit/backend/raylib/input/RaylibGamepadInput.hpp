#ifndef CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP
#define CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP
#include <raylib.h>
#include <conduit/core/primitives.hpp>
#include <conduit/backend/raylib/input/RaylibInputMapping.hpp>
#include <conduit/input/gamepad/GamepadButton.hpp>
#include <conduit/input/gamepad/GamepadStates.hpp>

namespace conduit::raylib {
class RaylibGamepadInput {
private:
    /**
     * Helper function that focuses on polling a gamepad's connection.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollConnection(int gamepad, GamepadState &state);

    /**
     * Helper function that focuses on polling a gamepad's axes.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollAxes(int gamepad, GamepadState &state);

    /**
     * Helper function that focuses on polling a gamepad's buttons.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollButtons(int gamepad, GamepadState &state);

public:
    RaylibGamepadInput() = default;
    ~RaylibGamepadInput() = default;

    /**
     * Polls gamepads using raylib specific functions.
     * 
     * @param gamepadStates a collection of gamepad states to poll and store the results in
     */
    void poll(GamepadStates &gamepadStates);
}; // class RaylibGamepadInput
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_GAMEPAD_INPUT_HPP