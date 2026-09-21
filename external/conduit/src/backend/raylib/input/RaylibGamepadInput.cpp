#include <conduit/backend/raylib/input/RaylibGamepadInput.hpp>

void conduit::raylib::RaylibGamepadInput::pollConnection(int gamepad, GamepadState &state)
{
    const bool connected = IsGamepadAvailable(gamepad);

    // Disconnected controller
    if (!connected)
    {
        state.reset();
        state.setConnection(false);
        return;
    }

    // Newly connected controller
    if (!state.isConnected())
    {
        state.reset();
    }

    state.setConnection(true);
}

void conduit::raylib::RaylibGamepadInput::pollAxes(int gamepad, GamepadState &state)
{
    const int AXIS_COUNT = GetGamepadAxisCount(gamepad);

    for (sizet axis = 0; axis < static_cast<sizet>(GamepadAxis::MAX_COUNT); ++axis)
    {
        conduit::GamepadAxis gamepad_axis = static_cast<conduit::GamepadAxis>(axis);
        raylibGamepadAxis raylib_gamepad_axis = conduit::raylib::toRaylibGamepadAxis(gamepad_axis);

        if (raylib_gamepad_axis >= AXIS_COUNT)
        {
            state.setAxis(gamepad_axis, static_cast<real>(0));
            continue;
        }

        state.setAxis(gamepad_axis, static_cast<real>(GetGamepadAxisMovement(gamepad, raylib_gamepad_axis)));
    }
}

void conduit::raylib::RaylibGamepadInput::pollButtons(int gamepad, GamepadState &state)
{
    // Update previous button state of gamepad
    state.updatePrevious();

    // Update current button state of gamepad
    for (sizet button = 0; button < static_cast<sizet>(GamepadButton::MAX_COUNT); ++button)
    {
        conduit::GamepadButton gamepad_button = static_cast<GamepadButton>(button);
        raylibGamepadButton raylib_gamepad_button = conduit::raylib::toRaylibGamepadButton(gamepad_button);

        state.setButton(gamepad_button, IsGamepadButtonDown(gamepad, raylib_gamepad_button));
    }
}

void conduit::raylib::RaylibGamepadInput::poll(GamepadStates &gamepadStates)
{
    for (sizet gamepad = 0; gamepad < gamepadStates.size(); ++gamepad)
    {
        GamepadState &gamepad_state = gamepadStates[gamepad];
    
        pollConnection(static_cast<int>(gamepad), gamepad_state);
        if (!gamepad_state.isConnected()) continue;

        pollAxes(static_cast<int>(gamepad), gamepad_state);
        
        pollButtons(static_cast<int>(gamepad), gamepad_state);
    }
}