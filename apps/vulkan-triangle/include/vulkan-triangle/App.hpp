#ifndef VT_APP_APP_HPP
#define VT_APP_APP_HPP
#define NULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
#include <conduit/core/primitives.hpp>

namespace vtapp {
class App {
private:
    void initialize();
    void shutdown();

public:
    static constexpr conduit::uint32 WIDTH = 800;
    static constexpr conduit::uint32 HEIGHT = 600;

    App();
    ~App();

    void run();
}; // class App
} // namespace vtapp

#endif // VT_APP_APP_HPP