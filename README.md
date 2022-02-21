# ![gas](https://user-images.githubusercontent.com/77606010/145761283-59a5ff5d-cba7-48b7-8d9a-9a24475aaf1b.png) The Autonomous Collection Robot
## Badges
[![Build Status](https://app.travis-ci.com/sameep989/gas.svg?branch=main)](https://app.travis-ci.com/sameep989/gas)
[![Coverage Status](https://coveralls.io/repos/github/sameep989/gas/badge.svg?branch=main)](https://coveralls.io/github/sameep989/gas?branch=main)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
## Authors
- [Gaurav Raut](https://github.com/gauraut) - M.Eng. Robotics student. I am interested in Computer Vision. I like rock music and anime.
- [Advait Patole](https://github.com/advaitp) - Graduate student at University of Maryland pursuing M.Eng. Robotics. Likes rock music.
- [Sameep Pote](https://github.com/Sameep2808) - Graduate student at University of Maryland pursuing M.Eng. Robotics.Loves to watch animes.

## Working
![gif](https://user-images.githubusercontent.com/77606010/145767290-c55dae8e-2dfe-49f5-92b8-2136d36f49ad.gif)

## Hardware Implementation Prototype

### Detecting warehouse
![g1](https://github.com/Sameep2808/gas/blob/master/gif/1.gif)

### Pickup Mechanism
![g2](https://github.com/Sameep2808/gas/blob/master/gif/2.gif)

## License
```
MIT License

Copyright (c) 2021 Gaurav Raut, Advait Patole, Sameep Pote

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## AIP documents and links
- Product and Iteration backlogs, Work logs - https://docs.google.com/spreadsheets/d/1KLyT2uEeI9b1TvwLfODoASXBfRGHRH0ggyx3o0lfnI0/edit?usp=sharing
- Sprint Meeting Document - https://docs.google.com/document/d/13UunkO20LzQ7dAkEkqdN7CIHWwQ9Xm0ZXc96tBIPPL8/edit?usp=sharing
- Video link (Phase 1) - https://youtu.be/7jqNsCYOL8Y
- Final Presentation Video - https://www.youtube.com/watch?v=89bhQhLPd2o
## Overview

The following proposal proposes a ROS package which simulates a pickup and place robot in a custom made world which replicates a real world storehouse facility. The code name, ‘GAS’, comes after the initials of the project developers. The idea of our project comes from the concept of warehouse automation. The robot that we are proposing will autonomously find any random targeted object and collect it for the user. Such a robot can be used in a variety of commercial and logistics scenarios. For example, our robot can be deployed in an IKEA storehouse. Here, the robot will input the customer’s receipt and autonomously find the items in the receipt and collect them by searching them in the warehouse. For doing this, the robot will localize itself and autonomously path a way towards the items in the organised warehouse and collect them using its fork actuator and drop the items in the billing area. For this, the robot uses LiDAR and also uses it to avoid any obstacle collision while navigating itself. The camera on robot is used to identify objects using HSV colour space.

## Technology
![Technology](https://user-images.githubusercontent.com/77606010/143810362-86c8a3c6-1070-4e19-949f-a3d171f37d05.png)

Our robot’s technology is divided into two parts:

- Navigation and Obstacle Avoidance: The aim of this aspect is
to navigate the robot using LiDAR and AMCL ROS package. Using this, the robot will autonomously navigate itself
to find the targeted location.It creates a Laser scan map around the robot and using this generated map, decides to continue on its
planned path or change its path.We have used ROS move_base package to traverse the robot to desired location.

- Object Identification: The camera on robot is used to identify objects. Every object has an unique colour and the robot will identify the object based on it's colour and then call a rosservice to pick up the object.Once the object is detected the robot uses Lidar to align and starts to move towards the object.

- Object Spawning: The objects are spawned at random location in the arena.Once the object is detected and the robot reaches near the object disappears from the arena.The robot starts to traverse towards the billing location.When the robot reaches the billing location the object spawns at the billing location.    

## Activity Diagram
![Screenshot from 2021-12-13 14-04-06](https://user-images.githubusercontent.com/77606010/145872861-ced46e77-77fb-4e37-a965-6270dfcbab2e.png)

## Class UML Diagram
![Screenshot from 2021-12-13 14-03-53](https://user-images.githubusercontent.com/77606010/145872958-6757e784-b208-4b5f-a9c7-11762dd2be40.png)


## Dependencies and Technologies used

- Programming language : C++
- Build system : catkin_make
- Operating System : Ubuntu 20.04
- Packages : OpenCV, sensor_msgs, gazebo_msgs, cv_bridge, move_base, turtlebot3 package

## Risks and Mitigation

We are using HSV color space for object detection based on
colour which sometimes does not give proper results If the
lighting conditions are not proper it fails to detect the object
based on it’s colour and also does not give accurate results as
compared to object detection using Convolutional Neural
Network. When the object is detected while picking the object there are issues of slippage of the object from the robot’s arm.
If there is a delay in sending readings from lidar to the
microprocessor the robot can hit the obstacles and it can affect
the performance of the robot. Object detection based on colour
of the object is cost effective and is also not computationally
heavy as compared to objection detection using CNN.
Mechanical failure of the robot also can lead to unexpected
behaviour of the robot’s arm and can be avoided by regular
maintenance of the robot.

## Organization
![Organization](https://user-images.githubusercontent.com/77606010/143795159-a4084549-180b-4f31-a1b5-d834b7cb681c.png)

The organization consists of a modest three programmer team.
Every programmer will assume to be a process manager and
the product manager of each other. The stakeholders and users
will drive the product backlog and requirements. This suggests
that the product backlog is a rather a live document rather than
a predefined checklist.

## Downloading the turtlebot3 package 
1. In new terminal
```
cd ~/catkin_ws/src/
git clone https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git
git clone https://github.com/ROBOTIS-GIT/turtlebot3.git
cd ~/catkin_ws && catkin_make
cd ~/catkin_ws/src/
git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
cd ~/catkin_ws && catkin_make
```

## Steps to Build package
1. Create Catkin Workspace
```
cd ~/catkin_ws
catkin_make clean && catkin_make
```
2. Copy the repository in src folder of catkin workspace
```
git clone --recursive https://github.com/Sameep2808/gas.git
cd ..
catkin_make clean && catkin_make
source ./devel/setup.bash
```
## Steps to Run package
1. Make sure you have sourced setup file
```
cd ~/catkin_ws
source ./devel/setup.bash
```

2. To run the package 
```
roslaunch gas navigation.launch
```

3. To run the package spawn the object at any location in map 
```
roslaunch gas navigation.launch x_d:=4 y_d:=3
```

4. To run the tests for package 
```
catkin_make run_tests_gas_rostest_test_test.launch
catkin_make run_tests_gas_rostest_test_Traverse_test.launch
```
## Recording bag file
```
roslaunch gas navigation.launch record_gas:=true  # By default record is set false. Records bag for 10 seconds
```

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
## Making Doxygen documentation

This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.
How to Generate Doxygen Documentation

To install doxygen run the following command:
```
sudo apt-get install doxygen

Now from the cloned directory run:

doxygen doxygen
```
Generated doxygen files are in html format and you can find them in ./docs folder. With the following command
```
cd docs
cd html
google-chrome index.html
```
## Working with Eclipse IDE

### Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/Sameep2808/gas.git
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of cpp-boilerplate

```
cd ~/workspace
mkdir -p boilerplate-eclipse
cd boilerplate-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../cpp-boilerplate/
```

### Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "boilerplate-eclipse" directory created previously as root directory -> Finish

### Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold boilerplate-eclipse project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

### Run

1. In Eclipse, right click on the boilerplate-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


### Debug


1. Set breakpoint in source file (i.e. double click in the left margin on the line you want 
the program to break).

2. In Eclipse, right click on the boilerplate-eclipse in Project Explorer, select Debug As -> 
Local C/C++ Application, choose the binaries to run (e.g. shell-app).

3. If prompt to "Confirm Perspective Switch", select yes.

4. Program will break at the breakpoint you set.

5. Press Step Into (F5), Step Over (F6), Step Return (F7) to step/debug your program.

6. Right click on the variable in editor to add watch expression to watch the variable in 
debugger window.

7. Press Terminate icon to terminate debugging and press C/C++ icon to switch back to C/C++ 
perspetive view (or Windows->Perspective->Open Perspective->C/C++).

## Future Plans 
1. This is only a software demonstration we plan to make a working model.
2. We plan to integrate depth sensors like kinect on the robot.
3. We plan to make a swarm of collection robots.

## Bugs
1. Currently the tests are divided into two nodes because of rostest limitation of 60 seconds.
2. Move_ base package waits and goes for more optimal path.
3. Object Spawning has string inputs which has conflicts with ISO C++ standards this does not affect the performance of software.

### Plugins

- CppChEclipse

    To install and run cppcheck in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> cppcheclipse.
    Set cppcheck binary path to "/usr/bin/cppcheck".

    2. To run CPPCheck on a project, right click on the project name in the Project Explorer 
    and choose cppcheck -> Run cppcheck.


- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml

- Git

    It is possible to manage version control through Eclipse and the git plugin, but it typically requires creating another project. If you're interested in this, try it out yourself and contact me on Canvas.
