#include <conduit/framework/Time.hpp>

void conduit::Time::tick()
{   
    // Get current time.
    const auto now = clock::now();

    // Get time passed since last frame.
    m_delta = std::chrono::duration<real>(now - m_previos).count();

    // Update previous.
    m_previos = now;

    // Update elapsed time.
    m_elapsed += m_delta;

    // Update frame count.
    ++m_frameCount;
}

conduit::real conduit::Time::delta() const
{
    return m_delta;
}

conduit::real conduit::Time::elapsed() const
{
    return m_elapsed;
}

conduit::uint64 conduit::Time::frameCount() const
{
    return m_frameCount;
}