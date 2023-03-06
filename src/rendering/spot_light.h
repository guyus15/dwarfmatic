/**
 * \file spot_light.h
 */

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "glm/vec4.hpp"

/**
 * \brief The data used for a spot light configuration.
 * Follows the std140 standard to be used in the `Lighting` UBO.
 */
struct SpotLightData
{
    alignas(16) glm::vec4 position;
    alignas(16) glm::vec4 direction;
    float constant;
    float linear;
    float quadratic;
    float inner_cut_off;
    float outer_cut_off;
    float padding1;
    float padding2;
    float padding3;
    alignas(16) glm::vec4 ambient;
    alignas(16) glm::vec4 diffuse;
    alignas(16) glm::vec4 specular;
};

/**
 * \brief Represents a spot light in 3D space.
 */
class SpotLight
{
public:
    explicit SpotLight(SpotLightData data);

    /**
     * \brief Gets the spot light data.
     * \return The spot light data.
     */
    [[nodiscard]] SpotLightData& GetData();

    /**
     * \brief Gets the index of the spot light.
     * \return The spot light's index.
     */
    [[nodiscard]] unsigned int GetIndex() const;

private:
    SpotLightData m_data;
    unsigned int m_index;

    /**
     * \brief Initialises the spot light.
     */
    void Initialise() const;

    static unsigned int s_index;
};

#endif // SPOT_LIGHT_H