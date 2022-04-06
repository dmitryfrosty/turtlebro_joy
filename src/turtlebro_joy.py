#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist


rospy.init_node("turtlebro_joy")
pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)

def callback(msg):
    linear = cd(msg.axes[1], -1.0, 1.0, -0.2, 0.2)
    angular = cd(msg.axes[0], -1.0, 1.0, -1.5, 1.5)
    vel(linear, angular)

def cd(old, old_min, old_max, new_min, new_max):
    new = (((old - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min
    return(new)

def vel(velx, velz):
    pub_vel = Twist()
    pub_vel.linear.x = velx
    pub_vel.angular.z = velz
    pub.publish(pub_vel)

rospy.Subscriber("/joy_orig", Joy, callback)

rospy.spin()