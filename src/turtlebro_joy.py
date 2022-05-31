#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

rospy.init_node("turtlebro_joy")
pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)

def callback(msg):
    pub_vel = Twist()
    pub_vel.linear.x = cd(msg.axes[1], -1.0, 1.0, -0.2, 0.2)
    pub_vel.angular.z = cd(msg.axes[0], -1.0, 1.0, -1.5, 1.5)
    pub.publish(pub_vel)

def cd(old, old_min, old_max, new_min, new_max):
    new = (((old - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min
    return(new)

rospy.Subscriber("/joy_orig", Joy, callback)

rospy.spin()