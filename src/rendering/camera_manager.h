/**
 * \file camera_manager.h
 */

#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera.h"

#include <memory>
#include <vector>

/**
 * \brief A singleton class to manage cameras in the scene.
 */
class CameraManager
{
public:
    CameraManager(const CameraManager&) = delete;
    CameraManager(CameraManager&&) noexcept = default;

    CameraManager& operator=(const CameraManager&) = delete;
    CameraManager& operator=(CameraManager&&) noexcept = default;

    /**
     * \brief Initialises the camera manager instance.
     */
    static void Initialise();

    /**
     * \brief Gets the main camera.
     * \return The main camera instance.
     */
    static Camera& GetMainCamera();

private:
    std::unique_ptr<Camera> m_main_camera;
    std::vector<Camera*> m_cameras;

    CameraManager() = default;
    ~CameraManager() = default;

    /**
     * \brief Gets a reference to the singleton instance.
     * \return The single instance.
     */
    static CameraManager& Get() { return s_instance; }

    static CameraManager s_instance;
};

#endif // CAMERA_MANAGER_H