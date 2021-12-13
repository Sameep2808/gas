///============================================================================
/// @file        : Traverse_test.cpp
/// @author      : Advait Patole (Driver)
/// @author      : Gaurav Raut (Navigator)
/// @author		   : Sameep Pote (Design Keeper)
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

/// @brief Test for Traverse constructor
///
TEST (TraverseTest1, testTraverse_constructor) {
	ros::NodeHandle nh_;
	Traverse test(nh_);
	EXPECT_EQ(test.X[0], -2.29);
}

/// @brief Test for Traverse move_next
///
TEST (TraverseTest2, testTraverse_move_next) {
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {0};
	test.W = {0};
	bool x = true;
	test.move_next();
	EXPECT_EQ(test.status, x);
}

/// @brief Test for Traverse to_goal
///
TEST (TraverseTest3, testTraverse_to_goal) {
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {-0.7118};
	test.W = {0.70234};
	bool x = true;
	test.to_goal(test.bill_x, test.bill_y);
	EXPECT_EQ(test.status, x);
}

/// @brief Test for Traverse reach_bill
///
TEST (TraverseTest4, testTraverse_reach_bill) {
	ros::NodeHandle(nh_);
	Traverse test(nh_);
	test.X = {test.bill_x};
	test.Y = {test.bill_y};
	test.Z = {0.7118};
	test.W = {0.70234};
	bool x = true;
	test.reach_bill();
	EXPECT_EQ(test.status, x);
}
