/**
 * \file scene.h
 */

#ifndef SCENE_H
#define SCENE_H

#include "ecs/system_manager.h"

#include "entt/entity/registry.hpp"

#include <string>

enum class LightUpdateType;
class Entity;

/**
 * \brief Represents a game scene used to manage currently existing entities.
 */
class Scene
{
public:
    Scene();
    ~Scene();

    Scene(const Scene&) = delete;
    Scene(Scene&&) noexcept = default;

    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) noexcept = default;

    /**
     * \brief Updates the scene using the given delta time.
     * \param dt The delta time.
     */
    void Update(double dt);

    /**
     * \brief Updates the given type of light sources within the scene via the lighting system.
     * \param update_type The type of light source to update.
     */
    void UpdateLightSources(LightUpdateType update_type);

    /**
     * \brief Creates an entity in the scene with the given name and returns a copy.
     * \param name The name of the entity.
     * \return A copy of the entity.
     */
    Entity CreateEntity(const std::string& name = "Game Object");

    /**
     * \brief Destroys the given entity from the scene.
     * \param entity The entity to destroy.
     */
    void DestroyEntity(Entity& entity);

private:
    entt::registry m_registry;
    SystemManager m_system_manager;

    friend class Entity;
    friend class RenderingSystem;
    friend class LightingSystem;
};

#endif // SCENE_H