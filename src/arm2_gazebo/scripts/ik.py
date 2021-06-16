import numpy as np
from arm2_gazebo.srv import IK,IKResponse
import tinyik as myIk
import rospy

def handle_inputs(req): #req.actuator_pose. res.new_angles
    arm = myIk.Actuator([
        "z", [0,0,0.15],
        "x", [0,0,2],
        "x", [0,0,1.0],
        "x", [0,0,0.5],
        "x", [0,0,0.1],
    ])
    arm.ee = req.actuator_pose
    res.new_angles = arm.angles
    print(arm.angles)
    return IKResponse(res.new_angles)


def ik_server():
    print("IK Server is running:...")
    rospy.init_node('ik_server')
    s = rospy.Service('ik', IK, handle_inputs)
    print("Ready to ik.")
    rospy.spin()

if __main__ == "__main__":
    ik_server()
    