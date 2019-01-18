
#include "daemon.hpp"

#include <iomanip>
#include <iostream>


class SlowDaemon: public Daemon
{

public:
    ~SlowDaemon() { alive_ = false; }

private:
    bool alive_ = true;

    virtual void task() override
    {
        std::cout << "Begin task. Alive = " << alive_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "End task. Alive = " << alive_ << std::endl;
    }

};


int main()
{
    {
        SlowDaemon daemon;
        daemon.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1750));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    return 0;
}
