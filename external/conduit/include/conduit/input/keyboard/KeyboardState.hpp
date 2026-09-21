#ifndef CONDUIT_KEYBOARD_STATE_HPP
#define CONDUIT_KEYBOARD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/input/keyboard/Key.hpp>
#include <conduit/core/containers/bitset.hpp>

namespace conduit {
/**
 * State tracker of the polled keyboard.
 */
class KeyboardState {
private:
    bitset<static_cast<sizet>(Key::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(Key::MAX_COUNT)> m_previous{};

public:
    KeyboardState() = default;
    ~KeyboardState() = default;

    /**
     * @param key the key to check
     * 
     * @return true if the key is down, false otherwise
     */
    bool isDown(Key key) const;

    /**
     * @param key the key to check
     * 
     * @return true if the key was pressed, false otherwise
     */
    bool wasPressed(Key key) const;
    
    /**
     * @param key the key to check
     * 
     * @return true if the key was released, false otherwise
     */
    
    bool wasReleased(Key key) const;
    
    /**
     * Resets the state of the keyboard.
     */
    void reset();

    /**
     * Sets a key to on/off.
     * 
     * @param key the key to set
     * @param state the state of the key
     */
    void setKey(Key key, bool state);

    /**
     * Updates the previous state of the keyboard.
     * This is essential for the wasPressed()/wasReleased() operations.
     */
    void updatePrevious();
}; // class KeyboardState
} // namespace conduit

#endif // CONDUIT_KEYBOARD_STATE_HPP