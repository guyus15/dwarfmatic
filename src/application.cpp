#include "application.h"
#include "rendering/shader.h"
#include "rendering/model.h"
#include "resource_manager.h"

#include <stdexcept>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "utils/gl_debug.h"

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
    const Shader shader = ResourceManager::LoadShader("model_shader", "resources/shaders/model_vertex.glsl", "resources/shaders/model_fragment.glsl");
    shader.Use();

    Model wizard_model{};
    wizard_model.Load("resources/models/cube/cube.fbx");

    glEnable(GL_DEPTH_TEST);

    while (!m_window->ShouldClose())
    {
        glm::mat4 model{ 1.0f };
        model = glm::scale(model, glm::vec3{ 0.01f, 0.01f, 0.01f });
        model = glm::rotate(model, glm::radians(static_cast<float>(glfwGetTime()) * 10.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
        model = glm::translate(model, glm::vec3{ 0.0f, 0.0f, 0.0f });

        glm::mat4 view{ 1.0f };
        view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 10.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });

        glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        shader.SetMat4("model", model);
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        wizard_model.Draw(shader);

        glfwPollEvents();
        m_window->SwapBuffers();
    }
}

void Application::Dispose()
{
    glfwTerminate();
}