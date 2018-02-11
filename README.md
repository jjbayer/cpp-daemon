# cppdaemon
Simple daemon class to run periodical tasks in background

## Example

See [example.cpp](./example.cpp).

```c++
/// Class to print time every second
class TimeLogger: public Daemon
{
    virtual void task() override
    {
        const auto now = std::time(nullptr);
        std::cout << "The current time is " << std::put_time(std::localtime(&now), "%c %Z") << std::endl;
    }
};
```
