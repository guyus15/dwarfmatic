#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "glm/vec3.hpp"

struct PointLightData
{
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class PointLight
{
public:
    explicit PointLight(PointLightData data);

    [[nodiscard]] PointLightData& GetData();

private:
    PointLightData m_data;
    unsigned int m_index;

    void Initialise() const;

    static unsigned int s_index;
};

#endif // POINT_LIGHT_H
