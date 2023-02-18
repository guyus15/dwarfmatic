#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera.h"

#include <memory>
#include <vector>

class CameraManager
{
public:
    static void Initialise();
    static Camera& GetMainCamera();

private:
    std::unique_ptr<Camera> m_main_camera;
    std::vector<Camera*> m_cameras;

    CameraManager() = default;
    CameraManager(const CameraManager&);
    CameraManager(CameraManager&&) noexcept;

    static CameraManager& Get() { return s_instance; }
    static CameraManager s_instance;
};

#endif // CAMERA_MANAGER_H