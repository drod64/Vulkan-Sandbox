#ifndef CONDUIT_GAME_PAD_AXIS_HPP
#define CONDUIT_GAME_PAD_AXIS_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
/**
 * Gamepad axes supported by Conduit.
 * These ideally should be valued from 0 - N.
 */
enum class GamepadAxis : uint16 {
    LEFT_STICK_X = 0,
    LEFT_STICK_Y,
    RIGHT_STICK_X,
    RIGHT_STICK_Y,

    LEFT_TRIGGER,
    RIGHT_TRIGGER,

    MAX_COUNT
}; // enum class GamepadAxis
} // namespace conduit

#endif // CONDUIT_GAME_PAD_AXIS_HPP