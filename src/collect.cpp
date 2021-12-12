#include <collect.hpp>

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
   <size>0.5 0.5 0.5</size>\
 </box>\
</geometry>\
<surface>\
          <friction>\
            <ode>\
              <mu>1</mu>\
              <mu2>1</mu2>\
              <fdir1>0 0 0</fdir1>\
              <slip1>0</slip1>\
              <slip2>0</slip2>\
            </ode>\
            <torsional>\
              <coefficient>1</coefficient>\
              <patch_radius>0</patch_radius>\
              <surface_radius>0</surface_radius>\
              <use_patch_radius>1</use_patch_radius>\
              <ode>\
                <slip>0</slip>\
              </ode>\
            </torsional>\
          </friction>\
          <bounce>\
            <restitution_coefficient>0</restitution_coefficient>\
            <threshold>1e+06</threshold>\
          </bounce>\
          <contact>\
            <collide_without_contact>0</collide_without_contact>\
            <collide_without_contact_bitmask>1</collide_without_contact_bitmask>\
            <collide_bitmask>1</collide_bitmask>\
            <ode>\
              <soft_cfm>0</soft_cfm>\
              <soft_erp>0.2</soft_erp>\
              <kp>1e+13</kp>\
              <kd>1</kd>\
              <max_vel>0.01</max_vel>\
              <min_depth>0</min_depth>\
            </ode>\
            <bullet>\
              <split_impulse>1</split_impulse>\
              <split_impulse_penetration_threshold>-0.01</split_impulse_penetration_threshold>\
              <soft_cfm>0</soft_cfm>\
              <soft_erp>0.2</soft_erp>\
              <kp>1e+13</kp>\
              <kd>1</kd>\
            </bullet>\
          </contact>\
        </surface>\
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
    
    checks = spawn_model_client.call(spawn_model);
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
        
        checkr = delete_model_client.call(delete_model);
        
        
    }
}



