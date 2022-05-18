#include "ros.h"
#include "std_msgs/Int16.h"
#include <Servo.h>

Servo servo_cam;
Servo servo_hand;

class NewHardware : public ArduinoHardware    //для работы связи ардуино и разбери на роботе
{
  public:
  NewHardware():ArduinoHardware(&Serial1, 115200){};
};
ros::NodeHandle_<NewHardware>  nh;

void servocam(const std_msgs::Int16 & toggle_msg){ 
  servo_cam.write(toggle_msg.data);
}

void servohand(const std_msgs::Int16 & toggle_msg){ 
  servo_hand.write(toggle_msg.data);
}

ros::Subscriber<std_msgs::Int16> subcam("servo_cam", &servocam );
ros::Subscriber<std_msgs::Int16> subhand("servo_hand", &servohand );

void setup(){
  servo_cam.attach(45);
  servo_hand.attach(46);
  nh.initNode();     //создаём ноду 
  nh.subscribe(subcam);
  nh.subscribe(subhand);
}

void loop(){
  nh.spinOnce();  //необходимо для работы топика
}