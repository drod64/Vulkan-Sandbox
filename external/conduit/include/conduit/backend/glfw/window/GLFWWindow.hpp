#ifndef CONDUIT_GLFW_WINDOW_HPP
#define CONDUIT_GLFW_WINDOW_HPP
#include <cassert>
#include <glfw/glfw3.h>
#include <conduit/core/primitives.hpp>

namespace conduit::glfw::window {
class GLFWWindow {
private:
    GLFWwindow *m_glfw_window = nullptr;

public:
    /**
     * Parameterized constructor.
     * 
     * @param width the width of the window
     * @param height the height of the window
     * @param title the title of the window
     */
    GLFWWindow(uint32 width, uint32 height, const char *title);

    /**
     * Destructor.
     */
    ~GLFWWindow();

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

    /**
     * Backend special function necessary for other backend systems (input).
     * 
     * @return the native handle of the this class
     */
    GLFWwindow* nativeHandle() const;
}; // class GLFWWindow
} // namespace conduit::glfw::window

#endif // CONDUIT_GLFW_WINDOW_HPP