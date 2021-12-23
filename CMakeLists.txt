cmake_minimum_required(VERSION 3.14)

project(temp_control)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(App)
add_subdirectory(test)