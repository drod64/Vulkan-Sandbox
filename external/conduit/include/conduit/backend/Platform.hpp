#ifndef CONDUIT_PLATFORM_HPP
#define CONDUIT_PLATFORM_HPP
#include <conduit/core/config.hpp>

#if CONDUIT_PLATFORM_BACKEND_GLFW
    #include <conduit/backend/glfw/platform/GLFWPlatform.hpp>
    namespace conduit {
        namespace platform = glfw;
    } // namespace conduit

#else

    #error "No supported platform backend selected."

#endif

#endif // CONDUIT_PLATFORM_HPP