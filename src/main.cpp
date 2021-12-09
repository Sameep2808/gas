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
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <vector>



int main(int argc, char **argv) {
    ros::init(argc, argv, "gas");
    ros::NodeHandle nh;
    
    Traverse nav(nh);
    ros::Publisher pub = nh.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 100);
    std::vector <move_base_msgs::MoveBaseActionGoal> goals;
    move_base_msgs::MoveBaseGoal my_goal;
    my_goal.target_pose.header.frame_id = "map";
    my_goal.target_pose.header.stamp = ros::Time::now();
    my_goal.target_pose.pose.position.x = 7.85;
    my_goal.target_pose.pose.position.y = 11.46;
    my_goal.target_pose.pose.orientation.z = -0.712;
    my_goal.target_pose.pose.orientation.w = 0.70234;
    nav.move_next(my_goal);
    ac.sendGoal(my_goal);
    ac.waitForResult();

 //    while(ros::ok()) {
 //    	pub.publish(my_goal);
 //    	ros::spin();
	// }
    ROS_INFO_STREAM("Goal reached!");
    return 0;
}