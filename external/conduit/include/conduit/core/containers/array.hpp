#ifndef CONDUIT_ARRAY_HPP
#define CONDUIT_ARRAY_HPP
#include <array>

namespace conduit {
    template <typename T, std::size_t Size>
    using array = std::array<T, Size>;
} // namespace conduit

#endif // CONDUIT_ARRAY_HPP