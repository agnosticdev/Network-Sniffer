# NetworkSniffer CMAKE
#
# CMake version number and project name
cmake_minimum_required(VERSION 3.4.3)
project(NetworkSniffer)


# The version number.
set (NetworkSniffer_VERSION_MAJOR 0)
set (NetworkSniffer_VERSION_MINOR 1)

# Set debug symbols and all warnings.
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS "-std=gnu++11")
set(CMAKE_CXX_FLAGS "-std=c++11")

# Add current and include directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_subdirectory(include)
