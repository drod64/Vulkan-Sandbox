#ifndef VT_APP_APP_HPP
#define VT_APP_APP_HPP
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <exception>
#include <vulkan/vulkan_raii.hpp>
#include <conduit/core/primitives.hpp>

namespace vtapp {
class App {
private:
    vk::raii::Context m_context;
    vk::raii::Instance m_instance = nullptr;

    /**
     * Starts up the application.
     */
    void initialize();

    /**
     * Creates the vulkan instance.
     */
    void createVkInstance();

    /**
     * Shuts down the application and cleans up any resources used during its lifetime.
     */
    void shutdown();

public:
    static constexpr conduit::uint32 WIDTH = 800;
    static constexpr conduit::uint32 HEIGHT = 600;

    /**
     * Default constructor.
     */
    App();

    /**
     * Destructor.
     */
    ~App();

    /**
     * Runs the Vulkan-Triangle app.
     */
    void run();
}; // class App
} // namespace vtapp

#endif // VT_APP_APP_HPP