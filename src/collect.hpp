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

#ifndef INCLUDE_Collect_HPP_
#define INCLUDE_Collect_HPP_

#include <tf/transform_broadcaster.h>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/SpawnModel.h>
#include <gazebo_msgs/SpawnModelRequest.h>
#include <gazebo_msgs/SpawnModelResponse.h>
#include <stdlib.h> 
#include<iostream> 
#include<fstream> 
#include "std_srvs/Empty.h"
#include "geometry_msgs/Pose.h"
#include "gazebo_msgs/DeleteModel.h"
#include <string>

class Collect {
 private :
    // the node handle of the collect node
    ros::NodeHandle nh;
 
    // the Service Client that activates spawn_model_client
    ros::ServiceClient spawn_model_client;

    // the Service Client that activates delete_model_client
    ros::ServiceClient delete_model_client;

    // geometry msgs to store position of the object of robot
    geometry_msgs::Pose pose;

   

 public :
    
    // Function to Spawn Objects
    
    void spawn(char* name,double xd, double yd, double zd, int c);
    
    // Function to Remove Objects
    
    void remove_ob(char* name);

};

#endif  // INCLUDE_collect_HPP_
