#include <conduit/backend/glfw/input/GLFWInputMapping.hpp>

conduit::glfw::input::glfwKey conduit::glfw::input::toGLFWKeyButton(conduit::Key key)
{
    switch (key)
    {
        case Key::A:
            return GLFW_KEY_A;
        
        case Key::B:
            return GLFW_KEY_B;

        case Key::C:
            return GLFW_KEY_C;
        
        case Key::D:
            return GLFW_KEY_D;

        case Key::E:
            return GLFW_KEY_E;

        case Key::F:
            return GLFW_KEY_F;

        case Key::G:
            return GLFW_KEY_G;

        case Key::H:
            return GLFW_KEY_H;

        case Key::I:
            return GLFW_KEY_I;
        
        case Key::J:
            return GLFW_KEY_J;
        
        case Key::K:
            return GLFW_KEY_K;

        case Key::L:
            return GLFW_KEY_L;

        case Key::M:
            return GLFW_KEY_M;

        case Key::N:
            return GLFW_KEY_N;

        case Key::O:
            return GLFW_KEY_O;

        case Key::P:
            return GLFW_KEY_P;

        case Key::Q:
            return GLFW_KEY_Q;

        case Key::R:
            return GLFW_KEY_R;

        case Key::S:
            return GLFW_KEY_S;

        case Key::T:
            return GLFW_KEY_T;

        case Key::U:
            return GLFW_KEY_U;

        case Key::V:
            return GLFW_KEY_V;

        case Key::W:
            return GLFW_KEY_W;

        case Key::X:
            return GLFW_KEY_X;
        
        case Key::Y:
            return GLFW_KEY_Y;

        case Key::Z:
            return GLFW_KEY_Z;

        case Key::NUM_0:
            return GLFW_KEY_0;

        case Key::NUM_1:
            return GLFW_KEY_1;

        case Key::NUM_2:
            return GLFW_KEY_2;
        
        case Key::NUM_3:
            return GLFW_KEY_3;

        case Key::NUM_4:
            return GLFW_KEY_4;

        case Key::NUM_5:
            return GLFW_KEY_5;

        case Key::NUM_6:
            return GLFW_KEY_6;

        case Key::NUM_7:
            return GLFW_KEY_7;

        case Key::NUM_8:
            return GLFW_KEY_8;

        case Key::NUM_9:
            return GLFW_KEY_9;

        case Key::F1:
            return GLFW_KEY_F1;
        
        case Key::F2:
            return GLFW_KEY_F2;

        case Key::F3:
            return GLFW_KEY_F3;

        case Key::F4:
            return GLFW_KEY_F4;

        case Key::F5:
            return GLFW_KEY_F5;

        case Key::F6:
            return GLFW_KEY_F6;

        case Key::F7:
            return GLFW_KEY_F7;

        case Key::F8:
            return GLFW_KEY_F8;

        case Key::F9:
            return GLFW_KEY_F9;

        case Key::F10:
            return GLFW_KEY_F10;

        case Key::F11:
            return GLFW_KEY_F11;

        case Key::F12:
            return GLFW_KEY_F12;

        case Key::LEFT_SHIFT:
            return GLFW_KEY_LEFT_SHIFT;

        case Key::RIGHT_SHIFT:
            return GLFW_KEY_RIGHT_SHIFT;

        case Key::LEFT_CONTROL:
            return GLFW_KEY_LEFT_CONTROL;

        case Key::RIGHT_CONTROL:
            return GLFW_KEY_RIGHT_CONTROL;

        case Key::LEFT_ALT:
            return GLFW_KEY_LEFT_ALT;

        case Key::RIGHT_ALT:
            return GLFW_KEY_RIGHT_ALT;

        case Key::LEFT_SUPER:
            return GLFW_KEY_LEFT_SUPER;

        case Key::RIGHT_SUPER:
            return GLFW_KEY_RIGHT_SUPER;

        case Key::UP:
            return GLFW_KEY_UP;

        case Key::DOWN:
            return GLFW_KEY_DOWN;

        case Key::RIGHT:
            return GLFW_KEY_RIGHT;

        case Key::LEFT:
            return GLFW_KEY_LEFT;

        case Key::HOME:
            return GLFW_KEY_HOME;

        case Key::END:
            return GLFW_KEY_END;

        case Key::PAGE_UP:
            return GLFW_KEY_PAGE_UP;

        case Key::PAGE_DOWN:
            return GLFW_KEY_PAGE_DOWN;

        case Key::INSERT:
            return GLFW_KEY_INSERT;

        case Key::DELETE:
            return GLFW_KEY_DELETE;

        case Key::BACKSPACE:
            return GLFW_KEY_BACKSPACE;

        case Key::ENTER:
            return GLFW_KEY_ENTER;

        case Key::TAB:
            return GLFW_KEY_TAB;

        case Key::ESCAPE:
            return GLFW_KEY_ESCAPE;

        case Key::SPACE:
            return GLFW_KEY_SPACE;

        case Key::APOSTOPHRE:
            return GLFW_KEY_APOSTROPHE;

        case Key::COMMA:
            return GLFW_KEY_COMMA;

        case Key::MINUS:
            return GLFW_KEY_MINUS;

        case Key::PERIOD:
            return GLFW_KEY_PERIOD;

        case Key::SLASH:
            return GLFW_KEY_SLASH;

        case Key::SEMICOLON:
            return GLFW_KEY_SEMICOLON;

        case Key::EQUAL:
            return GLFW_KEY_EQUAL;

        case Key::LEFT_BRACKET:
            return GLFW_KEY_LEFT_BRACKET;

        case Key::BACKSLASH:
            return GLFW_KEY_BACKSLASH;

        case Key::RIGHT_BRACKET:
            return GLFW_KEY_RIGHT_BRACKET;

        case Key::GRAVE:
            return GLFW_KEY_GRAVE_ACCENT;

        case Key::KP_0:
            return GLFW_KEY_KP_0;
            
        case Key::KP_1:
            return GLFW_KEY_KP_1;

        case Key::KP_2:
            return GLFW_KEY_KP_2;

        case Key::KP_3:
            return GLFW_KEY_KP_3;

        case Key::KP_4:
            return GLFW_KEY_KP_4;

        case Key::KP_5:
            return GLFW_KEY_KP_5;

        case Key::KP_6:
            return GLFW_KEY_KP_6;

        case Key::KP_7:
            return GLFW_KEY_KP_7;

        case Key::KP_8:
            return GLFW_KEY_KP_8;

        case Key::KP_9:
            return GLFW_KEY_KP_9;
        
        case Key::KP_DECIMAL:
            return GLFW_KEY_KP_DECIMAL;

        case Key::KP_DIVIDE:
            return GLFW_KEY_KP_DIVIDE;

        case Key::KP_MULTIPLY:
            return GLFW_KEY_KP_MULTIPLY;

        case Key::KP_SUBTRACT:
            return GLFW_KEY_KP_SUBTRACT;

        case Key::KP_ADD:
            return GLFW_KEY_KP_ADD;

        case Key::KP_ENTER:
            return GLFW_KEY_KP_ENTER;

        case Key::CAPS_LOCK:
            return GLFW_KEY_CAPS_LOCK;

        case Key::NUM_LOCK:
            return GLFW_KEY_NUM_LOCK;

        case Key::SCROLL_LOCK:
            return GLFW_KEY_SCROLL_LOCK;

        case Key::PRINT_SCREEN:
            return GLFW_KEY_PRINT_SCREEN;

        case Key::PAUSE:
            return GLFW_KEY_PAUSE;
        
        case Key::MENU:
            return GLFW_KEY_MENU;

        default:
            return GLFW_KEY_UNKNOWN;
    }
}

