#ifndef CONDUIT_VARIANT_HPP
#define CONDUIT_VARIANT_HPP
#include <variant>

namespace conduit {
    template <typename... Types>
    using variant = std::variant<Types...>;
} // namespace conduit

#endif // CONDUIT_VARIANT_HPP