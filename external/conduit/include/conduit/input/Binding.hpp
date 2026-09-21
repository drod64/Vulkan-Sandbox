#ifndef CONDUIT_BINDING_HPP
#define CONDUIT_BINDING_HPP
#include <conduit/input/InputControl.hpp>

namespace conduit {
/**
 * Simple struct that represents a binding.
 */
struct Binding {
    Binding(InputControl control, real scale = static_cast<real>(1)) :
    control(control),
    scale(scale)
    {}
    
    InputControl    control{};
    real            scale{};
}; // struct Binding
} // namespace conduit

#endif // CONDUIT_BINDING_HPP