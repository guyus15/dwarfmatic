/**
 * \file logging.h
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <memory>

#include "spdlog/spdlog.h"

/**
 * \brief Provides application logging functionality.
 */
class Logging
{
public:
    /**
     * \brief Intialises application logging.
     */
    static void Initialise();

    /**
     * \brief Gets a reference to the application's core logger.
     * \return A reference to the core logger.
     */
    static std::shared_ptr<spdlog::logger>& GetCoreLogger();

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
};

#define DFM_CORE_TRACE(...) Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define DFM_CORE_INFO(...) Logging::GetCoreLogger()->info(__VA_ARGS__)
#define DFM_CORE_WARN(...) Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define DFM_CORE_ERROR(...) Logging::GetCoreLogger()->error(__VA_ARGS__)
#define DFM_CORE_CRITICAL(...) Logging::GetCoreLogger()->critical(__VA_ARGS__)

#endif // LOGGING_H