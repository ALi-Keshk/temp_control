cmake_minimum_required(VERSION 3.14)

set(This temp_control_lib)

set(Sources
    temp_control.cpp
)

add_library(${This} ${Sources})

target_include_directories(${This} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../HAL/temp_sensor 
        ../HAL/temp_cool_heat_act 
        ../common
        )
