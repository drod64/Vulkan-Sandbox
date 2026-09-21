#include <conduit/input/Input.hpp>

conduit::Input::Input(const conduit::Window &window) :
m_window(window)
{}

const conduit::KeyboardState& conduit::Input::keyboard() const
{
    return m_keyboard_state;
}

conduit::KeyboardState& conduit::Input::keyboard()
{
    return m_keyboard_state;
}

const conduit::MouseState& conduit::Input::mouse() const
{
    return m_mouse_state;
}

conduit::MouseState& conduit::Input::mouse()
{
    return m_mouse_state;
}

const conduit::GamepadStates& conduit::Input::gamepads() const
{
    return m_gamepad_states;
}

conduit::GamepadStates& conduit::Input::gamepads()
{
    return m_gamepad_states;
}

void conduit::Input::poll()
{
    conduit::platform::input::poll(m_window.m_platform_window, *this);
}