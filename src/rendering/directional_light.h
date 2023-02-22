/**
 * \file directional_light.h
 */

#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "glm/vec4.hpp"

/**
 * \brief The data used for a directional light configuration.
 * Follows the std140 standard to be used in the `Lighting` UBO.
 */
struct DirectionalLightData
{
    glm::vec4 direction;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

/**
 * \brief Represents a directional light in 3D space.
 */
class DirectionalLight
{
public:
    explicit DirectionalLight(DirectionalLightData data);

    /**
     * \brief Gets the directional light data.
     * \return The directional light data.
     */
    [[nodiscard]] DirectionalLightData& GetData();

private:
    DirectionalLightData m_data;

    /**
     * \brief Initialises the directional light.
     */
    void Initialise() const;
};

#endif // DIRECTIONAL_LIGHT_H
