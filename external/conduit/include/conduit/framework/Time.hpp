#ifndef CONDUIT_TIME_HPP
#define CONDUIT_TIME_HPP
#include <chrono>
#include <conduit/core/primitives.hpp>

namespace conduit {
class Time {
private:
    using clock = std::chrono::steady_clock;

    clock::time_point   m_previos{};
    real                m_delta{};
    real                m_elapsed{};
    uint64              m_frameCount{};

public:
    Time() = default;
    ~Time() = default;

    void tick();
    real delta() const;
    real elapsed() const;
    uint64 frameCount() const;
}; // class Time
} // namespace conduit

#endif // CONDUIT_TIME_HPP