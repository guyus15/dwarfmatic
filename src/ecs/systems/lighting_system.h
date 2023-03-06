/**
 * \file lighting_system.h
 */

#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

#include "ecs/components.h"
#include "ecs/system.h"

#include "rendering/lighting.h"

enum class LightUpdateType
{
    Point,
    Spot,
    Directional,
    All
};

/**
 * \brief A system used to handle updating lighting components.
 */
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
        const auto& lights = m_scene->m_registry.view<LightComponent>();

        for (const auto& entity : lights)
        {
            auto& [id] = m_scene->m_registry.get<IdComponent>(entity);
            auto& transform_component = m_scene->m_registry.get<TransformComponent>(entity);

            switch (auto& light_component = m_scene->m_registry.get<LightComponent>(entity); light_component.type)
            {
            case LightComponent::Type::Point:
                if (auto search = m_point_lights.find(id); search != m_point_lights.end()) continue;

                {
                    auto point_light_data = ComponentToPointLightData(transform_component, light_component);
                    PointLight point_light{ point_light_data };

                    // Register this entity with this spot light.
                    m_point_lights[id] = point_light.GetIndex();
                }

                break;

            case LightComponent::Type::Directional:
                {
                    auto directional_light_data = ComponentToDirectionalLightData(transform_component, light_component);
                    [[maybe_unused]] DirectionalLight directional_light{ directional_light_data };
                }

                break;

            case LightComponent::Type::Spot:
                if (auto search = m_spot_lights.find(id); search != m_spot_lights.end()) continue;

                {
                    auto spot_light_data = ComponentToSpotLightData(transform_component, light_component);
                    SpotLight spot_light{ spot_light_data };

                    // Register this entity with this spot light.
                    m_spot_lights[id] = spot_light.GetIndex();
                }

                break;
            }
        }
    }

    /**
     * \brief Updates the given type of light sources within the scene.
     * \param update_type The type of light source to update.
     */
    void UpdateLightSources(const LightUpdateType update_type)
    {
        const auto view = m_scene->m_registry.view<LightComponent>();

        for (auto& entity : view)
        {
            auto& [uuid] = m_scene->m_registry.get<IdComponent>(entity);
            auto& transform_component = m_scene->m_registry.get<TransformComponent>(entity);
            auto& light_component = m_scene->m_registry.get<LightComponent>(entity);
            auto& light_type = light_component.type;

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
            else if (light_type == LightComponent::Type::Point && update_type == LightUpdateType::Point)
            {
                // Update point lights.
                const unsigned int index = m_point_lights[uuid];
                auto data = ComponentToPointLightData(transform_component, light_component);
                UpdatePointLight(index, data);
            }
            else if (light_type == LightComponent::Type::Directional && update_type == LightUpdateType::Directional)
            {
                // Update directional light.
                auto data = ComponentToDirectionalLightData(transform_component, light_component);
                UpdateDirectionalLight(data);
            }
            else if (light_type == LightComponent::Type::Spot && update_type == LightUpdateType::Spot)
            {
                // Update spot lights.
                const unsigned int index = m_spot_lights[uuid];
                auto data = ComponentToSpotLightData(transform_component, light_component);
                UpdateSpotLight(index, data);
            }
        }
    }

private:
    Scene* m_scene;
    std::unordered_map<UUID, unsigned int> m_spot_lights;
    std::unordered_map<UUID, unsigned int> m_point_lights;
};

#endif // LIGHTING_SYSTEM_H