#include "camera.h"
#include "ubo.h"

#include "glm/gtc/type_ptr.hpp"

constexpr int VIEW_POSITION_OFFSET = 0;

Camera::Camera(const glm::vec3& position, const glm::vec3& target_position)
    : m_position{ position },
    m_target_position{ target_position }
{
    UpdateUboBlocks();
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_position = position;
    UpdateUboBlocks();
}

void Camera::SetTarget(const glm::vec3& target_position)
{
    m_target_position = target_position;
    UpdateUboBlocks();
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

void Camera::UpdateUboBlocks() const
{
    // Set view position
    UboManager::Retrieve("lighting").SetSubData(VIEW_POSITION_OFFSET, sizeof(glm::vec3), glm::value_ptr(m_position));

    // Set matrices (view and projection)
    glm::mat4 view = glm::lookAt(m_position, m_target_position, { 0.0f, 1.0f, 0.0f });
    UboManager::Retrieve("matrices").SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    UboManager::Retrieve("matrices").SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
}
