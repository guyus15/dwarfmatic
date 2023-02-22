/**
 * \file point_light.h
 */

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "glm/vec4.hpp"

 /**
  * \brief The data used for a point light configuration.
  * Follows the std140 standard to be used in the `Lighting` UBO.
  */
struct PointLightData
{
    alignas(16) glm::vec4 position;
    float constant;
    float linear;
    float quadratic;
    float padding;
    alignas(16) glm::vec4 ambient;
    alignas(16) glm::vec4 diffuse;
    alignas(16) glm::vec4 specular;
};

/**
 * \brief Represents a point light in 3D space.
 */
class PointLight
{
public:
    explicit PointLight(PointLightData data);

    /**
     * \brief Gets the point light data.
     * \return The point light data.
     */
    [[nodiscard]] PointLightData& GetData();

private:
    PointLightData m_data;
    unsigned int m_index;

    /**
     * \brief Initialises the point light.
     */
    void Initialise() const;

    static unsigned int s_index;
};

#endif // POINT_LIGHT_H