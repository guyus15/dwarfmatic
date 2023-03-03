/**
 * application.cpp
 */

#include "application.h"
#include "resource_manager.h"
#include "ubo.h"
#include "rendering/camera.h"
#include "rendering/camera_manager.h"
#include "rendering/model.h"
#include "rendering/lighting.h"
#include "rendering/shader.h"
#include "utils/logging.h"
#include "utils/profiling.h"

#include <stdexcept>

#include "scene.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Application::Application()
{
    DFM_PROFILE_BEGIN_SESSION("Dwarfmatic");
    Initialise();
}

Application::~Application()
{
    Dispose();
    DFM_PROFILE_END_SESSION();
}

/**
 * \brief Performs application initialisation.
 */
void Application::Initialise()
{
    DFM_PROFILE_FUNCTION();

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
    lighting_ubo.Configure("Lighting", sizeof(Lighting));
    lighting_ubo.BindShaderBlock(shader);
    lighting_ubo.Create();
    UboManager::Register("lighting", lighting_ubo);

    // Initialise Cameras
    CameraManager::Initialise();

    DFM_CORE_INFO("Application initialised.");
}

/**
 * \brief Runs the application.
 */
void Application::Run() const
{
    DFM_PROFILE_FUNCTION();

    const Shader shader = ResourceManager::GetShader("model_shader");
    shader.Use();

    Model cube_model{};
    cube_model.Load("resources/models/cube/cube.fbx");

    Model ball_model{};
    ball_model.Load("resources/models/ball/ball.fbx");

    Camera camera{ { 0.0f, 0.0f, 7.0f }, { 0.0f, 0.0f, 0.0f } };

    PointLightData light_data{};
    light_data.position = { -0.5f, 0.0f, 2.0f, 0.0f };
    light_data.constant = 1.0f;
    light_data.linear = 0.14f;
    light_data.quadratic = 0.07f;
    light_data.ambient = { 0.3f, 0.3f, 0.3f, 0.0f };
    light_data.diffuse = { 0.8f, 0.8f, 0.8f, 0.0f, };
    light_data.specular = { 1.0f, 1.0f, 1.0f, 0.0f };
    PointLight light{ light_data };

    DirectionalLightData d_light_data{};
    d_light_data.direction = { 3.0f, 0.0f, 1.0f, 0.0f };
    d_light_data.ambient = { 0.1f, 0.1f, 0.1f, 0.0f };
    d_light_data.diffuse = { 0.3f, 0.3f, 0.3f, 0.0f };
    d_light_data.specular = { 0.2f, 0.2f, 0.2f, 0.0f, };
    DirectionalLight directional_light{ d_light_data };

    SpotLightData s_light_data{};
    s_light_data.position = { 0.0f, 0.0f, 5.0f, 0.0f };
    s_light_data.direction = { 0.0f, 0.0f, 1.0f, 0.0f };
    s_light_data.constant = 1.0f;
    s_light_data.linear = 0.14f;
    s_light_data.quadratic = 0.07f;
    s_light_data.inner_cut_off = glm::cos(glm::radians(20.0f));
    s_light_data.outer_cut_off = glm::cos(glm::radians(25.0f));
    s_light_data.ambient = { 0.3f, 0.3f, 0.3f, 0.0f };
    s_light_data.diffuse = { 0.8f, 0.8f, 0.8f, 0.0f, };
    s_light_data.specular = { 1.0f, 1.0f, 1.0f, 0.0f };
    SpotLight spot_light{ s_light_data };

    Scene scene;

    glEnable(GL_DEPTH_TEST);

    while (!m_window->ShouldClose())
    {
        // TODO: Calculate the actual delta time and pass this as a parameter.
        scene.Update(0.1);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{ 1.0f };
        model = glm::translate(model, glm::vec3{ -1.5f, 0.0f, 0.0f });
        model = glm::rotate(model, glm::radians(-static_cast<float>(glfwGetTime()) * 10.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
        shader.SetMat4("model", model);
        cube_model.Draw(shader);

        model = glm::mat4{ 1.0f };
        model = glm::translate(model, glm::vec3{ 0.0f, 0.0f, -5.0f });
        model = glm::rotate(model, glm::radians(-static_cast<float>(glfwGetTime()) * 15.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
        shader.SetMat4("model", model);
        cube_model.Draw(shader);

        model = glm::mat4{ 1.0f };
        model = model = glm::translate(model, glm::vec3{ 1.5f, 0.0f, 0.0f });
        model = glm::rotate(model, glm::radians(-static_cast<float>(glfwGetTime()) * 10.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
        shader.SetMat4("model", model);
        ball_model.Draw(shader);

        glfwPollEvents();
        m_window->SwapBuffers();
    }
}

/**
 * \brief Performs a cleanup before application is shut down.
 */
void Application::Dispose()
{
    DFM_PROFILE_FUNCTION();
    glfwTerminate();
}