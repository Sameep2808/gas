#include<collect.hpp>

void Collect::spawn(char* name,double xd, double yd, double zd, int c)
{
	//ros::NodeHandle nh;
	ros::service::waitForService("gazebo/spawn_sdf_model");
    spawn_model_client = nh.serviceClient<gazebo_msgs::SpawnModel>("gazebo/spawn_sdf_model");
    gazebo_msgs::SpawnModel spawn_model;
    spawn_model.request.model_name = name; 
    
    
    std::ifstream ifs;
    std::stringstream s;\
    //<size>0.102415 0.096252 0.101031</size>
    s<<"<?xml version='1.0'?>\
	  <sdf version='1.7'>\
	  <model name='Box1'>\
	    <link name='link_0'>\
	      <inertial>\
		<mass>0.000994789</mass>\
		<inertia>\
		  <ixx>1.61419e-06</ixx>\
		  <ixy>0</ixy>\
		  <ixz>0</ixz>\
		  <iyy>1.71568e-06</iyy>\
		  <iyz>0</iyz>\
		  <izz>1.63752e-06</izz>\
		</inertia>\
		<pose>0 0 0 0 -0 0</pose>\
	      </inertial>\
	      <pose>0 0 -0 0 -0 0</pose>\
	      <visual name='visual'>\
		<pose>0 0 0 0 -0 0</pose>\
		<geometry>\
		  <box>\
		    <size>0.5 0.5 0.5</size>\
		  </box>\
		</geometry>\
		<material>\
		  <lighting>1</lighting>\
		  <script>\
		    <uri>file://media/materials/scripts/gazebo.material</uri>\
		    <name>Gazebo/Grey</name>\
		  </script>\
		  <shader type='pixel'/>";
		  
	if(c==1){
		  s<<"<ambient>1 0 0 1</ambient>\
          <diffuse>1 0 0 1</diffuse>\
          <specular>1 0 0 1</specular>\
          <emissive>1 0 0 1</emissive>";
          }
        else if(c==2){
        s<<"<ambient>0 1 0 1</ambient>\
          <diffuse>0 1 0 1</diffuse>\
          <specular>0 1 0 1</specular>\
          <emissive>0 1 0 1</emissive>";
        }
        else{
        s<<"<ambient>0 0 1 1</ambient>\
          <diffuse>0 0 1 1</diffuse>\
          <specular>0 0 1 1</specular>\
          <emissive>0 0 1 1</emissive>";
        }
		
		s<<"</material>\
		<transparency>0</transparency>\
		<cast_shadows>1</cast_shadows>\
	      </visual>\
	      <collision name='collision'>\
		<laser_retro>0</laser_retro>\
		<max_contacts>10</max_contacts>\
		<pose>0 0 0 0 -0 0</pose>\
		<geometry>\
		  <box>\
		    <size>0.102415 0.096252 0.101031</size>\
		  </box>\
		</geometry>\
	      </collision>\
	    </link>\
	    <static>0</static>\
	    <allow_auto_disable>1</allow_auto_disable>\
	  </model>\
	  </sdf>";
    
    spawn_model.request.model_xml=s.str();
    spawn_model.request.robot_namespace = "";
    //geometry_msgs::Pose pose;
    pose.position.x = xd; pose.position.y = yd; pose.position.z = zd;
    pose.orientation.w = 1.0; pose.orientation.x = pose.orientation.y = pose.orientation.z = 0;
    spawn_model.request.initial_pose = pose;
    spawn_model.request.reference_frame = "";
    spawn_model_client.waitForExistence();
    
    if (!spawn_model_client.call(spawn_model)) {
        ROS_ERROR("Failed to call service %s","gazebo/spawn_sdf_model");
    }
    ROS_INFO("Result: %s, code %u",spawn_model.response.status_message.c_str(), spawn_model.response.success);
}

void Collect::remove_ob(char* name)
{
	//ros::NodeHandle nh;
	ros::service::waitForService("gazebo/delete_model");
	delete_model_client = nh.serviceClient<gazebo_msgs::DeleteModel>("gazebo/delete_model");
	gazebo_msgs::DeleteModel delete_model;
	delete_model.request.model_name = name;
	if (!delete_model_client.call(delete_model)) {
        ROS_ERROR("Failed to call service %s","gazebo/deleteModel");
        
    }
}



