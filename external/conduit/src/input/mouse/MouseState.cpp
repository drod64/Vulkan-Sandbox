#include <conduit/input/mouse/MouseState.hpp>

bool conduit::MouseState::isDown(MouseButton mouseButton) const
{
    sizet index = static_cast<sizet>(mouseButton);

    return m_current.test(index);
}

bool conduit::MouseState::wasPressed(MouseButton mouseButton) const
{
    sizet index = static_cast<sizet>(mouseButton);

    return !m_previous.test(index) && m_current.test(index);
}

bool conduit::MouseState::wasReleased(MouseButton mouseButton) const
{
    sizet index = static_cast<sizet>(mouseButton);

    return m_previous.test(index) && !m_current.test(index);
}

sm::Vec2 conduit::MouseState::position() const
{
    return m_position;
}

sm::Vec2 conduit::MouseState::delta() const
{
    return m_delta;
}

sm::Vec2 conduit::MouseState::wheel() const
{
    return m_wheel;
}

void conduit::MouseState::reset()
{
    m_current.reset();
    m_previous.reset();
    m_position = {static_cast<real>(0), static_cast<real>(0)};
    m_delta = {static_cast<real>(0), static_cast<real>(0)};
    m_wheel = {static_cast<real>(0), static_cast<real>(0)};
}

void conduit::MouseState::setButton(MouseButton mouseButton, bool state)
{
    sizet index = static_cast<sizet>(mouseButton);

    m_current.set(index, state);
}

void conduit::MouseState::updatePosition(sm::Vec2 position)
{
    m_position = position;
}

void conduit::MouseState::updateDelta(sm::Vec2 delta)
{
    m_delta = delta;
}

void conduit::MouseState::updateWheel(sm::Vec2 wheel)
{
    m_wheel = wheel;
}

void conduit::MouseState::updatePrevious()
{
    m_previous = m_current;
}