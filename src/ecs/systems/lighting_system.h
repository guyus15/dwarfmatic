/**
 * \file lighting_system.h
 */

#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

#include "ecs/components.h"
#include "ecs/system.h"

enum class LightUpdateType
{
    Point,
    Spot,
    Directional,
    All
};

class LightingSystem final : public ISystem
{
public:
    explicit LightingSystem(Scene* scene)
        : m_scene{ scene }
    {
    }

    /**
     * \brief Updates lighting-related components using the given delta time
     * \param dt The delta time.
     */
    void Update(const double dt) override
    {
    }

private:
    Scene* m_scene;

    void UpdateLightSources(const LightUpdateType update_type)
    {
        const auto view = m_scene->m_registry.view<LightComponent>();

        for (auto& entity : view)
        {
            auto [uuid] = m_scene->m_registry.get<IdComponent>(entity);
            auto [position, rotation, scale] = m_scene->m_registry.get<TransformComponent>(entity);
            auto light_component = m_scene->m_registry.get<LightComponent>(entity);
            auto light_type = light_component.type;

            if (update_type == LightUpdateType::All)
            {
                // Update all the lights.

                if (light_type == LightComponent::Type::Point)
                {
                    const unsigned int index = m_point_lights[uuid];
                    auto data = ComponentToPointLightData(transform_component, light_component);
                    UpdatePointLight(index, data);
                }

                if (light_type == LightComponent::Type::Directional)
                {
                    auto data = ComponentToDirectionalLightData(transform_component, light_component);
                    UpdateDirectionalLight(data);
                }

                if (light_type == LightComponent::Type::Spot)
                {
                    const unsigned int index = m_spot_lights[uuid];
                    auto data = ComponentToSpotLightData(transform_component, light_component);
                    UpdateSpotLight(index, data);
                }
            }
        }
    }
};

#endif // LIGHTING_SYSTEM_H