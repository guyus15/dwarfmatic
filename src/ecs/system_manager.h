/**
 * \file system_manager.h
 */

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "ecs/system.h"

#include "utils/logging.h"

#include <memory>
#include <unordered_map>

class Scene;

/**
 * \brief Manages systems used to act upon components.
 */
class SystemManager
{
public:
    /**
     * \brief Updates each of the registered systems using the given delta time.
     * \param dt The delta time.
     */
    void Update(double dt);

    /**
     * \brief Registers a system to the system registry.
     * \tparam T The type of system to register.
     * \param scene A pointer to the scene of which the system will act upon.
     */
    template <typename T>
    void RegisterSystem(Scene* scene)
    {
        const std::shared_ptr<ISystem> type_ptr = std::make_shared<T>(scene);
        m_registry[typeid(T).hash_code()] = type_ptr;
    }

    /**
     * \brief Removes a system from the system registry.
     * \tparam T The type of system to remove.
     */
    template <typename T>
    void RemoveSystem()
    {
        m_registry.erase(typeid(T).hash_code());
    }

    /**
     * \brief Gets a reference to the given system in the registry.
     * \tparam T The type of system to retrieve.
     * \return The retrieved system.
     */
    template <typename T>
    T& GetSystem()
    {
        return *(static_cast<T*>(m_registry.at(typeid(T).hash_code()).get()));
    }

private:
    std::unordered_map<size_t, std::shared_ptr<ISystem>> m_registry;
};

#endif // SYSTEM_MANAGER_H