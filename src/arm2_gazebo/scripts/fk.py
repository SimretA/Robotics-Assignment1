import numpy as np
from arm2_gazebo.srv import FK,FKResponse
import rospy

def Rx(rad):
    return np.array([[1, 0, 0, 0], [0, np.cos(rad), -np.sin(rad), 0],
                    [0, np.sin(rad), np.cos(rad), 0], [0, 0, 0, 1]])


def Ry(rad):
    return np.array([[np.cos(rad), 0, np.sin(rad), 0], [0, 1, 0, 0],
                    [-np.sin(rad), 0, np.cos(rad), 0], [0, 0, 0, 1]])


def Rz(rad):
    return np.array([[np.cos(rad), -np.sin(rad), 0, 0], [np.sin(rad),
                    np.cos(rad), 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])


def Tz(d):
    return np.array([[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, d], [0, 0,
                    0, 1]])


def handle_inputs(req):  # req.joint_angles. req.joint_length
    M1 = Tz(req.joint_length[0])
    M2 = Rz(np.radians(req.joint_angles[0])).dot(Tz(req.joint_length[1]))
    M3 = Rx(np.radians(req.joint_angles[1])).dot(Tz(req.joint_length[2]))
    M4 = Rx(np.radians(req.joint_angles[2])).dot(Tz(req.joint_length[3]))
    M5 = Rx(np.radians(req.joint_angles[3])).dot(Tz(req.joint_length[4]))

    M = M1.dot(M2).dot(M3).dot(M4).dot(M5)
    print(M)
    return FKResponse([M[0:3], M[1:3], M[2:3]])


def fk_server():
    print('FK Server is running:...')
    rospy.init_node('fk_server')
    s = rospy.Service('fk', FK, handle_inputs)
    print('Ready to fk.')
    rospy.spin()


if __name__ == '__main__':
    fk_server()
