cmake_minimum_required(VERSION 3.14)

project(temp_control_test)

set(CMAKE_CXX_STANDARD 11)

if(${CMAKE_PROJECT_NAME} MATCHES temp_control_test)
    enable_testing()
    add_subdirectory(test)
elseif(${CMAKE_PROJECT_NAME} MATCHES temp_control)
    #TODO configure the build for the project itself not the test
endif()

add_subdirectory(App)