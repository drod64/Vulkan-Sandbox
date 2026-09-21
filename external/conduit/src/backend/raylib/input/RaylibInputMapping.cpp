#include <conduit/backend/raylib/input/RaylibInputMapping.hpp>

raylibKeyButton conduit::raylib::toRaylibKeyButton(conduit::Key key)
{
    switch (key)
    {
        case Key::A:
            return KEY_A;
        
        case Key::B:
            return KEY_B;

        case Key::C:
            return KEY_C;

        case Key::D:
            return KEY_D;

        case Key::E:
            return KEY_E;

        case Key::F:
            return KEY_F;

        case Key::G:
            return KEY_G;

        case Key::H:
            return KEY_H;
        
        case Key::I:
            return KEY_I;
        
        case Key::J:
            return KEY_J;

        case Key::K:
            return KEY_K;

        case Key::L:
            return KEY_L;

        case Key::M:
            return KEY_M;

        case Key::N:
            return KEY_N;
        
        case Key::O:
            return KEY_O;

        case Key::P:
            return KEY_P;

        case Key::Q:
            return KEY_Q;

        case Key::R:
            return KEY_R;

        case Key::S:
            return KEY_S;
        
        case Key::T:
            return KEY_T;

        case Key::U:
            return KEY_U;

        case Key::V:
            return KEY_V;

        case Key::W:
            return KEY_W;
        
        case Key::X:
            return KEY_X;
        
        case Key::Y:
            return KEY_Y;
        
        case Key::Z:
            return KEY_Z;

        case Key::NUM_0:
            return KEY_ZERO;

        case Key::NUM_1:
            return KEY_ONE;

        case Key::NUM_2:
            return KEY_TWO;

        case Key::NUM_3:
            return KEY_THREE;
        
        case Key::NUM_4:
            return KEY_FOUR;
        
        case Key::NUM_5:
            return KEY_FIVE;

        case Key::NUM_6:
            return KEY_SIX;
        
        case Key::NUM_7:
            return KEY_SEVEN;

        case Key::NUM_8:
            return KEY_EIGHT;

        case Key::NUM_9:
            return KEY_NINE;

        case Key::F1:
            return KEY_F1;

        case Key::F2:
            return KEY_F2;

        case Key::F3:
            return KEY_F3;

        case Key::F4:
            return KEY_F4;

        case Key::F5:
            return KEY_F5;

        case Key::F6:
            return KEY_F6;

        case Key::F7:
            return KEY_F7;

        case Key::F8:
            return KEY_F8;

        case Key::F9:
            return KEY_F9;
        
        case Key::F10:
            return KEY_F10;

        case Key::F11:
            return KEY_F11;

        case Key::F12:
            return KEY_F12;

        case Key::LEFT_SHIFT:
            return KEY_LEFT_SHIFT;
        
        case Key::RIGHT_SHIFT:
            return KEY_RIGHT_SHIFT;
        
        case Key::LEFT_CONTROL:
            return KEY_LEFT_CONTROL;
        
        case Key::RIGHT_CONTROL:
            return KEY_RIGHT_CONTROL;

        case Key::LEFT_ALT:
            return KEY_LEFT_ALT;

        case Key::RIGHT_ALT:
            return KEY_RIGHT_ALT;

        case Key::LEFT_SUPER:
            return KEY_LEFT_SUPER;
        
        case Key::RIGHT_SUPER:
            return KEY_RIGHT_SUPER;

        case Key::UP:
            return KEY_UP;

        case Key::DOWN:
            return KEY_DOWN;

        case Key::RIGHT:
            return KEY_RIGHT;
        
        case Key::LEFT:
            return KEY_LEFT;

        case Key::HOME:
            return KEY_HOME;

        case Key::END:
            return KEY_END;

        case Key::PAGE_UP:
            return KEY_PAGE_UP;

        case Key::PAGE_DOWN:
            return KEY_PAGE_DOWN;

        case Key::INSERT:
            return KEY_INSERT;

        case Key::DELETE:
            return KEY_DELETE;

        case Key::BACKSPACE:
            return KEY_BACKSPACE;

        case Key::ENTER:
            return KEY_ENTER;
        
        case Key::TAB:
            return KEY_TAB;
        
        case Key::ESCAPE:
            return KEY_ESCAPE;

        case Key::SPACE:
            return KEY_SPACE;
        
        case Key::APOSTOPHRE:
            return KEY_APOSTROPHE;
        
        case Key::COMMA:
            return KEY_COMMA;

        case Key::MINUS:
            return KEY_MINUS;

        case Key::PERIOD:
            return KEY_PERIOD;

        case Key::SLASH:
            return KEY_SLASH;

        case Key::SEMICOLON:
            return KEY_SEMICOLON;
        
        case Key::EQUAL:
            return KEY_EQUAL;
        
        case Key::LEFT_BRACKET:
            return KEY_LEFT_BRACKET;
        
        case Key::BACKSLASH:
            return KEY_BACKSLASH;

        case Key::RIGHT_BRACKET:
            return KEY_RIGHT_BRACKET;

        case Key::GRAVE:
            return KEY_GRAVE;

        case Key::KP_0:
            return KEY_KP_0;
        
        case Key::KP_1:
            return KEY_KP_1;

        case Key::KP_2:
            return KEY_KP_2;

        case Key::KP_3:
            return KEY_KP_3;

        case Key::KP_4:
            return KEY_KP_4;

        case Key::KP_5:
            return KEY_KP_5;

        case Key::KP_6:
            return KEY_KP_6;

        case Key::KP_7:
            return KEY_KP_7;

        case Key::KP_8:
            return KEY_KP_8;

        case Key::KP_9:
            return KEY_KP_9;

        case Key::KP_DECIMAL:
            return KEY_KP_DECIMAL;
        
        case Key::KP_DIVIDE:
            return KEY_KP_DIVIDE;

        case Key::KP_MULTIPLY:
            return KEY_KP_MULTIPLY;

        case Key::KP_SUBTRACT:
            return KEY_KP_SUBTRACT;

        case Key::KP_ADD:
            return KEY_KP_ADD;
        
        case Key::KP_ENTER:
            return KEY_KP_ENTER;

        case Key::CAPS_LOCK:
            return KEY_CAPS_LOCK;
        
        case Key::NUM_LOCK:
            return KEY_NUM_LOCK;
        
        case Key::SCROLL_LOCK:
            return KEY_SCROLL_LOCK;

        case Key::PRINT_SCREEN:
            return KEY_PRINT_SCREEN;
        
        case Key::PAUSE:
            return KEY_PAUSE;
        
        case Key::MENU:
            return KEY_MENU;
        
        default:
            return KEY_NULL;
    }
}

