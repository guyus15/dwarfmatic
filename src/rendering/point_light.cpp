/**
 * \file point_light.cpp
 */

#include "lighting.h"
#include "ubo.h"
#include "utils/profiling.h"

constexpr int POINT_LIGHTS_SIZE_OFFSET = offsetof(Lighting, point_lights_size);
constexpr int POINT_LIGHTS_ARRAY_OFFSET = offsetof(Lighting, point_lights);

unsigned int PointLight::s_index = 0;

PointLight::PointLight(PointLightData data)
    : m_data{ data },
    m_index{ s_index }
{
    s_index++;

    Initialise();
}

/**
* \brief Gets the point light data.
* \return The point light data.
*/
PointLightData& PointLight::GetData()
{
    return m_data;
}

/**
* \brief Gets the index of the point light.
* \return The point light's index.
*/
unsigned int PointLight::GetIndex() const
{
    return m_index;
}

/**
 * \brief Initialises the point light.
 */
void PointLight::Initialise() const
{
    DFM_PROFILE_FUNCTION();

    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    const size_t point_lights_size = s_index;

    lighting_ubo.SetSubData(POINT_LIGHTS_SIZE_OFFSET, sizeof(Lighting::point_lights_size), &point_lights_size);
    lighting_ubo.SetSubData(POINT_LIGHTS_ARRAY_OFFSET + sizeof(PointLightData) * m_index, sizeof(PointLightData), &m_data);
}