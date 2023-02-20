#include "lighting.h"
#include "ubo.h"

constexpr int DIRECTIONAL_LIGHT_OFFSET = offsetof(Lighting, directional_light);

DirectionalLight::DirectionalLight(DirectionalLightData data)
    : m_data{ data }
{
    Initialise();
}

DirectionalLightData& DirectionalLight::GetData()
{
    return m_data;
}

void DirectionalLight::Initialise() const
{
    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");

    lighting_ubo.SetSubData(DIRECTIONAL_LIGHT_OFFSET, sizeof(DirectionalLight), &m_data);
}
