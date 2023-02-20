#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "glm/vec4.hpp"

struct DirectionalLightData
{
    glm::vec4 direction;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

class DirectionalLight
{
public:
    explicit DirectionalLight(DirectionalLightData data);

    [[nodiscard]] DirectionalLightData& GetData();

private:
    DirectionalLightData m_data;

    void Initialise() const;
};

#endif // DIRECTIONAL_LIGHT_H
