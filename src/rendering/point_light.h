#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "glm/vec3.hpp"

class PointLight
{
public:
    PointLight(const glm::vec3& position, const glm::vec3& colour);

    void SetViewPosition(const glm::vec3& view_position);
    void SetAmbientStrength(float ambient_strength);
    void SetSpecularStrength(float specular_strength);

    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] glm::vec3 GetColour() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_view_position;
    glm::vec3 m_colour;
    float m_ambient_strength;
    float m_specular_strength;
};

#endif // POINT_LIGHT_H
