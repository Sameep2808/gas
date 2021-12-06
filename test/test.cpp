///============================================================================
/// @file        : test.cpp
/// @author      : Gaurav Raut, Advait Patole, Sameep Pote
/// @version     : 1.0
/// @copyright   : MIT License
/// @brief       : Test definition
///============================================================================

#include <gtest/gtest.h>
#include <ros/ros.h>
#include <gas.hpp>


TEST(gas_test1, test_gas_constructor) {
  gas robot1;
  EXPECT_EQ(robot1.move.linear.x, 0)
}

TEST(gas_test2, test_gas_detection) {
  gas robot1;
  bool x = false;
  EXPECT_EQ(x, robot1.detection);
}

/// @fn int main(int, char**)
/// @brief Main file to run all tests
///
/// @pre
/// @post
/// @param argc
/// @param argv
/// @return
int main(int argc, char **argv) {
  ros::init(argc, argv, "gas_test_client");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}