/**
 * \file lighting.h
 */

#ifndef LIGHTING_H
#define LIGHTING_H

#include "rendering/point_light.h"
#include "rendering/spot_light.h"
#include "rendering/directional_light.h"

#include "ecs/components.h"

#include "ubo.h"

#include "glm/ext/matrix_transform.hpp"

constexpr int MAX_NO_POINT_LIGHTS = 128;
constexpr int MAX_NO_SPOT_LIGHTS = 128;

/**
 * \brief Represents various types of lighting.
 * Follows the std140 standard to be used in the `Lighting` UBO.
 */
struct Lighting
{
    glm::vec4 view_position;
    int point_lights_size;
    PointLightData point_lights[MAX_NO_POINT_LIGHTS];
    int spot_lights_size;
    SpotLightData spot_lights[MAX_NO_SPOT_LIGHTS];
    DirectionalLightData directional_light;
};

// TODO: Finish documenting this, and finish implement the lighting system in `lighting_system.h`.

inline void UpdatePointLight(const unsigned int index, const PointLightData& data)
{
    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    lighting_ubo.SetSubData(offsetof(Lighting, point_lights) + sizeof(PointLightData) * index, sizeof(PointLightData), &data);
}

inline void UpdateDirectionalLight(const DirectionalLightData& data)
{
    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    lighting_ubo.SetSubData(offsetof(Lighting, directional_light), sizeof(DirectionalLightData), &data);
}

inline void UpdateSpotLight(const unsigned int index, const SpotLightData& data)
{
    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    lighting_ubo.SetSubData(offsetof(Lighting, spot_lights) + sizeof(SpotLightData) * index, sizeof(SpotLightData), &data);
}

inline glm::vec3 CalculateDirectionFromRotation(const glm::vec3 rotation)
{
    const glm::vec3 default_direction = { 0.0f, 0.0f, -1.0f };
    glm::mat4 rotation_mat{ 1.0f };
    rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.x), glm::vec3{ 1.0f, 0.0f, 0.0f });
    rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.y), glm::vec3{ 0.0f, 1.0f, 0.0f });
    rotation_mat = glm::rotate(rotation_mat, glm::radians(rotation.z), glm::vec3{ 0.0f, 0.0f, 1.0f });

    return rotation_mat * glm::vec4(default_direction, 0.0f);
}

inline PointLightData ComponentToPointLightData(const TransformComponent& transform_component, const LightComponent& light_component)
{
    auto& position = transform_component.position;

    PointLightData point_light_data{};
    point_light_data.position = { position.x, position.y, position.z, 0.0f };
    point_light_data.constant = light_component.constant;
    point_light_data.linear = light_component.linear;
    point_light_data.quadratic = light_component.quadratic;
    point_light_data.ambient = { light_component.ambient.x, light_component.ambient.y, light_component.ambient.z, 0.0f };
    point_light_data.diffuse = { light_component.diffuse.x, light_component.diffuse.y, light_component.diffuse.z, 0.0f };
    point_light_data.specular = { light_component.specular.x, light_component.specular.y, light_component.specular.z, 0.0f };

    return point_light_data;
}

inline DirectionalLightData ComponentToDirectionalLightData(const TransformComponent& transform_component, const LightComponent& light_component)
{
    glm::vec3 direction = CalculateDirectionFromRotation(transform_component.rotation);

    DirectionalLightData directional_light_data{};
    directional_light_data.direction = { direction.x, direction.y, direction.z, 0.0f };
    directional_light_data.ambient = { light_component.ambient.x, light_component.ambient.y, light_component.ambient.z, 0.0f };
    directional_light_data.diffuse = { light_component.diffuse.x, light_component.diffuse.y, light_component.diffuse.z, 0.0f };
    directional_light_data.specular = { light_component.specular.x, light_component.specular.y, light_component.specular.z, 0.0f };

    return directional_light_data;
}

inline SpotLightData ComponentToSpotLightData(const TransformComponent& transform_component, const LightComponent& light_component)
{
    auto& position = transform_component.position;
    glm::vec3 direction = CalculateDirectionFromRotation(transform_component.rotation);

    SpotLightData spot_light_data{};
    spot_light_data.position = { position.x, position.y, position.z, 0.0f };
    spot_light_data.direction = { direction.x, direction.y, direction.z, 0.0f };
    spot_light_data.constant = light_component.constant;
    spot_light_data.linear = light_component.linear;
    spot_light_data.quadratic = light_component.quadratic;
    spot_light_data.inner_cut_off = glm::cos(glm::radians(light_component.inner_angle));
    spot_light_data.outer_cut_off = glm::cos(glm::radians(light_component.outer_angle));
    spot_light_data.ambient = { light_component.ambient.x, light_component.ambient.y, light_component.ambient.z, 0.0f };
    spot_light_data.diffuse = { light_component.diffuse.x, light_component.diffuse.y, light_component.diffuse.z, 0.0f };
    spot_light_data.specular = { light_component.specular.x, light_component.specular.y, light_component.specular.z, 0.0f };

    return spot_light_data;
}

#endif // LIGHTING_H