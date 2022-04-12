#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

float cd(float old, float old_min, float old_max, float new_min, float new_max)
{
  float new_value = (((old - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min;
  return(new_value);
}

void vel(float velx, float velz)
{
  geometry_msgs::Twist pub_vel;
  pub_vel.linear.x = velx;
  pub_vel.angular.z = velz;
  pub.publish(pub_vel);
}

void Callback(sensor_msgs::Joy msg)
{
  float linear = cd(msg.axes[1], -1.0, 1.0, -0.2, 0.2);
  float angular = cd(msg.axes[0], -1.0, 1.0, -1.5, 1.5);
  vel(linear, angular);
}

int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "turtlebro_joy");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("joy_orig", 1000, Callback);
  ros::spin();
  return 0;
}