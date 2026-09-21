#ifndef CONDUIT_GAMEPAD_STATES_HPP
#define CONDUIT_GAMEPAD_STATES_HPP
#include <conduit/core/config.hpp>
#include <conduit/input/gamepad/GamepadState.hpp>

namespace conduit {
    using GamepadStates = array<GamepadState, config::MAX_GAMEPADS>;
} // namespace conduit

#endif // CONDUIT_GAMEPAD_STATES_HPP