/**
 * application.h
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include "glfw_window.h"

#include <memory>

/**
 * \brief Represents the main entry point to the application.
 */
class Application
{
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application(Application&&) noexcept = default;

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) noexcept = default;

    /**
     * \brief Performs application initialisation.
     */
    void Initialise();

    /**
     * \brief Runs the application.
     */
    void Run() const;

    /**
     * \brief Performs a cleanup before application is shut down.
     */
    static void Dispose();

private:
    std::shared_ptr<GlfwWindow> m_window;
};

#endif // APPLICATION_H