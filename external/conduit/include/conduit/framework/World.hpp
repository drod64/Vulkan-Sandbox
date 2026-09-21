#ifndef CONDUIT_WORLD_HPP
#define CONDUIT_WORLD_HPP
#include <entt/entt.hpp>
#include <conduit/core/primitives.hpp>

namespace conduit {
class World {
private:
    // &engine
    entt::registry          m_registry;
    // systems
    entt::dispatcher        m_events;
    // commandBuffer

public:
    World() = default;
    virtual ~World() = default;

    virtual void onEnter() = 0;
    virtual void update(real dt) = 0;
    virtual void onEnd() = 0;
}; // class World
} // namespace conduit

#endif // CONDUIT_WORLD_HPP