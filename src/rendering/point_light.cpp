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

PointLightData& PointLight::GetData()
{
    return m_data;
}

void PointLight::Initialise() const
{
    DFM_PROFILE_FUNCTION();

    const Ubo& lighting_ubo = UboManager::Retrieve("lighting");
    const size_t point_lights_size = s_index;

    lighting_ubo.SetSubData(POINT_LIGHTS_SIZE_OFFSET, sizeof(Lighting::point_lights_size), &point_lights_size);
    lighting_ubo.SetSubData(POINT_LIGHTS_ARRAY_OFFSET + sizeof(PointLightData) * m_index, sizeof(PointLightData), &m_data);
}
