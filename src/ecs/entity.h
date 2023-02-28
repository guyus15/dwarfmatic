/**
 * \file entity.h
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"

#include "utils/assertion.h"
#include "utils/profiling.h"

/**
 * \brief A wrapper for an Entt entity.
 */
class Entity
{
public:
    Entity(const entt::entity handle, Scene* scene)
        : m_handle{ handle }, m_scene{ scene }, m_destroyed{ false }
    {
    }

    /**
     * \brief Adds a component to the entity.
     * \tparam T The type of component to add.
     * \tparam Args The types of parameters to be passed to the T constructor.
     * \param args The parameters to be passed to the T constructor.
     * \return A reference to the entity component.
     */
    template <typename T, typename... Args>
    T& AddComponent(Args... args)
    {
        DFM_PROFILE_FUNCTION();
        DFM_ASSERT(m_destroyed, "Trying to add component to a destroyed entity.");
        return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
    }

    /**
     * \brief Gets a component of the given type from the entity.
     * \tparam T The type of component to get.
     * \return A reference to the entity component.
     */
    template <typename T>
    T& GetComponent()
    {
        DFM_PROFILE_FUNCTION();
        DFM_ASSERT(m_destroyed, "Trying to get component from a destroyed entity.");
        return m_scene->m_registry.get<T>(m_handle);
    }

    /**
     * \brief Removes a component of the given type from the entity.
     * \tparam T The type of component to remove.
     */
    template <typename T>
    void RemoveComponent() const
    {
        DFM_PROFILE_FUNCTION();
        DFM_ASSERT(m_destroyed, "Trying to remove component from a destroyed entity.");
        m_scene->m_registry.erase<T>(m_handle);
    }

    /**
     * \brief Gets the Entt handle of the entity.
     * \return The entity handle.
     */
    entt::entity& GetHandle()
    {
        DFM_PROFILE_FUNCTION();
        DFM_ASSERT(m_destroyed, "Trying to get the handle of a destroyed entity.");
        return m_handle;
    }

    /**
     * \brief Destroys the entity by setting its destroyed flag to true.
     */
    void Destroy()
    {
        DFM_PROFILE_FUNCTION();
        DFM_ASSERT(m_destroyed, "Trying to destroy an already-destroyed entity.");
        m_destroyed = true;
    }

private:
    entt::entity m_handle;
    Scene* m_scene;
    bool m_destroyed;
};

#endif // ENTITY_H