import numpy as np
def Rx(rad):
    return np.array([
        [1,0,0,0],
        [0,np.cos(rad), -np.sin(rad),0],
        [0, np.sin(rad),np.cos(rad),0],
        [0,0,0,1],
    ])

def Ry(rad):
    return np.array([
        [np.cos(rad),0,np.sin(rad),0],
        [0,1,0,0],
        [-np.sin(rad), 0, np.cos(rad), 0],
        [0,0,0,1],
    ])


def Rz(rad):
    return np.array([
        [np.cos(rad),-np.sin(rad),0, 0],
        [np.sin(rad), np.cos(rad), 0, 0],
        [0,0,1,0],
        [0,0,0,1],
    ])

def Tz(d):
    return np.array([
        [1,0,0,0],
        [0,1,0,0],
        [0,0,1,d],
        [0,0,0,1],
    ])