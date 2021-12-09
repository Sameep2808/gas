#include "ros/ros.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "reach_goal");

  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  ROS_INFO("Sending goal");

  std::vector<std::vector<double>> locs {{4.484, -0.480, -0.010}};

  for(auto loc : locs){
    goal.target_pose.pose.position.x = loc[0];
    goal.target_pose.pose.orientation.w = loc[1];

    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base moved 1 meter forward");
    else
      ROS_INFO("The base failed to move forward 1 meter for some reason");
  }

  return 0;
}
