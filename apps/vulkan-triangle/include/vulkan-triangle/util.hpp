#ifndef VULKAN_TRIANGLE_UTIL_HPP
#define VULKAN_TRIANGLE_UTIL_HPP
#include <conduit/core/containers/vector.hpp>
#include <conduit/core/containers/string.hpp>

namespace vtapp::util {
    /**
     * Reads a file in binary format.
     * 
     * @param fileSource the source path to the file
     */
    [[nodiscard]] conduit::vector<char> readFile(const conduit::string &fileSource);
} // namespace vtapp

#endif // VULKAN_TRIANGLE_UTIL_HPP