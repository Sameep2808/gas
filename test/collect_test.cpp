///============================================================================
/// @file        : test.cpp
/// @author      : Gaurav Raut, Advait Patole, Sameep Pote
/// @version     : 1.0
/// @copyright   : MIT License
/// @brief       : Test definition
///============================================================================

#include <gtest/gtest.h>
#include <ros/ros.h>

#include <collect.hpp>


TEST(spawn, test_gas_constructor) {
	Collect c;
	c.spawn("box1",0,0,0,1);
	EXPECT_TRUE(c.checks);
}

TEST(remove, test_gas_constructor) {
	Collect b;
	b.spawn("box3",2,3,0,1);
	b.remove_ob("box3");
	EXPECT_FALSE(b.checkr);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "ct");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
