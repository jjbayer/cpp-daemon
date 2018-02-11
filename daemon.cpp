#include "daemon.hpp"


Daemon::Daemon()
    : timeoutSeconds_(std::chrono::duration<double>(1.0))
    , shouldRun_(false)
    , lastTaskCompleted_(TimePoint::min())
{}

void Daemon::setTimeout(double timeoutSeconds)
{
    timeoutSeconds_ = std::chrono::duration<double>(timeoutSeconds);
}

void Daemon::start()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if( ! shouldRun_ ) {
        shouldRun_ = true;
        thread_ = std::thread(&Daemon::loop, this);
    }
}

void Daemon::stop()
{
    bool shouldStop = false;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if( shouldRun_ ) {
            shouldStop = true;
            shouldRun_ = false;
        }
    }
    if( shouldStop ) { // TODO: threading problems here?
        cv_.notify_all();
        thread_.join();
    }
}

Daemon::~Daemon()
{
    stop();
}

void Daemon::loop()
{
    while( shouldRun_ ) {
        task();
        lastTaskCompleted_ = std::chrono::steady_clock::now();
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if( cv_.wait_for(lock, timeoutSeconds_.load(), [this]() { return ! shouldRun_; }) ) {
                // Was stopped
            } else {
                // std::cout << "Time has passed" << std::endl;
            }
        }
    }
}
