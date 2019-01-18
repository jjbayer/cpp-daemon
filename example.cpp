
#include "daemon.hpp"

#include <iomanip>
#include <iostream>


int main()
{
    Daemon daemon(1.0, []() {
        const auto now = std::time(nullptr);
        std::cout << "The current time is " << std::put_time(std::localtime(&now), "%c %Z") << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    return 0;
}
