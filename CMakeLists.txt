
cmake_minimum_required(VERSION 3.10)
project(LinkedHashMap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

# Add the executable
add_executable(code main.cpp)
target_include_directories(code PRIVATE .)
