#ifndef CONDUIT_MOUSE_BUTTON_HPP
#define CONDUIT_MOUSE_BUTTON_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
/**
 * Mouse buttons supported by Conduit.
 * These ideally should be valued from 0 - N.
 */
enum class MouseButton : uint16 {
    LEFT = 0,
    RIGHT,
    MIDDLE,

    SIDE,
    FORWARD,
    BACK,
    EXTRA,

    MAX_COUNT
}; // enum class MouseButton
} // namespace conduit

#endif // CONDUIT_MOUSE_BUTTON_HPP