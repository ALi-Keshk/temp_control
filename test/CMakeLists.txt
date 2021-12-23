cmake_minimum_required(VERSION 3.14)

set(This temp_control_test)

set(Sources
    temp_control_test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries( ${This} PUBLIC
    gtest_main
    temp_control
)

add_test(
    Name ${This}
    COMMAND ${This}
)