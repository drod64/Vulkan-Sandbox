#ifndef VULKAN_TRIANGLE_UTIL_HPP
#define VULKAN_TRIANGLE_UTIL_HPP
#include <conduit/core/containers/vector.hpp>
#include <conduit/core/containers/string.hpp>

namespace vtapp {
    /**
     * Reads a file in binary format.
     */
    [[nodiscard]] conduit::vector<char> readFile(const conduit::string &fileName);
} // namespace vtapp

#endif // VULKAN_TRIANGLE_UTIL_HPP