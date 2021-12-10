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
#include <move_base_msgs/MoveBaseAction.h>
#include <vector>

/// @class Traverse
/// @brief This is a Traverse class whose function is to make 
/// the robot traverse through the map to find the targeted
/// object.
class Traverse {
public:
	Traverse(ros::NodeHandle);
	void move_next();
	std::vector<move_base_msgs::MoveBaseGoal> goals;
	ros::Publisher goal_pub;
	std::vector<double> X = {7.88, 4.6625, 4.48, 7.88, 11.366, 11.3, 4.9, 5.05, 14.33, 15.28, 15.311, 14.1311, 0};
	std::vector<double> Y = {11.52, 11.61, 7.314, 7.36, 12.9, 18.95, 18.7, 13.27, 12.9, 12.88, 19, 19.06, 7.36};
	std::vector<double> Z = {-0.7118, -0.007, 0.7023, 1, 0.71, 1, -0.7012, 0.008, 0.008, 0.703, -1, -0.7012, 1};
	std::vector<double> W = {0.70234, 1, 0.7118, 0.007, 0.705, 0.007, 0.713, 1, 1, 0.711, 0.008, 0.713, 0};

private :
	ros::NodeHandle node;

};

#endif  // INCLUDE_TRAVERSE_H_