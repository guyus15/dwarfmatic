/**
 * \file scene.cpp
 */

#include "scene.h"

#include "ecs/entity.h"
#include "ecs/components.h"
#include "ecs/system_manager.h"
#include "ecs/systems/rendering_system.h"
#include "ecs/systems/lighting_system.h"

#include "utils/profiling.h"

Scene::Scene()
{
    m_system_manager.RegisterSystem<RenderingSystem>(this);
    m_system_manager.RegisterSystem<LightingSystem>(this);
}

Scene::~Scene()
{
    m_system_manager.RemoveSystem<RenderingSystem>();
    m_system_manager.RemoveSystem<LightingSystem>();
}

/**
 * \brief Updates the scene using the given delta time.
 * \param dt The delta time.
 */
void Scene::Update(const double dt)
{
    DFM_PROFILE_FUNCTION();

    m_system_manager.Update(dt);
}

/**
 * \brief Updates the given type of light sources within the scene via the lighting system.
 * \param update_type The type of light source to update.
 */
void Scene::UpdateLightSources(const LightUpdateType update_type)
{
    try
    {
        auto& lighting_system = m_system_manager.GetSystem<LightingSystem>();
        lighting_system.UpdateLightSources(update_type);
    }
    catch (std::out_of_range& e)
    {
        DFM_CORE_ERROR("{0}", e.what());
    }
}

/**
 * \brief Creates an entity in the scene with the given name and returns a copy.
 * \param name The name of the entity.
 * \return A copy of the entity.
 */
Entity Scene::CreateEntity(const std::string& name)
{
    DFM_PROFILE_FUNCTION();

    Entity entity{ m_registry.create(), this };
    entity.AddComponent<IdComponent>();
    auto& [tag_name] = entity.AddComponent<TagComponent>();
    tag_name = name;
    auto& [position, rotation, scale] = entity.AddComponent<TransformComponent>();
    position = { 0.0f, 0.0f, 0.0f };
    rotation = { 0.0f, 0.0f, 0.0f };
    scale = { 1.0f, 1.0f, 1.0f };

    return entity;
}

/**
 * \brief Destroys the given entity from the scene.
 * \param entity The entity to destroy.
 */
void Scene::DestroyEntity(Entity& entity)
{
    DFM_PROFILE_FUNCTION();

    m_registry.destroy(entity.GetHandle());
    entity.Destroy();
}