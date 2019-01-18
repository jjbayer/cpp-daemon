# cppdaemon
Simple daemon class to run periodical tasks in background

## Example

See [example.cpp](./example.cpp).

```c++
// Print the time every second
Daemon daemon(1.0, []() {
    const auto now = std::time(nullptr);
    std::cout << "The current time is " << std::put_time(std::localtime(&now), "%c %Z") << std::endl;
});
```

Output:

```
The current time is Fri Jan 18 17:38:09 2019 CET
The current time is Fri Jan 18 17:38:10 2019 CET
The current time is Fri Jan 18 17:38:11 2019 CET
...
```

