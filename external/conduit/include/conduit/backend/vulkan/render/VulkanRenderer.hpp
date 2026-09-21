#ifndef CONDUIT_VULKAN_RENDERER_HPP
#define CONDUIT_VULKAN_RENDERER_HPP
#include <vulkan/vulkan.hpp>

namespace conduit::vulkan {
class VulkanRenderer {
public:
    VkInstance vulkan_instance;
}; // class VulkanRenderer
} // namespace conduit::vulkan

#endif // CONDUIT_VULKAN_RENDERER_HPP