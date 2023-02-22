/**
 * \file camera.cpp
 */

#include "camera.h"
#include "lighting.h"
#include "ubo.h"
#include "utils/profiling.h"

#include "glm/gtc/type_ptr.hpp"

constexpr int VIEW_POSITION_OFFSET = 0;

Camera::Camera(const glm::vec3& position, const glm::vec3& target_position)
    : m_position{ position },
    m_target_position{ target_position }
{
    UpdateUboBlocks();
}

/**
 * \brief Sets the position of the camera to the given position.
 * \param position The new position.
 */
void Camera::SetPosition(const glm::vec3& position)
{
    DFM_PROFILE_FUNCTION();

    m_position = position;
    UpdateUboBlocks();
}

/**
 * \brief Sets the target position of the camera to the given position.
 * \param target_position The new target position.
 */
void Camera::SetTarget(const glm::vec3& target_position)
{
    DFM_PROFILE_FUNCTION();

    m_target_position = target_position;
    UpdateUboBlocks();
}

/**
 * \brief Gets the current position of the camera.
 * \return The camera's current position.
 */
glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

/**
* \brief Updates the uniform buffer object (UBO) blocks for the camera.
*/
void Camera::UpdateUboBlocks() const
{
    DFM_PROFILE_FUNCTION();

    // Set view position
    glm::vec4 position{ m_position.x, m_position.y, m_position.z, 0.0f };
    UboManager::Retrieve("lighting").SetSubData(VIEW_POSITION_OFFSET, sizeof(Lighting::view_position), glm::value_ptr(position));

    // Set matrices (view and projection)
    glm::mat4 view = glm::lookAt(m_position, m_target_position, { 0.0f, 1.0f, 0.0f });
    UboManager::Retrieve("matrices").SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    UboManager::Retrieve("matrices").SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
}