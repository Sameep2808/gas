/**
 * @brief main function 
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


#include <Traverse.h>
#include "ros/ros.h"
#include "collect.hpp"
#include "detection.hpp"
#include <vector>


int main(int argc, char **argv) {
    ros::init(argc, argv, "gas");
    ros::NodeHandle nh;
    Traverse tr(nh) ;
    tr.move_next();
    ROS_INFO_STREAM("Completed navigation!");

    while(ros::ok()) {
        ros::spinOnce();
    }
    return 0;
}
