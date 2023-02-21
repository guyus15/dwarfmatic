#include "glfw_window.h"
#include "utils/profiling.h"

#include <stdexcept>

GlfwWindow::GlfwWindow(const std::string& title, const WindowDimensions& dimensions, const bool fullscreen)
{
    DFM_PROFILE_FUNCTION();

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
    DFM_PROFILE_FUNCTION();
    glfwDestroyWindow(m_window_ptr);
}

void GlfwWindow::SwapBuffers() const
{
    DFM_PROFILE_FUNCTION();
    glfwSwapBuffers(m_window_ptr);
}

void GlfwWindow::MakeContextCurrent() const
{
    DFM_PROFILE_FUNCTION();
    glfwMakeContextCurrent(m_window_ptr);
}

bool GlfwWindow::ShouldClose() const
{
    DFM_PROFILE_FUNCTION();
    return glfwWindowShouldClose(m_window_ptr);
}

WindowDimensions GlfwWindow::GetDimensions() const
{
    DFM_PROFILE_FUNCTION();
    WindowDimensions dimensions{};
    glfwGetWindowSize(m_window_ptr, &dimensions.width, &dimensions.height);
    return dimensions;
}
