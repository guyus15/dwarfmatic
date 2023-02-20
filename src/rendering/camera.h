#ifndef CAMERA_H
#define CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& target_position);

    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target_position);

    [[nodiscard]] glm::vec3 GetPosition() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_target_position;

    void UpdateUboBlocks() const;
};

#endif // CAMERA_H
