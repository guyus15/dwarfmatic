#ifndef CAMERA_H
#define CAMERA_H

#include "ubo.h"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& target_position, Ubo matrices_block);

    void SetPosition(const glm::vec3& position);
    void SetTarget(const glm::vec3& target_position);

    [[nodiscard]] glm::vec3 GetPosition() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_target_position;
    Ubo m_ubo_block;

    void UpdateMatricesBlock() const;
};

#endif // CAMERA_H
