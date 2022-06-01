#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class robot():
    def __init__(self):
        rospy.init_node("robotino_joy")
        self.pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)
        rospy.Subscriber("/joy_orig", Joy, self.callback)
        self.r = rospy.Rate(20)
        self.axes_x = 0
        self.axes_y = 0

    def converting(self, old, old_min, old_max, new_min, new_max):
        new = (((old - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min
        return(new)
    
    def callback(self, msg):
        self.axes_x = msg.axes[1]
        self.axes_y = msg.axes[0]

    def work(self):
        pub_vel = Twist()
        pub_vel.linear.x = self.converting(self.axes_x, -1.0, 1.0, -2.5, 2.5)
        pub_vel.angular.z = self.converting(self.axes_y, -1.0, 1.0, -3.0, 3.0)
        self.pub.publish(pub_vel)
        self.r.sleep()

a = robot()

while not rospy.is_shutdown():
    a.work()    