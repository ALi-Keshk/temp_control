## This is a Temperature control module written in C++ and googletest framework for learning and training purposes

### Follow the following steps to build and run the tests
* Clone the repo
* Open a terminal or CMD on windows and navigate to the repo directory
* Initialize and update googletest submodule by running the following command:
```
$ git submodule update --init 
```
* Create a build directory and change directory to it
```
$ mkdir build
$ cd build
```
* Run cmake command to configure the project
```
$ cmake ..
```
* Run cmake build command to build the project
```
$ cmake --build .
```
* Navigate to the test directory and run temp_control_test
