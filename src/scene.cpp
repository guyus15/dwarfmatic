#include "scene.h"

#include "ecs/entity.h"
#include "ecs/components.h"

#include "utils/profiling.h"

void Scene::Update(double dt)
{
    DFM_PROFILE_FUNCTION();
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