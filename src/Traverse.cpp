#include <ros/ros.h>
#include <Traverse.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

Traverse::Traverse(ros::NodeHandle nh) {
	node = nh;
}

void Traverse::move_next(move_base_msgs::MoveBaseGoal new_goal) {
	MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  	}
}