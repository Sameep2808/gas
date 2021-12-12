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

detect::detect(ros::NodeHandle nh) {
	
	laser_dist = 0.0;
	aligned = false;
	get_dist = false;
	pos_x = 0.0;
	pos_y = 0.0;
	orientation = 0.0;
	n=nh;
	rotate = 0;
	out=0;
}

void detect::reach_bill() {
    MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal cur_goal;
	cur_goal.target_pose.header.frame_id = "map";
       cur_goal.target_pose.header.stamp = ros::Time::now();
   
    double diff_x = 0.452;
    double diff_y = -1.0;

    cur_goal.target_pose.pose.position.x = diff_x;
    cur_goal.target_pose.pose.position.y = diff_y;
    cur_goal.target_pose.pose.orientation.z = 0.7118;
    cur_goal.target_pose.pose.orientation.w = 0.70234;

    ac.sendGoal(cur_goal);
    ac.waitForResult();
    ROS_INFO_STREAM("Reached near bill");
    Collect c;
    c.spawn("Ghe mc",0.452,-0.25,2.5,1);
    
    ROS_INFO_STREAM("Task completed. Killing now!");
    
    ros::shutdown();
   }	

void detect::to_goal(double x, double y) {
    MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal cur_goal;
	cur_goal.target_pose.header.frame_id = "map";
    cur_goal.target_pose.header.stamp = ros::Time::now();

    cur_goal.target_pose.pose.position.x = x;
    cur_goal.target_pose.pose.position.y = y;
    cur_goal.target_pose.pose.orientation.z = -0.7118;
    cur_goal.target_pose.pose.orientation.w = 0.70234;

    ac.sendGoal(cur_goal);
    ac.waitForResult();
    ROS_INFO_STREAM("Reached near object");
    Collect c;
    c.remove_ob("box1");
    ROS_INFO_STREAM("Closed all sensors");
    
    reach_bill();
    
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
		double min_dist1 = 3.0;
		double min_dist2 = 3.0;
		double curr_dist1, curr_dist2;
		ROS_INFO("GETTING THE DISTANCE OF OBJECT AFTER ALIGNMENT");
		
		
		curr_dist1 = msg->ranges[359];
		ROS_INFO("d1 = %f",curr_dist1);
		if(curr_dist1 < 3){
		get_dist = true;
		laser_dist=curr_dist1;
		ROS_INFO("DISTANCE OF OBJECT AFTER ALIGNMENT: %lf", laser_dist);}
		else{
		drive_robot(0.2, 0.0) ;
		aligned=false;
		}
	}
}

void detect::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
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

		to_goal(pos_x, pos_y);

	}
}

void detect::process_image_callback(const sensor_msgs::Image img) {	
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

	  	bool spotted = false;

	  	std::vector<int> pos;
	  	cv::Mat im = cv_ptr->image;
	  	
	  	for(int i = 0; i < im.rows; i++)
	  	{
	  		for(int j = 0 ; j < im.cols ; j++)
	  		{
	  			cv::Vec3b pixel = im.at<cv::Vec3b>(i, j);
	  			if(pixel.val[0] == 0 && pixel.val[1] == 0 && pixel.val[2] == 255)
	  			{
	  				spotted = true ;
	  				pos = {i, j} ;
	  				break;
	  			}
	  		}
	  	}

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
}

void detect::startdetect() {
	ROS_INFO("Starting detection node") ;
	out=0;
	rotate = 0;
	camsub = n.subscribe("/camera/rgb/image_raw", 1, &detect::process_image_callback, this);
	scansub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1, &detect::LaserCallback, this);
	odomsub = n.subscribe("odom", 1000, &detect::odomCallback, this);
	motorpub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 2);
	while(out==0) {
		ros::spinOnce();
	}
}