raylibMouseButton conduit::raylib::toRaylibMouseButton(conduit::MouseButton mouseButton)
{
    switch (mouseButton)
    {
        case MouseButton::LEFT:
            return MOUSE_BUTTON_LEFT;
        
        case MouseButton::RIGHT:
            return MOUSE_BUTTON_RIGHT;
        
        case MouseButton::MIDDLE:
            return MOUSE_BUTTON_MIDDLE;
        
        case MouseButton::SIDE:
            return MOUSE_BUTTON_SIDE;
        
        case MouseButton::FORWARD:
            return MOUSE_BUTTON_FORWARD;
        
        case MouseButton::BACK:
            return MOUSE_BUTTON_BACK;
        
        case MouseButton::EXTRA:
            return MOUSE_BUTTON_EXTRA;
    }

    assert(false && "[RaylibInputMapping] - Invalid MouseButton value.");
    std::abort();
}

raylibGamepadButton conduit::raylib::toRaylibGamepadButton(conduit::GamepadButton gamepadButton)
{
    switch (gamepadButton)
    {
        case GamepadButton::A:
            return GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
        
        case GamepadButton::B:
            return GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
        
        case GamepadButton::X:
            return GAMEPAD_BUTTON_RIGHT_FACE_LEFT;
        
        case GamepadButton::Y:
            return GAMEPAD_BUTTON_RIGHT_FACE_UP;
        
        case GamepadButton::LEFT_BUMPER:
            return GAMEPAD_BUTTON_LEFT_TRIGGER_1;
        
        case GamepadButton::RIGHT_BUMPER:
            return GAMEPAD_BUTTON_RIGHT_TRIGGER_1;
        
        case GamepadButton::BACK:
            return GAMEPAD_BUTTON_MIDDLE_LEFT;
        
        case GamepadButton::START:
            return GAMEPAD_BUTTON_MIDDLE_RIGHT;
        
        case GamepadButton::GUIDE:
            return GAMEPAD_BUTTON_MIDDLE;

        case GamepadButton::LEFT_STICK:
            return GAMEPAD_BUTTON_LEFT_THUMB;
        
        case GamepadButton::RIGHT_STICK:
            return GAMEPAD_BUTTON_RIGHT_THUMB;

        case GamepadButton::D_PAD_UP:
            return GAMEPAD_BUTTON_LEFT_FACE_UP;
        
        case GamepadButton::D_PAD_DOWN:
            return GAMEPAD_BUTTON_LEFT_FACE_DOWN;
        
        case GamepadButton::D_PAD_RIGHT:
            return GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
        
        case GamepadButton::D_PAD_LEFT:
            return GAMEPAD_BUTTON_LEFT_FACE_LEFT;
    }

    assert(false && "[RaylibInputMapping] - Invalid GamepadButton value.");
    std::abort();
}

raylibGamepadAxis conduit::raylib::toRaylibGamepadAxis(conduit::GamepadAxis gamepadAxis)
{
    switch (gamepadAxis)
    {
        case GamepadAxis::LEFT_STICK_X:
            return GAMEPAD_AXIS_LEFT_X;

        case GamepadAxis::LEFT_STICK_Y:
            return GAMEPAD_AXIS_LEFT_Y;
        
        case GamepadAxis::RIGHT_STICK_X:
            return GAMEPAD_AXIS_RIGHT_X;
            
        case GamepadAxis::RIGHT_STICK_Y:
            return GAMEPAD_AXIS_RIGHT_Y;

        case GamepadAxis::LEFT_TRIGGER:
            return GAMEPAD_AXIS_LEFT_TRIGGER;

        case GamepadAxis::RIGHT_TRIGGER:
            return GAMEPAD_AXIS_RIGHT_TRIGGER;
    }

    assert(false && "[RaylibInputMapping] - Invalid GamepadAxis value.");
    std::abort();
}