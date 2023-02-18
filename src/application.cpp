#include "application.h"
#include "resource_manager.h"
#include "ubo.h"
#include "rendering/camera.h"
#include "rendering/camera_manager.h"
#include "rendering/model.h"
#include "rendering/point_light.h"
#include "rendering/shader.h"
#include "utils/logging.h"

#include <stdexcept>

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    // Initialise logging
    Logging::Initialise();

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

    // Load shaders
    const Shader shader = ResourceManager::LoadShader("model_shader", "resources/shaders/model_vertex.glsl", "resources/shaders/model_fragment.glsl");

    // Create UBOs
    Ubo matrices_ubo;
    matrices_ubo.Configure("Matrices", 2 * sizeof(glm::mat4));
    matrices_ubo.BindShaderBlock(shader);
    matrices_ubo.Create();
    UboManager::Register("matrices", matrices_ubo);

    Ubo lighting_ubo;
    lighting_ubo.Configure("Lighting", sizeof(int) + sizeof(PointLightData) * 128 + sizeof(glm::vec3) * 5);
    lighting_ubo.BindShaderBlock(shader);
    lighting_ubo.Create();
    UboManager::Register("lighting", lighting_ubo);

    // Initialise Cameras
    CameraManager::Initialise();

    DFM_CORE_INFO("Application initialised");
}

void Application::Run() const
{
    const Shader shader = ResourceManager::GetShader("model_shader");
    shader.Use();

    Model cube_model{};
    cube_model.Load("resources/models/cube/cube.fbx");

    Camera camera{ { 0.0f, 0.0f, 7.0f }, { 0.0f, 0.0f, 0.0f } };

    PointLightData light_data{};
    light_data.position = { 0.0f, 0.0f, 2.0f };
    light_data.constant = 1.0f;
    light_data.linear = 0.35f;
    light_data.quadratic = 0.44f;
    light_data.ambient = { 1.0f, 1.0f, 1.0f };
    light_data.diffuse = { 1.0f, 1.0f, 1.0f };
    light_data.specular = { 1.0f, 1.0f, 1.0f };
    PointLight light{ light_data };

    // TODO: Look at why multiple lights arent working

    glEnable(GL_DEPTH_TEST);

    while (!m_window->ShouldClose())
    {
        glm::mat4 model{ 1.0f };
        model = glm::rotate(model, glm::radians(-static_cast<float>(glfwGetTime()) * 10.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });

        shader.SetMat4("model", model);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube_model.Draw(shader);

        glfwPollEvents();
        m_window->SwapBuffers();
    }
}

void Application::Dispose()
{
    glfwTerminate();
}