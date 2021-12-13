///============================================================================
/// @file        : Traverse.h
/// @author      : Gaurav Raut (Driver)
/// @author      : Advait Patole (Navigator)
/// @author      : Sameep Pote (Design Keeper)
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
  /**
   * @brief Constructor for class Traverse
   *
   * @param ros::NodeHandle
   */
  explicit Traverse(ros::NodeHandle);

  /**
   * @brief Function to travserse the robot in a trajectory
   *
   */
  void move_next();
  bool status;
  /// @brief Method to navigate robot to a x,y
  /// coordinates on map
  ///
  /// @param x x-coordinate
  /// @param y y-coordinate
  void to_goal(double x, double y);

  /// @brief Reach the billing site
  ///
  void reach_bill();
  double bill_x;  // x-coordinate of billing site
  double bill_y;  // y-coordinate of billing site

  // X coordinates for traversing
  std::vector<double> X = { -2.29, -5.1, 1.184, -5, 5.35, 4.221 };

  // Y coordinates for traversing
  std::vector<double> Y = { 1.2336, -2.21, 3.31, 8.6, 3, 9 };

  // Z orientations for traversing
  std::vector<double> Z = { -0.707, 0.7071, -1, -0.7071, 0.7071, -0.7071 };

  // W orientation for traversing
  std::vector<double> W = { 0.707, 0.7071, 3.3, 0.7071, 0.7071, 0.7071 };
  std::vector<move_base_msgs::MoveBaseGoal> goals;  // Goals for traversing

 private:
  // Node Handle for ROS
  ros::NodeHandle node;
};

#endif  // INCLUDE_TRAVERSE_H_
