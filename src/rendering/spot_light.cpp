#include "lighting.h"
#include "ubo.h"

constexpr int SPOT_LIGHTS_SIZE_OFFSET = offsetof(Lighting, spot_lights_size);
constexpr int SPOT_LIGHTS_ARRAY_OFFSET = offsetof(Lighting, spot_lights);

unsigned int SpotLight::s_index = 0;

SpotLight::SpotLight(SpotLightData data)
    : m_data{ data },
    m_index{ s_index }
{
    s_index++;

    Initialise();
}

SpotLightData& SpotLight::GetData()
{
    return m_data;
}

void SpotLight::Initialise() const
{
    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    const size_t spot_lights_size = s_index;

    lighting_ubo.SetSubData(SPOT_LIGHTS_SIZE_OFFSET, sizeof(Lighting::spot_lights_size), &spot_lights_size);
    lighting_ubo.SetSubData(SPOT_LIGHTS_ARRAY_OFFSET + sizeof(SpotLightData) * m_index, sizeof(SpotLightData), &m_data);
}
