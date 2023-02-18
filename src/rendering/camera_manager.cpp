#include "camera_manager.h"

constexpr glm::vec3 DEFAULT_CAMERA_POSITION{ 0.0f, 0.0f, 10.0f };
constexpr glm::vec3 DEFAULT_CAMERA_TARGET{ 0.0f, 0.0f, 0.0f };

CameraManager CameraManager::s_instance;

void CameraManager::Initialise()
{
    Get().m_main_camera = std::make_unique<Camera>(DEFAULT_CAMERA_POSITION, DEFAULT_CAMERA_TARGET);
    Get().m_cameras.push_back(Get().m_main_camera.get());
}

Camera& CameraManager::GetMainCamera()
{
    return *Get().m_main_camera;
}
