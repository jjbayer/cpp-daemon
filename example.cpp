
#include "daemon.hpp"

#include <iomanip>
#include <iostream>


class TimeLogger: public Daemon
{
    virtual void task() override
    {
        const auto now = std::time(nullptr);
        std::cout << "The current time is " << std::put_time(std::localtime(&now), "%c %Z") << std::endl;
    }
};


int main()
{
    TimeLogger daemon;

    daemon.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    daemon.stop();

    return 0;
}
