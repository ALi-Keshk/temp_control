cmake_minimum_required(VERSION 3.14)

set(Sources
    temp_control_test.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${Sources})
target_link_libraries( ${CMAKE_PROJECT_NAME} PUBLIC
    gtest_main
    gmock_main
    temp_control_lib
    )
    
add_test(
    Name ${CMAKE_PROJECT_NAME}
    COMMAND ${CMAKE_PROJECT_NAME}
    )

add_subdirectory(googletest)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})
