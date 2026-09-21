#ifndef CONDUIT_GAME_PAD_BUTTON_HPP
#define CONDUIT_GAME_PAD_BUTTON_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
/**
 * Gamepad buttons supported by Conduit.
 * These ideally should be valued from 0 - N.
 */
enum class GamepadButton : uint16 {
    A = 0,
    B,
    X,
    Y,
    LEFT_BUMPER,
    RIGHT_BUMPER,
    BACK,
    START,
    GUIDE,
    LEFT_STICK,
    RIGHT_STICK,
    D_PAD_UP,
    D_PAD_DOWN,
    D_PAD_RIGHT,
    D_PAD_LEFT,

    MAX_COUNT
}; // enum class GamepadButton
} // namespace conduit

#endif // CONDUIT_GAME_PAD_BUTTON_HPP
