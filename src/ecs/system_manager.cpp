/**
 * \file system_manager.cpp
 */

#include "ecs/system_manager.h"

 /**
  * \brief Updates each of the registered systems using the given delta time.
  * \param dt The delta time.
  */
void SystemManager::Update(const double dt)
{
    for (const auto& [_, value] : m_registry)
    {
        value.get()->Update(dt);
    }
}