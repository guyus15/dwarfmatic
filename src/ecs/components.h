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

#endif // COMPONENTS_H