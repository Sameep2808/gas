#include"ros/ros.h"
#include <gtest/gtest.h>
#include "detection.hpp"
#include "collect.hpp"

 /// @brief Test for contructor
 ///
TEST(TestDetection1, constructor_test) {
	ros::NodeHandle nc;
	Detect dete(nc);
	EXPECT_TRUE(!dete.spotted);
	EXPECT_EQ(dete.out,0); 
}

/// @brief Test for laser
///
TEST(Testlaser, testlaser) {
	// initialise the test object
	ros::NodeHandle nh;
	//  Create a publisher on the topic
	Detect det(nh);
	det.aligned = true;
	int a=10;
	ros::Subscriber scansub = nh.subscribe<sensor_msgs::LaserScan>("/scan", 1, &Detect::LaserCallback, &det);
	EXPECT_NO_FATAL_FAILURE(scansub);
}

/// @brief Test to spot red color in image
///
TEST(TestDetection2, reddetection) {
  ros::NodeHandle nh;
  Detect dete(nh);
  cv::Mat img;
  img = cv::imread("/red.jpg");
  dete.spot_image(img);
  EXPECT_TRUE(!dete.spotted);
}

/// @brief Test to get the location of red color
///
TEST(TestDetection3, reddetectionloc) {
  ros::NodeHandle n;
  Detect det(n);
  cv::Mat img;
  img = cv::imread("/red.jpg");
  det.spot_image(img);
  double locx, locy;
  locx = 0.0;
  locy = 0.0;
  EXPECT_TRUE(!det.spotted);
}

/// @brief Test to check if robot is rotating once on no object found
///
TEST(TestDetection4, checkrot) {
   ros::NodeHandle ns;
   Detect de(ns);
   cv::Mat img;
   img = cv::imread("/black.jpg");
   de.startdetect();
   EXPECT_EQ(de.rotate,70); 
}

/// @brief Test to check publisher of robot
///
TEST(Testpub, teststartdetect) {
	geometry_msgs::Twist msg;
	msg.linear.x = 1.0;
	msg.linear.y = 0.0;
	msg.linear.z = 0.0;
	msg.angular.x = 0.0;
	msg.angular.y = 0.0;
	msg.angular.z = 0.0;
	// initialise the test object
	ros::NodeHandle nh;
	//  Create a publisher on the topic
	Detect det(nh);
	ros::Publisher motorpub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 2);
	ros::Subscriber camsub = nh.subscribe("/camera/rgb/image_raw", 1, &Detect::process_image_callback, &det);
	ros::Subscriber odomsub = nh.subscribe("odom", 1000, &Detect::odomCallback, &det);
	ros::Subscriber scansub = nh.subscribe<sensor_msgs::LaserScan>("/scan", 1, &Detect::LaserCallback, &det);
	motorpub.publish(msg);
	EXPECT_EQ(0, motorpub.getNumSubscribers());
	ros::Duration(10).sleep();
	EXPECT_EQ(1, motorpub.getNumSubscribers());
}


