/**
 * \file glfw_window.h
 */

#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "GLFW/glfw3.h"

#include <string>

/**
 * \brief Represents the dimensions of a window.
 */
struct WindowDimensions
{
    int width, height;
};

constexpr WindowDimensions DEFAULT_DIMENSIONS{ 800, 600 };

/**
 * \brief A wrapper for a GLFW window.
 */
class GlfwWindow
{
public:
    explicit GlfwWindow(const std::string& title, const WindowDimensions& dimensions = DEFAULT_DIMENSIONS, bool fullscreen = false);
    ~GlfwWindow();

    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow(GlfwWindow&&) noexcept = default;

    GlfwWindow& operator=(const GlfwWindow&) = delete;
    GlfwWindow& operator=(GlfwWindow&&) = delete;

    /**
     * \brief Swaps the front and back buffers of the window.
     */
    void SwapBuffers() const;

    /**
     * \brief Makes this window be the current context.
     */
    void MakeContextCurrent() const;

    /**
     * \brief Determines whether the window should be closed.
     * \return A boolean value indicating if the window should be closed.
     */
    [[nodiscard]] bool ShouldClose() const;

    /**
     * \brief Gets the dimensions of the window.
     * \return A \code WindowDimensions object representing the dimensions of the window.
     */
    [[nodiscard]] WindowDimensions GetDimensions() const;

private:
    GLFWwindow* m_window_ptr;
};

#endif // GLFW_WINDOW_H
