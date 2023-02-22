/**
 * \file profiling.h
 */

#ifndef PROFILING_H
#define PROFILING_H

#include <chrono>
#include <fstream>
#include <string>

const std::string DEFAULT_RESULTS_PATH = "./profile-results.json";

struct ProfileResult
{
    std::string name;
    long long start, end;
    size_t thread_id;
};

struct InstrumentationSession
{
    std::string name;
};

class Instrumentor
{
public:
    Instrumentor(const Instrumentor&) = delete;
    Instrumentor(Instrumentor&&) noexcept = delete;

    Instrumentor& operator=(const Instrumentor&) = delete;
    Instrumentor& operator=(Instrumentor&&) noexcept = delete;

    /**
     * \brief Begins an instrumentation session.
     * \param name The name of the instrumentation session.
     * \param filepath The path of the file in which to save profiling results.
     */
    static void BeginSession(const std::string& name, const std::string& filepath = DEFAULT_RESULTS_PATH);

    /**
     * \brief Ends the current instrumentation session.
     */
    static void EndSession();

    /**
     * \brief Writes a profile result to the profiling results file.
     * \param result The profiling result to be written.
     */
    static void WriteProfile(const ProfileResult& result);

    /**
     * \brief Writes a profiling results header to the profiling results file.
     */
    static void WriteHeader();

    /**
     * \brief Writes a profiling results footer to the profiling results file.
     */
    static void WriteFooter();

private:
    InstrumentationSession* m_current_session;
    std::ofstream m_output_stream;
    int m_profile_count;

    Instrumentor();
    ~Instrumentor() = default;

    static Instrumentor& Get() { return s_instance; }
    static Instrumentor s_instance;
};

class InstrumentationTimer
{
public:
    explicit InstrumentationTimer(std::string name);
    ~InstrumentationTimer();

    InstrumentationTimer(const InstrumentationTimer&) = default;
    InstrumentationTimer(InstrumentationTimer&&) noexcept = default;

    InstrumentationTimer& operator=(const InstrumentationTimer&) = delete;
    InstrumentationTimer& operator=(InstrumentationTimer&&) noexcept = delete;

    /**
     * \brief Stops the instrumentation timer, and writes the profiling result to the results file.
     */
    void Stop();

private:
    const std::string m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_timepoint;
    bool m_stopped;
};

#define DFM_PROFILING 1
#if DFM_PROFILING
#define DFM_PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__{ name }
#define DFM_PROFILE_FUNCTION() DFM_PROFILE_SCOPE(__FUNCSIG__)
#define DFM_PROFILE_BEGIN_SESSION(name) Instrumentor::BeginSession(name)
#define DFM_PROFILE_END_SESSION() Instrumentor::EndSession()
#else
#define DFM_PROFILE_SCOPE(name)
#define DFM_PROFILE_FUNCTION(name)
#define DFM_PROFILE_BEGIN_SESSION(name)
#define DFM_PROFILE_END_SESSION()
#endif

#endif // PROFILING_H