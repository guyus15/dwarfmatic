/**
 * \file camera_manager.cpp
 */

#include "camera_manager.h"
#include "utils/profiling.h"

constexpr glm::vec3 DEFAULT_CAMERA_POSITION{ 0.0f, 0.0f, -10.0f };
constexpr glm::vec3 DEFAULT_CAMERA_TARGET{ 0.0f, 0.0f, 0.0f };

CameraManager CameraManager::s_instance;

/**
 * \brief Initialises the camera manager instance.
 */
void CameraManager::Initialise()
{
    DFM_PROFILE_FUNCTION();

    Get().m_main_camera = std::make_unique<Camera>(DEFAULT_CAMERA_POSITION, DEFAULT_CAMERA_TARGET);
    Get().m_cameras.push_back(Get().m_main_camera.get());
}

/**
 * \brief Gets the main camera.
 * \return The main camera instance.
 */
Camera& CameraManager::GetMainCamera()
{
    return *Get().m_main_camera;
}
