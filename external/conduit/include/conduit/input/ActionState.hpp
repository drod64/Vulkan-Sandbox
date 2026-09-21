#ifndef CONDUIT_ACTION_STATE_HPP
#define CONDUIT_ACTION_STATE_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
/**
 * Simple state tracker of an action.
 */
struct ActionState {
    real    current{};
    real    previous{};
}; 
} // namespace conduit

#endif // CONDUIT_ACTION_STATE_HPP