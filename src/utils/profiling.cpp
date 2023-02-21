#include "profiling.h"

#include <algorithm>
#include <thread>

Instrumentor Instrumentor::s_instance;

Instrumentor::Instrumentor()
    : m_current_session{ nullptr }, m_profile_count{ 0 }
{
}

void Instrumentor::BeginSession(const std::string& name, const std::string& filepath)
{
    Get().m_output_stream.open(filepath);
    WriteHeader();
    Get().m_current_session = new InstrumentationSession{ name };
}

void Instrumentor::EndSession()
{
    WriteFooter();
    Get().m_output_stream.close();
    delete Get().m_current_session;
    Get().m_current_session = nullptr;
    Get().m_profile_count = 0;
}

void Instrumentor::WriteProfile(const ProfileResult& result)
{
    if (Get().m_profile_count > 0)
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

void Instrumentor::WriteHeader()
{
    Get().m_output_stream << R"({"otherData": {},"traceEvents":[)";
    Get().m_output_stream.flush();
}

void Instrumentor::WriteFooter()
{
    Get().m_output_stream << "]}";
    Get().m_output_stream.flush();
}

InstrumentationTimer::InstrumentationTimer(std::string name)
    : m_name{ std::move(name) }, m_stopped{ false }
{
}

InstrumentationTimer::~InstrumentationTimer()
{
    if (!m_stopped)
    {
        Stop();
    }
}

void InstrumentationTimer::Stop()
{
    const auto end_timepoint = std::chrono::high_resolution_clock::now();

    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

    const size_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());

    Instrumentor::WriteProfile({ m_name, start, end, thread_id });

    m_stopped = true;
}