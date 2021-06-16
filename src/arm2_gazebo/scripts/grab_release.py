#!/usr/bin/env python

from __future__ import print_function

from arm_gazebo.srv import Grab, GrabResponse
import rospy

def handle_req(req):
    if(req.grab):#will be 1 for grab and 0 for release
        #set angles to the end effector 
        pass
    else:
        #set angles to the end effector
        pass
    return GrabResponse(req.grab)

def grabber_server():
    rospy.init_node('grabber_server')
    s = rospy.Service('grabber_server', Grab, handle_req)
    print("Ready to grab or release")
    rospy.spin()

if __name__ == "__main__":
    grabber_server()