conduit::glfw::input::glfwMouseButton conduit::glfw::input::toGLFWMouseButton(conduit::MouseButton mouseButton)
{
    switch (mouseButton)
    {
        case MouseButton::LEFT:
            return GLFW_MOUSE_BUTTON_LEFT;
        
        case MouseButton::RIGHT:
            return GLFW_MOUSE_BUTTON_RIGHT;

        case MouseButton::MIDDLE:
            return GLFW_MOUSE_BUTTON_MIDDLE;
        
        case MouseButton::SIDE:
            return GLFW_MOUSE_BUTTON_4;

        case MouseButton::FORWARD:
            return GLFW_MOUSE_BUTTON_5;

        case MouseButton::BACK:
            return GLFW_MOUSE_BUTTON_6;

        case MouseButton::EXTRA:
            return GLFW_MOUSE_BUTTON_7;
    }

    assert(false && "[GLFWInputMapping] - Invalid MouseButton value.");
    std::abort();
}

conduit::glfw::input::glfwGamepadButton conduit::glfw::input::toGLFWGamepadButton(conduit::GamepadButton gamepadButton)
{
    switch (gamepadButton)
    {
        case GamepadButton::A:
            return GLFW_GAMEPAD_BUTTON_A;
        
        case GamepadButton::B:
            return GLFW_GAMEPAD_BUTTON_B;

        case GamepadButton::X:
            return GLFW_GAMEPAD_BUTTON_X;

        case GamepadButton::Y:
            return GLFW_GAMEPAD_BUTTON_Y;

        case GamepadButton::LEFT_BUMPER:
            return GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;

        case GamepadButton::RIGHT_BUMPER:
            return GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;

        case GamepadButton::BACK:
            return GLFW_GAMEPAD_BUTTON_BACK;

        case GamepadButton::START:
            return GLFW_GAMEPAD_BUTTON_START;

        case GamepadButton::GUIDE:
            return GLFW_GAMEPAD_BUTTON_GUIDE;

        case GamepadButton::LEFT_STICK:
            return GLFW_GAMEPAD_BUTTON_LEFT_THUMB;

        case GamepadButton::RIGHT_STICK:
            return GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;

        case GamepadButton::D_PAD_UP:
            return GLFW_GAMEPAD_BUTTON_DPAD_UP;

        case GamepadButton::D_PAD_DOWN:
            return GLFW_GAMEPAD_BUTTON_DPAD_DOWN;

        case GamepadButton::D_PAD_RIGHT:
            return GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;

        case GamepadButton::D_PAD_LEFT:
            return GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
    }

    assert(false && "[GLFWInputMapping] - Invalid GamepadButton value.");
    std::abort();
}

conduit::glfw::input::glfwGamepadAxis conduit::glfw::input::toGLFWGamepadAxis(conduit::GamepadAxis gamepadAxis)
{
    switch (gamepadAxis)
    {
        case GamepadAxis::LEFT_STICK_X:
            return GLFW_GAMEPAD_AXIS_LEFT_X;

        case GamepadAxis::LEFT_STICK_Y:
            return GLFW_GAMEPAD_AXIS_LEFT_Y;

        case GamepadAxis::RIGHT_STICK_X:
            return GLFW_GAMEPAD_AXIS_RIGHT_X;

        case GamepadAxis::RIGHT_STICK_Y:
            return GLFW_GAMEPAD_AXIS_RIGHT_Y;

        case GamepadAxis::LEFT_TRIGGER:
            return GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;

        case GamepadAxis::RIGHT_TRIGGER:
            return GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
    }

    assert(false && "[GLFWInputMapping] - Invalid GamepadAxis value.");
    std::abort();
}