#ifndef CONDUIT_KEY_HPP
#define CONDUIT_KEY_HPP

namespace conduit {
/**
 * Keys supported by Conduit.
 * These ideally should be valued from 0 - N.
 */
enum class Key {
    // Letters
    A = 0, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    // Numbers
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4,
    NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,

    // Function Keys.
    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,

    // Modifiers
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_CONTROL,
    RIGHT_CONTROL,
    LEFT_ALT,
    RIGHT_ALT,
    LEFT_SUPER,
    RIGHT_SUPER,

    // Navigation
    UP,
    DOWN,
    RIGHT,
    LEFT,

    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,

    INSERT,
    DELETE,

    // Editing / Whitespace
    BACKSPACE,
    ENTER,
    TAB,
    ESCAPE,
    SPACE,

    // Punctuation / symbols
    APOSTOPHRE,
    COMMA,
    MINUS,
    PERIOD,
    SLASH,
    SEMICOLON,
    EQUAL,

    LEFT_BRACKET,
    BACKSLASH,
    RIGHT_BRACKET,
    GRAVE,

    // Keypad
    KP_0, KP_1, KP_2, KP_3, KP_4,
    KP_5, KP_6, KP_7, KP_8, KP_9,

    KP_DECIMAL,
    KP_DIVIDE,
    KP_MULTIPLY,
    KP_SUBTRACT,
    KP_ADD,
    KP_ENTER,

    // Lock / system
    CAPS_LOCK,
    NUM_LOCK,
    SCROLL_LOCK,
    PRINT_SCREEN,
    PAUSE,

    // Menu
    MENU,

    MAX_COUNT
}; // enum class Key
} // namespace conduit

#endif // CONDUIT_KEY_HPP