/**
 * @file gas.cpp
 * @brief program to run gas robot autonmously in an environment
 * @author Advait Patole
 *
 * Copyright (c) 2021 Advait Patole Gaurav Raut Sameep Pote
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include<gas.hpp>

/**
 * @brief constructor of gas class
 */
gas::gas() {
    move.linear.x = 0;
    move.linear.y = 0;
    move.linear.z = 0;
    move.angular.x = 0;
    move.angular.y = 0;
    move.angular.z = 0;

    dis_t = 1;
    vel = 0.2;
    rot = 1.57;
    detected = false;
    right = false;
    left = false;

    velpub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    scansub = nh.subscribe<sensor_msgs::LaserScan>
            ("/scan", 1, &gas::LaserCallback, this);
}

/**
 * @brief Function to check if the object is detected by laser scan
 * @param msg sensor msg sent by the laser
 */
void gas::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    if (msg->ranges[0] < dis_t && msg->ranges[29]
                       < dis_t && msg->ranges[329] < dis_t) {
        detected = true;
        if (msg->ranges[0] > msg->ranges[179]) {
            right = true;
        } else {
            left = true;
        }
        return;
    }

    detected = false;
}

/**
 * @brief Function to navigate the robot autonmously 
 */
void gas::navigate() {
    detected = false;

    ros::Rate loop_rate(10);
    while (ros::ok()) {
        if (detected) {
            if (left) {
                move.linear.x = 0;
                move.angular.z = rot;
                ROS_INFO_STREAM("Rotating Robot Obstacle detected left");
            } else {
                move.linear.x = 0;
                move.angular.z = -rot;
                ROS_INFO_STREAM("Rotating Robot Obstacle detected right");
            }
        } else {
            move.linear.x = vel;
            move.angular.z = 0;
            ROS_INFO_STREAM("Moving Forward");
        }
        velpub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void collectobject() {
    cout<<"Function to collect object"<<endl;
}

void findobject() {
    cout<<"Function to detect the object using laser scan "<<endl;
}

void stoprobot() {
    cout<<"Function to stop robot during obstacle "<<endl;
}

bool hasdestinationreached() {
    cout<<"Function to check if bot reached final"<<endl;
}

gas::~gas() {
    velpub.publish(move);
}
