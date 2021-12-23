cmake_minimum_required(VERSION 3.14)

project(temp_control)

include_directories(../HAL/temp_sensor ../HAL/temp_cool_heat_act ../common)

set(Sources
    temp_control.cpp
)

add_library(${PROJECT_NAME} ${Sources})