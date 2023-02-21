#include "logging.h"
#include "utils/profiling.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Logging::s_core_logger;

void Logging::Initialise()
{
    DFM_PROFILE_FUNCTION();

    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_core_logger = spdlog::stdout_color_mt("DWARFMATIC");
    s_core_logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Logging::GetCoreLogger()
{
    DFM_PROFILE_FUNCTION();

    return s_core_logger;
}