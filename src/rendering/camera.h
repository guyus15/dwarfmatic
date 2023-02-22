/**
 * \file camera.h
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

/**
 * \brief Represents a camera in a 3D scene.
 */
class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& target_position);

    /**
     * \brief Sets the position of the camera to the given position.
     * \param position The new position.
     */
    void SetPosition(const glm::vec3& position);

    /**
     * \brief Sets the target position of the camera to the given position.
     * \param target_position The new target position.
     */
    void SetTarget(const glm::vec3& target_position);

    /**
     * \brief Gets the current position of the camera.
     * \return The camera's current position.
     */
    [[nodiscard]] glm::vec3 GetPosition() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_target_position;

    /**
     * \brief Updates the uniform buffer object (UBO) blocks for the camera.
     */
    void UpdateUboBlocks() const;
};

#endif // CAMERA_H