#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sensor_msgs/image_encodings.h>
#include <bits/stdc++.h>
#include<sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>
#include"ros/ros.h"

class detect {
	public :
		double laser_dist ;
		bool aligned ;
		bool get_dist;
		double pos_x;
		double pos_y;
		double orientation;

		ros::Subscriber camsub;
	    ros::Subscriber scansub;
	    ros::Subscriber odomsub;
	    ros::Publisher motorpub;

	    detect(ros::NodeHandle);
	    void process_image_callback(const sensor_msgs::Image img);
	    void LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
	    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
	    void drive_robot(float lin_x, float ang_z) ;
	    void startdetect();

	private :
		ros::NodeHandle n;

} ;
