/**
 * \file directional_light.cpp
 */

#include "lighting.h"
#include "ubo.h"
#include "utils/profiling.h"

constexpr int DIRECTIONAL_LIGHT_OFFSET = offsetof(Lighting, directional_light);

DirectionalLight::DirectionalLight(DirectionalLightData data)
    : m_data{ data }
{
    Initialise();
}

/**
 * \brief Gets the directional light data.
 * \return The directional light data.
 */
DirectionalLightData& DirectionalLight::GetData()
{
    return m_data;
}

/**
 * \brief Initialises the directional light.
 */
void DirectionalLight::Initialise() const
{
    DFM_PROFILE_FUNCTION();

    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");

    lighting_ubo.SetSubData(DIRECTIONAL_LIGHT_OFFSET, sizeof(DirectionalLight), &m_data);
}
