#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include "glfw_window.h"

#include <memory>

class Application
{
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application(Application&&) noexcept = default;

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) noexcept = default;

    void Initialise();
    void Run() const;
    void Dispose();

private:
    std::shared_ptr<GlfwWindow> m_window;
};

#endif // APPLICATION_H