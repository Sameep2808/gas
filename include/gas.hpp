/**
 * @file gas.hpp
 * @brief gas class highlighting all attributes of gas 
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

#ifndef INCLUDE_gas_HPP_
#define INCLUDE_gas_HPP_

#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>

class gas {
 private :
    // the node handle of the gas node
    ros::NodeHandle nh;

    // the laser subscriber that subscribes to /scan topic
    ros::Subscriber scansub;

    // ros publisher that publishes the velocity data
    ros::Publisher velpub;

    // geometry msgs to store motion of robot
    geometry_msgs::Twist move;

    // distance threshold
    float dis_t;

    // the angular velocity of robot
    float rot;

    // the linear velocity of robot
    float vel;

    // turns of the robot
    bool right;
    bool left;

 public :
    /**
     * @brief constructor of gas class
     */
    gas();

    // Variable to check if the obstacle is detected by the laser
    bool objectfound;

    // locations of starting point of robot
    vector<double> startpoint;

    // locations of destination 
    vector<double> endpoint;

    // current location of robot 
    vector<double> currpos;

    // location of aisles
    vector<vector<double>> aislelocations;

    /**
     * @brief Function to collect object
     */
    void collectobject();

    /**
     * @brief Function to detect the object using laser scan 
     */
    void findobject();

    /**
     * @brief Function to stop robot during obstacle 
     */
    void stoprobot();

    /**
     * @brief Function to check if bot reached final 
     * return bool
     */
    bool hasdestinationreached();
    
    /**
     * @brief Function to check if the object is detected by laser scan
     * @param msg sensor msg sent by the laser
     */
    void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

    /**
     * @brief Function to navigate the robot autonmously 
     */
    void navigate();

    /**
     * @brief destructor of gas class
     */
    ~gas();
};

#endif  // INCLUDE_gas_HPP_
