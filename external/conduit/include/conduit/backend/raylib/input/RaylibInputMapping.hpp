#ifndef CONDUIT_RAYLIB_INPUT_MAPPING_HPP
#define CONDUIT_RAYLIB_INPUT_MAPPING_HPP
#include <cassert>
#include <cstdlib>
#include <raylib.h>
#include <conduit/input/keyboard/Key.hpp>
#include <conduit/input/mouse/MouseButton.hpp>
#include <conduit/input/gamepad/GamepadButton.hpp>
#include <conduit/input/gamepad/GamepadAxis.hpp>

using raylibKeyButton = KeyboardKey;
using raylibMouseButton = MouseButton;
using raylibGamepadButton = GamepadButton;
using raylibGamepadAxis = GamepadAxis;

namespace conduit::raylib {
    /**
     * Converts a conduit::Key to a raylib KeyboardKey.
     * 
     * @param key the key to convert
     * 
     * @return the raylib KeyboardKey value
     */
    raylibKeyButton toRaylibKeyButton(conduit::Key key);

    /**
     * Converts a conduit::MouseButton to a raylib MouseButton.
     * 
     * @param mouseButton the mouse button to convert
     * 
     * @return the raylib MouseButton value
     */
    raylibMouseButton toRaylibMouseButton(conduit::MouseButton mouseButton);

    /**
     * Converts a conduit::GamepadButton to a raylib GamepadButton.
     * 
     * @param gamepadButton the gamepad button to convert
     * 
     * @return the raylib GamepadButton value
     */
    raylibGamepadButton toRaylibGamepadButton(conduit::GamepadButton gamepadButton);

    /**
     * Converts a conduit::GamedpadAxis to a raylibG GamepadAxis.
     * 
     * @param gamepadAxis
     * 
     * @return the raylib GamepadAxis value
     */
    raylibGamepadAxis toRaylibGamepadAxis(conduit::GamepadAxis gamepadAxis);
} // namespace conduit::raylib

#endif // CONDUIT_RAYLIB_INPUT_MAPPING_HPP