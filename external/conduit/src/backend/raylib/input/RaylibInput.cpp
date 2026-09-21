#include <conduit/backend/raylib/input/RaylibInput.hpp>

void conduit::raylib::RaylibInput::pollKeyboard(KeyboardState &keyboardState)
{
    // Update previous button state of keyboard
    keyboardState.updatePrevious();

    // Update current button state of keyboard
    for (sizet i = 0; i < static_cast<sizet>(Key::MAX_COUNT); ++i)
    {
        conduit::Key key = static_cast<conduit::Key>(i);
        raylibKeyButton raylib_key = conduit::raylib::toRaylibKeyButton(key);

        keyboardState.setKey(key, IsKeyDown(raylib_key));
    }
}

void conduit::raylib::RaylibInput::pollMouse(MouseState &mouseState)
{
    // Update previous button state of mouse
    mouseState.updatePrevious();

    // Update current button state of mouse
    for (sizet i = 0; i < static_cast<sizet>(MouseButton::MAX_COUNT); ++i)
    {
        conduit::MouseButton mouseButton = static_cast<conduit::MouseButton>(i);

        raylibMouseButton raylib_mouse_button = conduit::raylib::toRaylibMouseButton(mouseButton);

        mouseState.setButton(mouseButton, IsMouseButtonDown(raylib_mouse_button));
    }

    // Update mouse axes
    using raylibVec2 = Vector2;
    raylibVec2 rl_mouse_position = raylibVec2(GetMousePosition());
    raylibVec2 rl_mouse_delta = raylibVec2(GetMouseDelta());
    raylibVec2 rl_mouse_wheel = raylibVec2(GetMouseWheelMoveV());
    // Translate to sm::Vec2
    mouseState.updatePosition({rl_mouse_position.x, rl_mouse_position.y});
    mouseState.updateDelta({rl_mouse_delta.x, rl_mouse_delta.y});
    mouseState.updateWheel({rl_mouse_wheel.x, rl_mouse_delta.y});
}

void conduit::raylib::RaylibInput::pollGamepads(GamepadStates &gamepadStates)
{
    m_gamepad_input.poll(gamepadStates);
}

void conduit::raylib::RaylibInput::poll(Input &input)
{
    pollKeyboard(input.m_keyboard_state);
    pollMouse(input.m_mouse_state);
    pollGamepads(input.m_gamepad_states);
}