#!/usr/bin/env python
from arm2_gazebo.msg import setangles
import tinyik as myIk
import sys
import rospy

def callback(data):
    print("HERE: " + data)

def handle_inputs(ee): #req.actuator_pose. res.new_angles
    arm = myIk.Actuator([
        "z", [0,0,0.15],
        "x", [0,0,2],
        "x", [0,0,1.0],
        "x", [0,0,0.5],
        "x", [0,0,0.1],
    ])
    arm.ee = ee
    return arm.angles

def go_talk(angles):
    pub = rospy.Publisher('angle_listner_topic', setangles, queue_size=10)
    rospy.init_node('end_efector_talker', anonymous=True)
    rate = rospy.Rate(30) # 10hz
    fingerer = 10
    while not rospy.is_shutdown():
        e = setangles()
        e.angle1 = to_deg(angles[0])
        e.angle2 = to_deg(angles[1])
        e.angle3 = to_deg(angles[2])
        e.angle4 = to_deg(angles[3])
        e.finger_finger_tip = fingerer
        pub.publish(e)
        # rate.sleep()
        print("---")
        # rospy.spin()
        fingerer = 90
        e.finger_finger_tip = fingerer
        pub.publish(e)
        # source ./devel
        # rosrun arm2_gazebo ik.py 1 1 1

    

def to_deg(angle):
    return (angle*180)/3.14

if __name__ == "__main__":
    given_ee = []
    for e in sys.argv[1:]:
        given_ee.append(float(e))
    print(given_ee)
    angles = handle_inputs(given_ee)
    print(angles)
    go_talk(angles)
    
    