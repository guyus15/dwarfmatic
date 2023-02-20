#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "glm/vec4.hpp"

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

class SpotLight
{
public:
    explicit SpotLight(SpotLightData data);

    [[nodiscard]] SpotLightData& GetData();

private:
    SpotLightData m_data;
    unsigned int m_index;

    void Initialise() const;

    static unsigned int s_index;
};

#endif // SPOT_LIGHT_H