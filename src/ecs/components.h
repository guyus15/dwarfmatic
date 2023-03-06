/**
 * \file components.h
 */

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ecs/uuid.h"

#include "glm/vec3.hpp"

#include "rendering/model.h"
#include "rendering/shader.h"

/**
 * \brief Represents a universally-unique-identifier (UUID) used to identify an entity.
 */
struct IdComponent
{
    UUID uuid;
};

/**
 * \brief Represents the name or string-value that an entity will possess.
 */
struct TagComponent
{
    std::string name;
};

/**
 * \brief Represents the world-space transformation of the entity.
 */
struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

/**
 * \brief Represents the 3D mesh used to draw an entity.
 */
struct MeshComponent
{
    Model model;
};

/**
 * \brief Represents the shader that will be used to render the entity.
 */
struct ShaderComponent
{
    Shader shader;
};

/**
 * \brief Represents a component that will be used to represent different types of light.
 */
struct LightComponent
{
    /**
     * \brief Represents different types of light sources of which the light component can behave as.
     */
    enum class Type
    {
        Point,
        Directional,
        Spot
    };

    /**
     * \brief The type of light source that the light component will behave as.
     */
    Type type;

    /**
     * \brief Constant attentuation value. Usually kept at 1.0f to make sure the denominator
     * never becomes smaller than 1.0f which would cause intensity to boost at certain distances.
     */
    float constant;

    /**
     * \brief Linear attentuation value. Reduces intensity of light linearly in proportion to the
     * distance from the light source.
     */
    float linear;

    /**
     * \brief Quadratic attentuation value. Will be less significant to the compared linear value when
     * distance is small, but gets much larger as the distane grows.
     */
    float quadratic;

    /**
     * \brief The initial ambient light colour and intensity.
     */
    glm::vec3 ambient;

    /**
     * \brief The initial diffuse light colour and intensity.
     */
    glm::vec3 diffuse;

    /**
     * \brief The initial specular light colour and intensity.
     */
    glm::vec3 specular;

    /**
    * \brief Specific to spot lights - the light's inner angle (in degrees).
    */
    [[maybe_unused]] float inner_angle;

    /**
     * \brief Specific to spot lights - the light's outer angle (in degrees).
     */
    [[maybe_unused]] float outer_angle;
};

#endif // COMPONENTS_H