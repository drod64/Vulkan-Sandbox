#ifndef CONDUIT_BITSET_HPP
#define CONDUIT_BITSET_HPP
#include <bitset>

namespace conduit {
    template <std::size_t Size>
    using bitset = std::bitset<Size>;
} // namespace conduit

#endif // CONDUIT_BITSET_HPP