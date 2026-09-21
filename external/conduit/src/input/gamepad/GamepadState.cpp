#include <conduit/input/gamepad/GamepadState.hpp>

bool conduit::GamepadState::isConnected() const
{
    return m_connected;
}

bool conduit::GamepadState::isDown(GamepadButton gamepadButton) const
{
    const sizet index = static_cast<sizet>(gamepadButton);

    return m_current.test(index);
}

bool conduit::GamepadState::wasPressed(GamepadButton gamepadButton) const
{
    const sizet index = static_cast<sizet>(gamepadButton);

    return !m_previous.test(index) && m_current.test(index);
}

bool conduit::GamepadState::wasReleased(GamepadButton gamepadButton) const
{
    const sizet index = static_cast<sizet>(gamepadButton);

    return m_previous.test(index) && !m_current.test(index);
}

conduit::real conduit::GamepadState::axisValue(GamepadAxis gamepadAxis) const
{
    const sizet index = static_cast<sizet>(gamepadAxis);

    return m_axes[index];
}

void conduit::GamepadState::reset()
{
    m_axes.fill(static_cast<real>(0));
    m_current.reset();
    m_previous.reset();
}

void conduit::GamepadState::setConnection(bool state)
{
    m_connected = state;
}

void conduit::GamepadState::setButton(GamepadButton gamepadButton, bool state)
{
    sizet index = static_cast<sizet>(gamepadButton);

    m_current.set(index, state);
}

void conduit::GamepadState::setAxis(GamepadAxis gamepadAxis, real value)
{
    sizet index = static_cast<sizet>(gamepadAxis);
    m_axes[index] = value;
}

void conduit::GamepadState::updatePrevious()
{
    m_previous = m_current;
}