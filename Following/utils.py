# coding=utf-8
import vrep
import math
vrep.simxFinish(-1)
clientID = vrep.simxStart('127.0.0.1', 19997, True, True, 5000, 5)  # Connect to V-REP
_, drone = vrep.simxGetObjectHandle(clientID, 'drone_zed', vrep.simx_opmode_blocking)
_, target = vrep.simxGetObjectHandle(clientID, 'Quadricopter_target', vrep.simx_opmode_blocking)


def rotateDrone(angel):
    vrep.simxSetObjectOrientation(clientID, target, target, [0, 0, math.radians(angel)], vrep.simx_opmode_oneshot)


def rotateDroneTo(angel):
    vrep.simxSetObjectOrientation(clientID, target, -1, [0, 0, math.radians(angel)], vrep.simx_opmode_oneshot)
