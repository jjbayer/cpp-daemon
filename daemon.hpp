#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

/// Abstract daemon class
/// Subclasses which implement daemon can be started & stopped and run in background
class Daemon
{
public:

    /// seconds
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

    /// Cannot copy
    Daemon(const Daemon &) = delete;

    /// Cannot be assigned
    Daemon & operator=(const Daemon &) = delete;

    explicit Daemon();

    /// Set period between action() calls
    /// If this function is not called, timeout is set to one second
    /// May be called even when daemon is running
    void setTimeout(double timeoutSeconds);

    void start();

    void stop();

    /// When was task completed last?
    /// Useful for checking daemon health
    TimePoint lastTaskCompleted() const
    {
        return lastTaskCompleted_;
    }

    virtual ~Daemon();

private:

    /// Implement periodically called task in this method
    virtual void task() = 0;

    /// Internal function which runs in thread_
    void loop();

    std::atomic<std::chrono::duration<double> > timeoutSeconds_;
    bool shouldRun_;
    std::atomic<TimePoint> lastTaskCompleted_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::thread thread_;
};
