/**
 * application.cpp
 */

#include "application.h"
#include "resource_manager.h"
#include "ubo.h"
#include "scene.h"

#include "rendering/camera.h"
#include "rendering/camera_manager.h"
#include "rendering/model.h"
#include "rendering/lighting.h"
#include "rendering/shader.h"

#include "ecs/entity.h"

#include "utils/logging.h"
#include "utils/profiling.h"

#include <stdexcept>

#include "ecs/systems/lighting_system.h"
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

    Scene scene;

    Entity cube_object = scene.CreateEntity("Cube 1");
    cube_object.AddComponent<MeshComponent>(cube_model);
    cube_object.AddComponent<ShaderComponent>(shader);
    auto& cube_object_transform = cube_object.GetComponent<TransformComponent>();
    cube_object_transform.position = { -1.5f, 0.0f, 0.0f };

    Entity cube_object2 = scene.CreateEntity("Cube 2");
    cube_object2.AddComponent<MeshComponent>(cube_model);
    cube_object2.AddComponent<ShaderComponent>(shader);
    auto& cube_object2_transform = cube_object2.GetComponent<TransformComponent>();
    cube_object2_transform.position = { 0.0f, 0.0f, 5.0f };

    Entity ball_object = scene.CreateEntity("Ball 1");
    ball_object.AddComponent<MeshComponent>(ball_model);
    ball_object.AddComponent<ShaderComponent>(shader);
    auto& ball_object_transform = ball_object.GetComponent<TransformComponent>();
    ball_object_transform.position = { 1.5f, 0.0f, 0.0f };

#define POINT_LIGHT 1
#define DIRECTIONAL_LIGHT 0
#define SPOT_LIGHT 0

#if POINT_LIGHT
    Entity point_light_object = scene.CreateEntity("Point Light");
    point_light_object.AddComponent<MeshComponent>(cube_model);
    point_light_object.AddComponent<ShaderComponent>(shader);
    auto& point_light_component = point_light_object.AddComponent<LightComponent>();
    point_light_component.type = LightComponent::Type::Point;
    point_light_component.constant = 1.0f;
    point_light_component.linear = 0.14f;
    point_light_component.quadratic = 0.07f;
    point_light_component.ambient = { 0.3f, 0.3f, 0.3f };
    point_light_component.diffuse = { 0.8f, 0.8f, 0.8f };
    point_light_component.specular = { 1.0f, 1.0f, 1.0f };
    auto& point_light_object_transform = point_light_object.GetComponent<TransformComponent>();
    point_light_object_transform.position = { 0.0f, 0.0f, -3.0f };
    point_light_object_transform.scale = { 0.1f, 0.1f, 0.1f };
#endif

#if DIRECTIONAL_LIGHT
    Entity directional_light_object = scene.CreateEntity("Directional Light");
    auto& directional_light_component = directional_light_object.AddComponent<LightComponent>();
    directional_light_component.type = LightComponent::Type::Directional;
    directional_light_component.ambient = { 0.1f, 0.1f, 0.1f };
    directional_light_component.diffuse = { 0.3f, 0.3f, 0.3f };
    directional_light_component.specular = { 0.2f, 0.2f, 0.2f };
    auto& directional_light_transform = directional_light_object.GetComponent<TransformComponent>();
    directional_light_transform.rotation = { 0.0f, 45.0f, 0.0f };
#endif

#if SPOT_LIGHT
    Entity spot_light_object = scene.CreateEntity("Spot Light");
    spot_light_object.AddComponent<MeshComponent>(cube_model);
    spot_light_object.AddComponent<ShaderComponent>(shader);
    auto& spot_light_component = spot_light_object.AddComponent<LightComponent>();
    spot_light_component.type = LightComponent::Type::Spot;
    spot_light_component.constant = 1.0f;
    spot_light_component.linear = 0.14f;
    spot_light_component.quadratic = 0.07f;
    spot_light_component.inner_angle = 20.0f;
    spot_light_component.outer_angle = 25.0f;
    spot_light_component.ambient = { 0.3f, 0.3f, 0.3f };
    spot_light_component.diffuse = { 0.8f, 0.8f, 0.8f };
    spot_light_component.specular = { 1.0f, 1.0f, 1.0f };
    auto& spot_light_object_transform = spot_light_object.GetComponent<TransformComponent>();
    spot_light_object_transform.position = { 0.0f, 0.0f, -5.0f };
    spot_light_object_transform.rotation = { 0.0f, 0.0f, 0.0f };
    spot_light_object_transform.scale = { 0.1f, 0.1f, 0.1f };
#endif

    glEnable(GL_DEPTH_TEST);

    while (!m_window->ShouldClose())
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: Calculate the actual delta time and pass this as a parameter.
        scene.Update(0.1);

        // Update entities
        cube_object_transform.rotation = { 0.0f, static_cast<float>(glfwGetTime()) * 10.0f, 0.0f };
        point_light_object_transform.position = { sin(static_cast<float>(glfwGetTime())) * 5.0f, 0.0f, cos(static_cast<float>(glfwGetTime())) * 5.0f };
        scene.UpdateLightSources(LightUpdateType::All);

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