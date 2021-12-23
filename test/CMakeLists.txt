cmake_minimum_required(VERSION 3.14)

set(This temp_control_test)

set(Sources
    temp_control_test.cpp
)

include_directories(../App)
include_directories(../HAL/temp_sensor ../HAL/temp_cool_heat_act ../common)

add_executable(${This} ${Sources})
target_link_libraries( ${This} PUBLIC
    gtest_main
    gmock_main
    temp_control
)

add_test(
    Name ${This}
    COMMAND ${This}
)