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
	std::vector<double> X = {-2.29, -5.1, 1.184, -5, 5.35, 4.221};
	std::vector<double> Y = {1.2336, -2.21, 3.31, 8.6, 3, 9};
	std::vector<double> Z = {-0.707, 0.7071, -1, -0.7071, 0.7071, -0.7071};
	std::vector<double> W = {0.707, 0.7071, 3.3, 0.7071, 0.7071, 0.7071};

	// std::vector<double> X = {-2.29, -5.075, -5.1, -2.072, 1.184, 1.066, -5, -5, 4.24, 5.35, 5.35, 4.221, 0};
	// std::vector<double> Y = {1.2336, 1.15, -2.21, -2.072, 3.31, 8.8, 8.6, 3.612, 3, 3, 8.9, 9, 7.36};
	// std::vector<double> Z = {-0.707, 3.53, 0.7071, 1, -1, -1, -0.7071, 3.5327, 2.83, 0.7071, -1, -0.7071, 1};
	// std::vector<double> W = {0.707, 1, 0.7071, 0.007, 3.3, 7.11, 0.7071, 1, 1, 0.7071, 5.68, 0.7071, 0};

private :
	ros::NodeHandle node;

};

#endif  // INCLUDE_TRAVERSE_H_