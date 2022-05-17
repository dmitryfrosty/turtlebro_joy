#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int16.h"
#include <cmath>

ros::Publisher pub;
ros::Publisher publ;

float conversion(float old, float old_min, float old_max, float new_min, float new_max)
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

void servo(float angle)
{
  std_msgs::Int16 pub_servo;
  pub_servo.data = trunc(angle);
  publ.publish(pub_servo);
}

void Callback(sensor_msgs::Joy msg)
{ float angle = conversion(msg.axes[2], -1.0, 1.0, 1, 180);
  float linear = conversion(msg.axes[1], -1.0, 1.0, -0.2, 0.2);
  float angular = conversion(msg.axes[0], -1.0, 1.0, -1.5, 1.5);
  vel(linear, angular);
  servo(angle);
}

int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "turtlebro_joy");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  publ = n.advertise<std_msgs::Int16>("servo_cam", 1000);
  ros::Subscriber sub = n.subscribe("joy_orig", 1000, Callback);
  ros::spin();
  return 0;
}