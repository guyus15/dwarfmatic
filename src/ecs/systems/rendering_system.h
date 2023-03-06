/**
 * \file rendering_system.h
 */

#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "ecs/components.h"
#include "ecs/system.h"

#include "utils/logging.h"

#include "glm/ext/matrix_transform.hpp"

 /**
  * \brief A system used to handle updating renderable components.
  */
class RenderingSystem final : public ISystem
{
public:
    explicit RenderingSystem(Scene* scene)
        : m_scene{ scene }
    {
    }

    /**
     * \brief Updates rendering-related components using the given delta time
     * \param dt The delta time.
     */
    void Update(const double dt) override
    {
        const auto renderable_view = m_scene->m_registry.view<MeshComponent, ShaderComponent>();
        for (const auto entity : renderable_view)
        {
            auto [position, rotation, scale] = m_scene->m_registry.get<TransformComponent>(entity);
            auto [model] = m_scene->m_registry.get<MeshComponent>(entity);
            auto [shader] = m_scene->m_registry.get<ShaderComponent>(entity);

            glm::mat4 model_mat{ 1.0f };
            model_mat = glm::translate(model_mat, position);
            model_mat = glm::rotate(model_mat, glm::radians(rotation.x), glm::vec3{ 1.0f, 0.0f, 0.0f });
            model_mat = glm::rotate(model_mat, glm::radians(rotation.y), glm::vec3{ 0.0f, 1.0f, 0.0f });
            model_mat = glm::rotate(model_mat, glm::radians(rotation.z), glm::vec3{ 0.0f, 0.0f, 1.0f });
            model_mat = glm::scale(model_mat, scale);

            shader.Use();
            shader.SetMat4("model", model_mat);

            model.Draw(shader);
        }
    }

private:
    Scene* m_scene;
};

#endif // RENDERING_SYSTEM_H