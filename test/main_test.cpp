///============================================================================
/// @file        : test.cpp
/// @author      : Gaurav Raut, Advait Patole, Sameep Pote
/// @version     : 1.0
/// @copyright   : MIT License
/// @brief       : Test definition
///============================================================================

#include <gtest/gtest.h>
#include <ros/ros.h>


int main(int argc, char **argv) {
  ros::init(argc, argv, "test_gas");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
