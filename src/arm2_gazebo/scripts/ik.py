#!/usr/bin/env python
from arm2_gazebo.msg import setangles
import tinyik as myIk
import sys
from arm2_gazebo.srv import IK,IKResponse
import rospy

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

def go_talk(angles,state):
    pub = rospy.Publisher('angle_listner_topic', setangles, queue_size=10)
    rospy.init_node('end_efector_talker', anonymous=True)
    rate = rospy.Rate(30) # 10hz
    while not rospy.is_shutdown():
        e = setangles()
        e.state = state
        if state == 'G':  #g for go
            e.angle1 = to_deg(angles[0])
            e.angle2 = to_deg(angles[1])
            e.angle3 = to_deg(angles[2])
            e.angle4 = to_deg(angles[3])
        elif state == 'C':
            e.finger_finger_tip = 50 #c for catch
        elif state == 'R':
            e.finger_finger_tip = 10 #r for release
        
        # close the connection
        connections = pub.get_num_connections()
        if connections > 0:
            pub.publish(e)
            break
        rate.sleep()

def to_deg(angle):
    return (angle*180)/3.14

def handle_end_efactors(req):
    EE = req.actuator_pose
    print("<<")
    print(EE)
    print(">>")
    response = IKResponse()
    response.new_angles = handle_inputs(EE)
    print(response.new_angles)
    return response

if __name__ == "__main__":
    print("Service is running...")
    # Ik_server()
    print(sys.argv)
    if len(sys.argv) != 5:
        print("input wrong..more than need to be just 5 inputs")
    else:
        given_ee = []
        for e in sys.argv[1:-1]:
            given_ee.append(float(e))
        print(given_ee)
        angles = handle_inputs(given_ee)
        print(angles)
        go_talk(angles,sys.argv[-1])
    

# rosrun arm2_gazebo ik.py 0 -2.5 0.4 G
# rosrun arm2_gazebo ik.py 0 -2.5 0.4 C
# rosrun arm2_gazebo ik.py 1.4 -1.7 0.5 G
# rosrun arm2_gazebo ik.py 1.4 -1.7 0.5 R
# rosrun arm2_gazebo ik.py 1.4 -1.7 0.1 G
# rosrun arm2_gazebo ik.py 1.4 -1.7 0.9 G
