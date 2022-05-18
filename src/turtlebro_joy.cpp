#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int16.h"
#include <cmath>

ros::Publisher pubvel;
ros::Publisher pubservocam;
ros::Publisher pubservohand;

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
  pubvel.publish(pub_vel);
}

void servocam(float angle)
{
  std_msgs::Int16 pub_servo;
  pub_servo.data = trunc(angle);
  pubservocam.publish(pub_servo);
}

void servohand(bool flag_button_2, bool flag_button_3)
{
  std_msgs::Int16 pub_servo;
  
  if (flag_button_2 != 0)
  {
  pub_servo.data = 0;
  pubservohand.publish(pub_servo);
  }
  
  if (flag_button_3 != 0)
  {
  pub_servo.data = 55;
  pubservohand.publish(pub_servo);
  }
    
}

void Callback(sensor_msgs::Joy msg)
{ 
  float angle_servo_cam = conversion(msg.axes[2], -1.0, 1.0, 1, 110);
  float linear = conversion(msg.axes[1], -1.0, 1.0, -0.2, 0.2);
  float angular = conversion(msg.axes[0], -1.0, 1.0, -1.5, 1.5);
  
  vel(linear, angular);
  servocam(angle_servo_cam);
  
  servohand(msg.buttons[1], msg.buttons[2]);
}

int main(int argc, char **argv)
{ 
  ros::init(argc, argv, "turtlebro_joy");
  ros::NodeHandle n;
  
  pubvel = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  pubservocam = n.advertise<std_msgs::Int16>("servo_cam", 1000);
  pubservohand = n.advertise<std_msgs::Int16>("servo_hand", 1000);
  
  ros::Subscriber sub = n.subscribe("joy_orig", 1000, Callback);
  
  ros::spin();
  return 0;
}