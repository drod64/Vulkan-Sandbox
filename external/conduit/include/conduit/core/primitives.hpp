#ifndef CONDUIT_PRIMITIVES_HPP
#define CONDUIT_PRIMITIVES_HPP
#include <entt/entt.hpp>
#include <cstdint>
#include <conduit/core/config.hpp>

namespace conduit {
    using real = config::precision_type;

    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;
    using sizet = std::size_t;

    using entity = entt::entity;
    constexpr entity null_entity = entt::null;

} // namespace conduit

#endif // CONDUIT_PRIMITIVES_HPP