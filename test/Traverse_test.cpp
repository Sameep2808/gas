///============================================================================
/// @file        : Traverse_test.cpp
/// @author      : Advait Patole (Driver)
/// @author      : Gaurav Raut (Navigator)
/// @author		 : Sameep Pote (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : Traverse_test.cpp include file
///============================================================================

#include <ros/ros.h>
#include <Traverse.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <actionlib/client/simple_action_client.h>
#include "detection.hpp"
#include <gtest/gtest.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

TEST (TraverseTest1, testTraverse_constructor) {
	ros::NodeHandle nh_;
	Traverse test(nh_);
	EXPECT_EQ(test.X[0], -2.29);
}

TEST (TraverseTest2, testTraverse_move_next) {
	// MoveBaseClient mbc_test("move_base",true);
	// while(!mbc_test.waitForServer(ros::Duration(5.0))) {
 //    ROS_INFO("Waiting for the move_base action server to come up");
 //  	}
	// move_base_msgs::MoveBaseGoal cur_goal;
	// cur_goal.target_pose.header.frame_id = "map";
	// cur_goal.target_pose.header.stamp = ros::Time::now();
	// cur_goal.target_pose.pose.position.x = 0;
	// cur_goal.target_pose.pose.position.y = 0;
	// cur_goal.target_pose.pose.orientation.z = 0;
	// cur_goal.target_pose.pose.orientation.w = 0;
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {0};
	test.W = {0};
	// mbc_test.waitForServer();
	// mbc_test.sendGoal(cur_goal);
	bool x = true;
	test.move_next();
	EXPECT_EQ(test.status, x);
}

TEST (TraverseTest3, testTraverse_to_goal) {
	// MoveBaseClient mbc_test("move_base",true);
	// while(!mbc_test.waitForServer(ros::Duration(5.0))) {
 //    ROS_INFO("Waiting for the move_base action server to come up");
 //  	}
	// move_base_msgs::MoveBaseGoal cur_goal;
	// cur_goal.target_pose.header.frame_id = "map";
	// cur_goal.target_pose.header.stamp = ros::Time::now();
	// cur_goal.target_pose.pose.position.x = 0;
	// cur_goal.target_pose.pose.position.y = 0;
	// cur_goal.target_pose.pose.orientation.z = 0;
	// cur_goal.target_pose.pose.orientation.w = 0;
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {-0.7118};
	test.W = {0.70234};
	// mbc_test.waitForServer();
	// mbc_test.sendGoal(cur_goal);
	bool x = true;
	test.to_goal(test.bill_x, test.bill_y);
	EXPECT_EQ(test.status, x);
}

TEST (TraverseTest4, testTraverse_reach_bill) {
	// MoveBaseClient mbc_test("move_base",true);
	// while(!mbc_test.waitForServer(ros::Duration(5.0))) {
 //    ROS_INFO("Waiting for the move_base action server to come up");
 //  	}
	// move_base_msgs::MoveBaseGoal cur_goal;
	// cur_goal.target_pose.header.frame_id = "map";
	// cur_goal.target_pose.header.stamp = ros::Time::now();
	// cur_goal.target_pose.pose.position.x = 0;
	// cur_goal.target_pose.pose.position.y = 0;
	// cur_goal.target_pose.pose.orientation.z = 0;
	// cur_goal.target_pose.pose.orientation.w = 0;
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {0.7118};
	test.W = {0.70234};
	// mbc_test.waitForServer();
	// mbc_test.sendGoal(cur_goal);
	bool x = true;
	test.reach_bill();
	EXPECT_EQ(test.status, x);
}