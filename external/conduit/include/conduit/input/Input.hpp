#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <conduit/input/gamepad/GamepadStates.hpp>
#include <conduit/input/keyboard/KeyboardState.hpp>
#include <conduit/input/mouse/MouseState.hpp>
#include <conduit/window/Window.hpp>

namespace conduit {
/**
 * State tracker of all supported input sources (keyboard, mouse, gamepads).
 */
class Input {
private:
    const conduit::Window                      &m_window;
    KeyboardState                               m_keyboard_state{};
    MouseState                                  m_mouse_state{};
    GamepadStates                               m_gamepad_states{};

public:
    /**
     * Parameterized constructor.
     * 
     * Every Input object must be linked to a conduit::Window in order
     * to poll input pertaining to that window.
     * 
     * @param window the window to link the Input to
     */
    Input(const conduit::Window &window);
    ~Input() = default;

    /**
     * @return the state of the keyboard for the current frame
     */
    const KeyboardState& keyboard() const;
    KeyboardState& keyboard();

    /**
     * @return the state of the mouse for the current frame
     */
    const MouseState& mouse() const;
    MouseState& mouse();

    /**
     * @return the state of the gamepads for the current frame
     */
    const GamepadStates& gamepads() const;
    GamepadStates& gamepads();

    /**
     * Polls the input state of the frame.
     * Results can be extracted via Input's keyboard(), mouse(), and gamepads() calls.
     */
    void poll();
}; // class Input
} // namespace conduit

#endif // CONDUIT_INPUT_HPP