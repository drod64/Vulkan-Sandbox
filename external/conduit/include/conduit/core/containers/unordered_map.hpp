#ifndef CONDUIT_UNORDERED_MAP_HPP
#define CONDUIT_UNORDERED_MAP_HPP
#include <unordered_map>

namespace conduit
{
    template<
        typename Key,
        typename T,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>,
        typename Allocator = std::allocator<std::pair<const Key, T>>
    >
    using unordered_map = std::unordered_map<Key, T, Hash, Pred, Allocator>;
}

#endif // CONDUIT_UNORDERED_MAP_HPP