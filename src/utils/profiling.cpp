/**
 * \file profiling.cpp
 */

#include "profiling.h"

#include <algorithm>
#include <thread>

Instrumentor Instrumentor::s_instance;

Instrumentor::Instrumentor()
    : m_current_session{ nullptr }, m_profile_count{ 0 }
{
}

/**
 * \brief Begins an instrumentation session.
 * \param name The name of the instrumentation session.
 * \param filepath The path of the file in which to save profiling results.
 */
void Instrumentor::BeginSession(const std::string& name, const std::string& filepath)
{

    Get().m_output_stream.open(filepath);
    WriteHeader();
    Get().m_current_session = new InstrumentationSession{ name };
}

/**
 * \brief Ends the current instrumentation session.
 */
void Instrumentor::EndSession()
{
    WriteFooter();
    Get().m_output_stream.close();
    delete Get().m_current_session;
    Get().m_current_session = nullptr;
    Get().m_profile_count = 0;
}

/**
 * \brief Writes a profile result to the profiling results file.
 * \param result The profiling result to be written.
 */
void Instrumentor::WriteProfile(const ProfileResult& result)
{
    if (Get().m_profile_count++ > 0)
    {
        Get().m_output_stream << ", ";
    }

    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');

    Get().m_output_stream << "{";
    Get().m_output_stream << R"("cat":"function",)";
    Get().m_output_stream << "\"dur\":" << (result.end - result.start) << ',';
    Get().m_output_stream << R"("name":")" << name << "\",";
    Get().m_output_stream << R"("ph":"X",)";
    Get().m_output_stream << "\"pid\":0,";
    Get().m_output_stream << R"("tid":")" << result.thread_id << "\",";
    Get().m_output_stream << "\"ts\":" << result.start;
    Get().m_output_stream << "}";

    Get().m_output_stream.flush();
}

/**
 * \brief Writes a profiling results header to the profiling results file.
 */
void Instrumentor::WriteHeader()
{
    Get().m_output_stream << R"({"otherData": {},"traceEvents":[)";
    Get().m_output_stream.flush();
}

/**
 * \brief Writes a profiling results footer to the profiling results file.
 */
void Instrumentor::WriteFooter()
{
    Get().m_output_stream << "]}";
    Get().m_output_stream.flush();
}

InstrumentationTimer::InstrumentationTimer(std::string name)
    : m_name{ std::move(name) }, m_stopped{ false }
{
    m_start_timepoint = std::chrono::high_resolution_clock::now();
}

InstrumentationTimer::~InstrumentationTimer()
{
    if (!m_stopped)
    {
        Stop();
    }
}

/**
 * \brief Stops the instrumentation timer, and writes the profiling result to the results file.
 */
void InstrumentationTimer::Stop()
{
    const auto end_timepoint = std::chrono::high_resolution_clock::now();

    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

    const size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());

    Instrumentor::WriteProfile({ m_name, start, end, thread_id });

    m_stopped = true;
}