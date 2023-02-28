/**
 * \file scene.h
 */

#ifndef SCENE_H
#define SCENE_H

#include "entt/entity/registry.hpp"

#include <string>

class Entity;

class Scene
{
public:
    Scene() = default;

    /**
     * \brief Updates the scene using the given delta time.
     * \param dt The delta time.
     */
    void Update(double dt);

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

    friend class Entity;
};

#endif // SCENE_H