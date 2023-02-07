#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "GLFW/glfw3.h"

#include <string>

struct WindowDimensions
{
    int width, height;
};

constexpr WindowDimensions DEFAULT_DIMENSIONS{ 800, 600 };

class GlfwWindow
{
public:
    explicit GlfwWindow(const std::string& title, const WindowDimensions& dimensions = DEFAULT_DIMENSIONS, bool fullscreen = false);
    ~GlfwWindow();

    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow(GlfwWindow&&) noexcept = default;

    GlfwWindow& operator=(const GlfwWindow&) = delete;
    GlfwWindow& operator=(GlfwWindow&&) = delete;

    void SwapBuffers() const;
    void MakeContextCurrent() const;

    [[nodiscard]] bool ShouldClose() const;
    [[nodiscard]] WindowDimensions GetDimensions() const;

private:
    GLFWwindow* m_window_ptr;
};

#endif // GLFW_WINDOW_H
