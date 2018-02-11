project(cppdaemon)
set(CMAKE_CXX_STANDARD 14)

add_executable(example example.cpp daemon.cpp)
target_link_libraries(example pthread)
