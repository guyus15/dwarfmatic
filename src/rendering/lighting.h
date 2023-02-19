#ifndef LIGHTING_H
#define LIGHTING_H

#include "point_light.h"
#include "directional_light.h"

constexpr int MAX_NO_POINT_LIGHTS = 128;

struct Lighting
{
    glm::vec4 view_position;
    int point_lights_size;
    PointLightData point_lights[MAX_NO_POINT_LIGHTS];
    DirectionalLightData directional_light;
};

#endif // LIGHTING_H