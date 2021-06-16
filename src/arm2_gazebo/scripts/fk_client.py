#!/usr/bin/env python
import sys
import rospy
from arm2_gazebo.srv import FK,FKResponse

def handle_inputs(angles,joint_length):
    rospy.wait_for_service('fk')
    try:
        fk_server = rospy.ServiceProxy('fk', FK)
        resp1 = fk_server(angles,joint_length)
        return resp1.actuator_pose
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("wrong number of arguments enter 4 arguments!!")
    else:
        given_angles =[]
        for a in sys.argv[1:]:
            given_angles.append(float(a))
        print(given_angles)
        joint_length = [0.15,2,1,0.5,0.1]
        print(handle_inputs(given_angles,joint_length))