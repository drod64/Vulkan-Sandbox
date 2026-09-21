#ifndef INPUT_CONTROL_HPP
#define INPUT_CONTROL_HPP
#include <conduit/core/containers/variant.hpp>
#include <conduit/input/InputTypes.hpp>

namespace conduit {
/**
 * Supported control types of Conduit.
 */
using InputControl = variant <
    GamepadAxis,
    GamepadButton,
    Key,
    MouseButton >;
} // namespace conduit

#endif // INPUT_CONTROL_HPP