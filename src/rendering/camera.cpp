#include "camera.h"

#include "glm/gtc/type_ptr.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& target_position, Ubo matrices_block)
    : m_position{ position },
    m_target_position{ target_position },
    m_ubo_block{ std::move(matrices_block) }
{
    UpdateMatricesBlock();
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_position = position;
    UpdateMatricesBlock();
}

void Camera::SetTarget(const glm::vec3& target_position)
{
    m_target_position = target_position;
    UpdateMatricesBlock();
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

void Camera::UpdateMatricesBlock() const
{
    glm::mat4 view = glm::lookAt(m_position, m_target_position, { 0.0f, 1.0f, 0.0f });
    m_ubo_block.SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    m_ubo_block.SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
}
