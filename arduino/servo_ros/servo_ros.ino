#include "ros.h"
#include "std_msgs/Int16.h"
#include <Servo.h>

Servo servo_cam;

class NewHardware : public ArduinoHardware    //для работы связи ардуино и разбери на роботе
{
  public:
  NewHardware():ArduinoHardware(&Serial1, 115200){};
};
ros::NodeHandle_<NewHardware>  nh;

void messageCb(const std_msgs::Int16 & toggle_msg){ 
  servo_cam.write(toggle_msg.data);
}

ros::Subscriber<std_msgs::Int16> sub("servo_cam", &messageCb ); 

void setup(){
  servo_cam.attach(45);
  nh.initNode();     //создаём ноду 
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();  //необходимо для работы топика
}
