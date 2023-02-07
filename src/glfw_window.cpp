#include "glfw_window.h"

#include <stdexcept>

GlfwWindow::GlfwWindow(const std::string& title, const WindowDimensions& dimensions, const bool fullscreen)
{
    m_window_ptr = glfwCreateWindow(
        dimensions.width,
        dimensions.height,
        title.c_str(),
        fullscreen ? glfwGetPrimaryMonitor() : nullptr,
        nullptr
    );

    if (!m_window_ptr)
    {
        throw std::runtime_error{ "Failed to create GLFW window." };
    }
}

GlfwWindow::~GlfwWindow()
{
    glfwDestroyWindow(m_window_ptr);
}

void GlfwWindow::SwapBuffers() const
{
    glfwSwapBuffers(m_window_ptr);
}

void GlfwWindow::MakeContextCurrent() const
{
    glfwMakeContextCurrent(m_window_ptr);
}

bool GlfwWindow::ShouldClose() const
{
    return glfwWindowShouldClose(m_window_ptr);
}

WindowDimensions GlfwWindow::GetDimensions() const
{
    WindowDimensions dimensions{};
    glfwGetWindowSize(m_window_ptr, &dimensions.width, &dimensions.height);
    return dimensions;
}
