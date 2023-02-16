#include "point_light.h"

constexpr float DEFAULT_AMBIENT_STRENGTH = 0.2f;
constexpr float DEFAULT_SPECULAR_STRENGTH = 0.5f;

PointLight::PointLight(const glm::vec3& position, const glm::vec3& colour)
    : m_position{ position },
    m_view_position{},
    m_colour{ colour },
    m_ambient_strength{ DEFAULT_AMBIENT_STRENGTH },
    m_specular_strength{ DEFAULT_SPECULAR_STRENGTH }
{
}

void PointLight::SetViewPosition(const glm::vec3& view_position)
{
    m_view_position = view_position;
}

void PointLight::SetAmbientStrength(const float ambient_strength)
{
    m_ambient_strength = ambient_strength;
}

void PointLight::SetSpecularStrength(const float specular_strength)
{
    m_specular_strength = specular_strength;
}

glm::vec3 PointLight::GetPosition() const
{
    return m_position;
}

glm::vec3 PointLight::GetColour() const
{
    return m_colour;
}