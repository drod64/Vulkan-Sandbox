#ifndef CONDUIT_WINDOW_HPP
#define CONDUIT_WINDOW_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/backend/Platform.hpp>

namespace conduit {
/**
 * Forward of Input class.
 */
class Input;

/**
 * This class is the engine facing window API.
 * Essentially, it acts as a contract that other backend window implementations will have to follow in order
 * to be cleanly compatible with Conduit's pipeline.
 * 
 * Besides needing to implement the below public functions, backend implementation windows will also need to
 * have a public "nativehandle()" as Conduit's other subsystems like Input depend on it.
 */
class Window {
private:
    friend class Input;
    platform::Window m_platform_window;

public:
    /**
     * Parameterized constructor.
     * 
     * @param width the width of the window
     * @param height the height of the window
     * @param title the title of the window
     */
    Window(uint32 width, uint32 height, const char *title);

    ~Window() = default;

    /**
     * @return true if the window should close, false otherwise
     */
    bool shouldClose() const;

    /**
     * Closes the window.
     */
    void close();

    /**
     * Polls events of the window.
     */
    void pollEvents();

    /**
    * Swaps buffers of the window.
    */
    void swapBuffers();

    /**
     * @return the current width of the window
     */
    uint32 width() const;

    /**
     * @return the current height of the window
     */
    uint32 height() const;

    /**
     * Sets the title of the window.
     * 
     * @param title the new title
     */
    void setTitle(const char *title);

    /**
     * @return true if the window is focused, false otherwise
     */
    bool isFocused() const;

    /**
     * @return true if the window is minimized, false otherwsie
     */
    bool isMinimized() const;
}; // class Window
} // namespace conduit

#endif // CONDUIT_WINDOW_HPP