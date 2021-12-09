#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sensor_msgs/image_encodings.h>
#include <bits/stdc++.h>
#include<sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>
#include"ros/ros.h"
#include"detection.hpp"
#include<vector>

detect::detect(ros::NodeHandle nh) {
	laser_dist = 0.0;
	aligned = false;
	get_dist = false;
	pos_x = 0.0;
	pos_y = 0.0;
	orientation = 0.0;

	n = nh;
}

void detect::drive_robot(float lin_x, float ang_z) {
    ROS_INFO("ROTATING THE CAR");
    ros::Rate loop_rate(10) ;

    geometry_msgs::Twist motor_command ;
    motor_command.linear.x = lin_x;
    motor_command.angular.z = ang_z;
    motorpub.publish(motor_command);

    ROS_INFO("PUBLISHED GEOMETRY MESSAGE");
    loop_rate.sleep();
}

void detect::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
	if(aligned) {
		ROS_INFO("GETTING THE DISTANCE OF OBJECT AFTER ALIGNMENT");

		laser_dist = msg->ranges[0];
		get_dist = true;
		ROS_INFO("DISTANCE OF OBJECT AFTER ALIGNMENT: %lf", laser_dist);
		drive_robot(0.0, 0.0) ;
	}
}

void detect::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	if(get_dist) {
		orientation = msg->pose.pose.orientation.z;
		pos_x = laser_dist*cos(orientation);
		pos_y = laser_dist*sin(orientation);
	}
}

void detect::process_image_callback(const sensor_msgs::Image img) {	
	if(!aligned) {
		ROS_INFO("Starting process_image_callback if robot not aligned");
		cv_bridge::CvImagePtr cv_ptr;
		try {
			cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
		}

		catch (cv_bridge::Exception& e) {
		    ROS_ERROR("cv_bridge exception: %s", e.what());
		    return;
	  	}

	  	bool spotted = false ;

	  	std::vector<int> pos ;
	  	cv::Mat im = cv_ptr->image ;
	  	
	  	for(int i = 0 ; i < im.rows ; i++)
	  	{
	  		for(int j = 0 ; j < im.cols ; j++)
	  		{
	  			cv::Vec3b pixel = im.at<cv::Vec3b>(i, j) ;
	  			if(pixel.val[0] == 0 && pixel.val[1] == 0 && pixel.val[2] == 255)
	  			{
	  				spotted = true ;
	  				pos = {i, j} ;
	  				break;
	  			}
	  		}
	  	}

	  	if(!spotted) {
	  		ROS_INFO("KEEP ROTATING OBJECT NOT SPOTTED YET");
	  		drive_robot(0.0, 0.8);
	  	}

	  	else {
	  		ROS_INFO("SPOTTED STOP CURRENTLY");
	  		drive_robot(0.0, 0.0);
	  		int row = pos[0] ;
		  	int col = pos[1] ;
		  	
			if(col < im.cols/3) {
				ROS_INFO("Moving LEFT");
				drive_robot(0.0, 0.3) ;
			}

			// GO STRAIGHT
			else if(col > im.cols/3 && col< (2*im.cols/3)) {
				ROS_INFO("Moving STRAIGHT");
				aligned = true;
				drive_robot(0.0, 0.0) ;
			}

			// GO RIGHT
			else {
				ROS_INFO("Moving RIGHT") ;
				drive_robot(0.0, -0.3) ;
			}
	  	}
	}
}

void detect::startdetect() {
	ROS_INFO("Starting detection node") ;

	camsub = n.subscribe("/camera/rgb/image_raw", 1, &detect::process_image_callback, this);
	scansub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, &detect::LaserCallback, this);
	odomsub = n.subscribe("odom", 1000, &detect::odomCallback, this);
	motorpub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 2);
}

