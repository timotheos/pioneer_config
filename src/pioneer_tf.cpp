#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <nav_msgs/Odometry.h>

void poseCallback(void nav_msgs::Odometry& msg){
  static tf2_ros::TransformBroadcaster br;
  nav_msgs::Odometry transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "octomap_odom";
  transformStamped.child_frame_id = "pioneer_base";
  transformStamped.pose.pose.position.x = &msg->pose.pose.position.x;
  transformStamped.pose.pose.position.y = &msg->pose.pose.position.y;
  transformStamped.pose.pose.position.z = &msg->pose.pose.position.z;

  transformStamped.pose.pose.orientation.x = msg->p;
  transformStamped.pose.pose.orientation.y = msg->y;
  transformStamped.pose.pose.orientation.z = msg->;
  transformStamped.pose.pose.orientation.w = msg->p;
  transformStamped.pose.pose.position.y = msg->y;
  transformStamped.pose.pose.position.z = 0.0;

  tf2::Quaternion q;
  q.setRPY(0, 0, &msg->theta);
  transformStamped.transform.rotation.x = q.x();
  transformStamped.transform.rotation.y = q.y();
  transformStamped.transform.rotation.z = q.z();
  transformStamped.transform.rotation.w = q.w();

  br.sendTransform(transformStamped);
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "odom_filtered_to_pioneer_base");
  
  ros::NodeHandle node;
  
  ros::Rate r(1.0);

  while(node.ok())
  {
    br.sendTransform(transformStamped);
    ros::spinOnce();
  }
  
   return 0;
}