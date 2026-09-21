#ifndef CONDUIT_VULKAN_TESTER_HPP
#define CONDUIT_VULKAN_TESTER_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
class VulkanTester {
private:
    void initialize();
    void shutdown();

public:
    static constexpr uint32 WIDTH = 800;
    static constexpr uint32 HEIGHT = 600;

    VulkanTester();
    ~VulkanTester();

    void run();
}; // class VulkanTester
} // namespace conduit

#endif // CONDUIT_VULKAN_TESTER_HPP