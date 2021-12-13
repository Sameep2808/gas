///============================================================================
/// @file        : Traverse.cpp
/// @author      : Gaurav Raut (Driver)
/// @author      : Advait Patole (Navigator)
/// @author		 : Sameep Pote (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : Traverse.cpp include file
///============================================================================

#include <ros/ros.h>
#include <Traverse.h>
#include <vector>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "collect.hpp"
#include "detection.hpp"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

Traverse::Traverse(ros::NodeHandle nh) {
	node = nh;
	status = false;
	bill_x = 0.452;
	bill_y = -1.0;
}

void Traverse::move_next() {
	MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  	}
  	ros::NodeHandle ns;
  	Detect det(ns);
  	for(int i = 0; i < X.size(); i++) {
  		move_base_msgs::MoveBaseGoal cur_goal;
  		cur_goal.target_pose.header.frame_id = "map";
    	cur_goal.target_pose.header.stamp = ros::Time::now();
    	cur_goal.target_pose.pose.position.x = X[i];
    	cur_goal.target_pose.pose.position.y = Y[i];
    	cur_goal.target_pose.pose.orientation.z = Z[i];
    	cur_goal.target_pose.pose.orientation.w = W[i];
    	goals.push_back(cur_goal);
    	ac.sendGoal(goals[i]);
    	status = ac.waitForResult();
    	ROS_INFO_STREAM("Reached node " << i);

    	
    	det.startdetect();
  	}
}

void Traverse::to_goal(double x, double y) {
    MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal cur_goal;
	cur_goal.target_pose.header.frame_id = "map";
    cur_goal.target_pose.header.stamp = ros::Time::now();

    cur_goal.target_pose.pose.position.x = x;
    cur_goal.target_pose.pose.position.y = y;
    cur_goal.target_pose.pose.orientation.z = -0.7118;
    cur_goal.target_pose.pose.orientation.w = 0.70234;

    ac.sendGoal(cur_goal);
    ac.waitForResult();
    status = ac.waitForResult();
    ROS_INFO_STREAM("Reached near object");
    Collect c;
    c.remove_ob("box1");
    ROS_INFO_STREAM("Closed all sensors");
    reach_bill();
}

void Traverse::reach_bill() {
    MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal cur_goal;
	cur_goal.target_pose.header.frame_id = "map";
    cur_goal.target_pose.header.stamp = ros::Time::now();
   
    cur_goal.target_pose.pose.position.x = bill_x;
    cur_goal.target_pose.pose.position.y = bill_y;
    cur_goal.target_pose.pose.orientation.z = 0.7118;
    cur_goal.target_pose.pose.orientation.w = 0.70234;

    ac.sendGoal(cur_goal);
    ac.waitForResult();
    status = ac.waitForResult();
    ROS_INFO_STREAM("Reached near bill");
    Collect c;
    c.spawn("Ghe mc",0.452,-0.25,2.5,1);
    
    ROS_INFO_STREAM("Task completed. Killing now!");
    
    ros::shutdown();
}
