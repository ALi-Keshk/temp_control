This is a Temperature control module written in C++ and googletest framework for learning and training purposes

Follow the following steps to build and run the tests
1- clone the repo
2- initialize and update googletest submodule by running the following command:
$ git submodule update --init
3- open a terminal or CMD on windows and change directory to the repo directory
4- create a build directory and change directory to it
$ mkdir build
$ cd build
5- run cmake command to configure the project
$ cmake ..
6- run cmake build command to build the project
$ cmake --build .
7- navigate to the test directory and run temp_control_test