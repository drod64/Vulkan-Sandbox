#ifndef CONDUIT_GAMEPAD_STATE_HPP
#define CONDUIT_GAMEPAD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/array.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/input/gamepad/GamepadButton.hpp>
#include <conduit/input/gamepad/GamepadAxis.hpp>

namespace conduit {
/**
 * State tracker of polled gamepads.
 */
class GamepadState {
private:
    bool m_connected = false;
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> m_previous{};
    array<real, static_cast<sizet>(GamepadAxis::MAX_COUNT)> m_axes{};

public:
    GamepadState() = default;
    ~GamepadState() = default;

    /**
     * @return true if the gamepad is connected, false otherwise
     */
    bool isConnected() const;

    /**
     * @param gamepadButton the button to check
     * 
     * @return true if the specified button is down, false otherwise
     */
    bool isDown(GamepadButton gamepadButton) const;

    /**
     * @param gamepadButton the button to check
     * 
     * @return true if the specified button was pressed, false otherwise
     */
    bool wasPressed(GamepadButton gamepadButton) const;

    /**
     * @param gamepadButton the button to check
     * 
     * @return true if the specified button was released, false otherwise
     */
    bool wasReleased(GamepadButton gamepadButton) const;

    /**
     * @param gamepadAxis the axis to check
     * 
     * @return the value of the specified axis which ranges from [-1, 1]
     */
    real axisValue(GamepadAxis gamepadAxis) const;

    /**
     * Resets the state of the gamepad.
     */
    void reset();

    /**
     * Sets the connection status of the gamepad.
     * 
     * @param state the state of connection
     */
    void setConnection(bool state);

    /**
     * Sets a specified button to on/off.
     * 
     * @param gamepadButton the button to set
     * @param state the state of the button
     */
    void setButton(GamepadButton gamepadButton, bool state);

    /**
     * Sets a specified axis to a value.
     * 
     * @param gamepadAxis the axis to set
     * @param value the value of the axis
     */
    void setAxis(GamepadAxis gamepadAxis, real value);

    /**
     * Updates the previous state of the gamepad.
     * This is essential for the wasPressed()/wasReleased() operations.
     */
    void updatePrevious();
}; // class GamepadState
} // namespace conduit

#endif // CONDUIT_GAMEPAD_STATE_HPP