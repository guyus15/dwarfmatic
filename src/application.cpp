#include "application.h"

#include <stdexcept>

Application::Application()
{
    Initialise();
}

Application::~Application()
{
    Dispose();
}

void Application::Initialise()
{
    // Initialise GLFW.
    if (!glfwInit())
    {
        throw std::runtime_error{ "Failed to initialise GLFW." };
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = std::make_shared<GlfwWindow>("Dwarfmatic");
    m_window->MakeContextCurrent();

    // Initialise GLAD.
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error{ "Failed to initialise GLAD." };
    }

    const auto [width, height] = m_window->GetDimensions();
    glViewport(0, 0, width, height);
}

void Application::Run() const
{
    while (!m_window->ShouldClose())
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        m_window->SwapBuffers();
    }
}

void Application::Dispose()
{
    glfwTerminate();
}