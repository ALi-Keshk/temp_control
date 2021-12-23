cmake_minimum_required(VERSION 3.14)

project(temp_control)

set(Sources
    temp_control.cpp
)

add_library(${PROJECT_NAME} ${Sources})