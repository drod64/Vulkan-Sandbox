#include <conduit/input/keyboard/KeyboardState.hpp>

bool conduit::KeyboardState::isDown(Key key) const
{
    sizet index = static_cast<sizet>(key);

    return m_current.test(index);
}

bool conduit::KeyboardState::wasPressed(Key key) const
{
    sizet index = static_cast<sizet>(key);

    return !m_previous.test(index) && m_current.test(index);
}

bool conduit::KeyboardState::wasReleased(Key key) const
{
    sizet index = static_cast<sizet>(key);
    
    return m_previous.test(index) && !m_current.test(index);
}

void conduit::KeyboardState::reset()
{
    m_current.reset();
    m_previous.reset();
}

void conduit::KeyboardState::setKey(Key key, bool state)
{
    sizet index = static_cast<sizet>(key);

    m_current.set(index, state);
}

void conduit::KeyboardState::updatePrevious()
{
    m_previous = m_current;
}