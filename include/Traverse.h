///============================================================================
/// @file        : Traverse.h
/// @author      : Gaurav Raut (Driver)
/// @author      : Advait Patole (Navigator)
/// @author		 : Sameep Pote (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : Traverse.h include file
///============================================================================

#ifndef INCLUDE_TRAVERSE_H_
#define INCLUDE_TRAVERSE_H_

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseActionGoal.h>

/// @class Traverse
/// @brief This is a Traverse class whose function is to make 
/// the robot traverse through the map to find the targeted
/// object.
class Traverse {
private:
		ros::NodeHandle node;
public:
	Traverse(ros::NodeHandle);
	void move_next(move_base_msgs::MoveBaseActionGoal);
	ros::Publisher goal_pub;
};

#endif  // INCLUDE_TRAVERSE_H_