/**
 * \file glfw_window.cpp
 */

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

/**
 * \brief Swaps the front and back buffers of the window.
 */
void GlfwWindow::SwapBuffers() const
{
    DFM_PROFILE_FUNCTION();
    glfwSwapBuffers(m_window_ptr);
}

/**
 * \brief Makes this window be the current context.
 */
void GlfwWindow::MakeContextCurrent() const
{
    DFM_PROFILE_FUNCTION();
    glfwMakeContextCurrent(m_window_ptr);
}

/**
 * \brief Determines whether the window should be closed.
 * \return A boolean value indicating if the window should be closed.
 */
bool GlfwWindow::ShouldClose() const
{
    DFM_PROFILE_FUNCTION();
    return glfwWindowShouldClose(m_window_ptr);
}

/**
 * \brief Gets the dimensions of the window.
 * \return A \code WindowDimensions object representing the dimensions of the window.
 */
WindowDimensions GlfwWindow::GetDimensions() const
{
    DFM_PROFILE_FUNCTION();
    WindowDimensions dimensions{};
    glfwGetWindowSize(m_window_ptr, &dimensions.width, &dimensions.height);
    return dimensions;
}
