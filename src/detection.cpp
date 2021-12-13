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
#include"Traverse.h"
#include<vector>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "collect.hpp"
#include "tf/transform_datatypes.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

Detect::Detect(ros::NodeHandle nh) {
	laser_dist = 0.0;
	aligned = false;
	get_dist = false;
	pos_x = 0.0;
	pos_y = 0.0;
	orientation = 0.0;
	n=nh;
	rotate = 0;
	out=0;
	// bill_x = 0.452;
	// bill_y = -1.0;
	spotted = false;
	pos={};
}

void Detect::drive_robot(float lin_x, float ang_z) {
    ROS_INFO("ROTATING THE CAR");
    ros::Rate loop_rate(10);

    geometry_msgs::Twist motor_command ;
    motor_command.linear.x = lin_x;
    motor_command.angular.z = ang_z;
    motorpub.publish(motor_command);

    ROS_INFO("PUBLISHED GEOMETRY MESSAGE");
    loop_rate.sleep();
}

void Detect::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
	ROS_INFO("GETTING THE DISTANCE OF OBJECT AFTER ALIGNMENT");
	if(aligned) {
		double min_dist1 = 3.0;
		double min_dist2 = 3.0;
		double curr_dist1, curr_dist2;
		ROS_INFO("GETTING THE DISTANCE OF OBJECT AFTER ALIGNMENT");
		curr_dist1 = msg->ranges[359];
		ROS_INFO("d1 = %f",curr_dist1);
		
		if(curr_dist1 < 3) {
		get_dist = true;
		laser_dist=curr_dist1;
		ROS_INFO("DISTANCE OF OBJECT AFTER ALIGNMENT: %lf", laser_dist);
		}

		else {
		drive_robot(0.2, 0.0) ;
		aligned=false;
		}
	}
}

void Detect::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	if(get_dist) {
		orientation = msg->pose.pose.orientation.z;
		double inc_x = msg->pose.pose.position.x;
		double inc_y = msg->pose.pose.position.y;
		
		tf::Quaternion q(msg->pose.pose.orientation.x,msg->pose.pose.orientation.y,msg->pose.pose.orientation.z,msg->pose.pose.orientation.w);
		double roll,pitch,yaw;
		tf::Matrix3x3 m(q);
		m.getRPY(roll,pitch,yaw);
		ROS_INFO("POSITION OOOOOOOOO %lf", sin(yaw));
		
		ROS_INFO("POSITION X  %lf", inc_x);
		ROS_INFO("POSITION Y  %lf", inc_y);
		
		pos_x = inc_x + (laser_dist - 1)*cos(yaw);
		pos_y = inc_y  + (laser_dist - 1)*sin(yaw) ;

		ROS_INFO("POSITION X OF OBJECT AFTER ALIGNMENT: %lf", pos_x);
		ROS_INFO("POSITION Y OF OBJECT AFTER ALIGNMENT: %lf", pos_y);
		ROS_INFO("TRAVERSING TO THE OBJECT");

		Traverse tr(n);
		tr.to_goal(pos_x, pos_y);

	}
}

void Detect::spot_image(cv::Mat im) {
	for(int i = 0 ; i < im.rows ; i++) {
  		for(int j = 0 ; j < im.cols ; j++) {
  			cv::Vec3b pixel = im.at<cv::Vec3b>(i, j) ;
  			if(pixel.val[0] == 0 && pixel.val[1] == 0 && pixel.val[2] == 255) {
  				spotted = true ;
  				pos = {i, j} ;
  				break;
  			}
  		}
  	}
}

void Detect::robot_motion(cv::Mat im) {
	if(!spotted && rotate < 70) {
  		ROS_INFO("KEEP ROTATING OBJECT NOT SPOTTED YET");
  		drive_robot(0.0, 0.8);
  		rotate++;
  		ROS_INFO_STREAM("ROBOT ROTATED TIMES: " << rotate);	
	 }

  	else if(spotted){
  		ROS_INFO("SPOTTED STOP CURRENTLY");
  		drive_robot(0.0, 0.0);
  		int row = pos[0] ;
	  	int col = pos[1] ;
	  	
	  	// GO LEFT
		if(col < im.cols/3) {
			ROS_INFO("Moving LEFT");
			drive_robot(0.0, 0.3) ;
		}

		// GO STRAIGHT
		else if(col < 2*im.cols/3 &&col > im.cols/3) {
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

  	else {
  		drive_robot(0.0, 0);
  		out=1;
  		ROS_INFO_STREAM("POCHLO");
  	}
}

void Detect::process_image_callback(const sensor_msgs::Image img) {	
	if(!aligned) {
		ROS_INFO("Starting process_image_callback if robot not aligned %d",rotate);
		cv_bridge::CvImagePtr cv_ptr;
		try {
			cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
		}

		catch (cv_bridge::Exception& e) {
		    ROS_ERROR("cv_bridge exception: %s", e.what());
		    return;
	  	}

	  	spotted = false ;
	  	cv::Mat im = cv_ptr->image ;
	  	spot_image(im) ;
	  	robot_motion(im) ;
	}
}

void Detect::startdetect() {
	ROS_INFO("Starting detection node") ;
	out=0;
	rotate = 0;
	camsub = n.subscribe("/camera/rgb/image_raw", 1, &Detect::process_image_callback, this);
	scansub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, &Detect::LaserCallback, this);
	odomsub = n.subscribe("odom", 1000, &Detect::odomCallback, this);
	motorpub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 2);
	while(out==0) {
		ros::spinOnce();
	}
}

