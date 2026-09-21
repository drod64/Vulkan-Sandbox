#ifndef CONDUIT_MOUSE_STATE_HPP
#define CONDUIT_MOUSE_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/input/mouse/MouseButton.hpp>
#include <sm/Vec2.h>

namespace conduit {
/**
 * State tracker for the polled mouse.
 */
class MouseState {
private:
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(MouseButton::MAX_COUNT)> m_previous{};

    sm::Vec2 m_position{};
    sm::Vec2 m_delta{};
    sm::Vec2 m_wheel{};

public:
    MouseState() = default;
    ~MouseState() = default;

    /**
     * @param mouseButton the mouse button to check
     * 
     * @return true if the specified button is down, false otherwise
     */
    bool isDown(MouseButton mouseButton) const;

    /**
     * @param mouseButton the mouse button to check
     * 
     * @return true if the specified button was pressed, false otherwise
     */
    bool wasPressed(MouseButton mouseButton) const;

    /**
     * @param mouseButton the mouse button to check
     * 
     * @return true if the specified button was released, false otherwise
     */
    bool wasReleased(MouseButton mouseButton) const;

    /**
     * @return the position of the mouse
     */
    sm::Vec2 position() const;

    /**
     * @return the delta of the mouse
     */
    sm::Vec2 delta() const;

    /**
     * @return the wheel speed of the mouse
     */
    sm::Vec2 wheel() const;

    /**
     * Resets the state of the mouse.
     */
    void reset();

    /**
     * Sets the specified mouse button to on/off.
     * 
     * @param mouseButton the mouse button to set
     * @param state the state of the mouse button
     */
    void setButton(MouseButton mouseButton, bool state);

    /**
     * Updates the position of the mouse.
     * 
     * @param position the new position of the mouse
     */
    void updatePosition(sm::Vec2 position);

    /**
     * Updates the delta of the mouse.
     * 
     * @param delta the new delta of the mouse
     */
    void updateDelta(sm::Vec2 delta);

    /**
     * Updates the wheel speed of the mouse
     * 
     * @param wheel the new wheel speed of the mouse
     */
    void updateWheel(sm::Vec2 wheel);

    /**
     * Updates the previous state of the mouse.
     * This is essential for the wasPressed()/wasReleased() operations.
     */
    void updatePrevious();

}; // class MouseState
} // namespace conduit

#endif // CONDUIT_MOUSE_STATE_HPP