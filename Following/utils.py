# coding=utf-8
import vrep
import math
import numpy as np

vrep.simxFinish(-1)
clientID = vrep.simxStart('127.0.0.1', 19997, True, True, 5000, 5)  # Connect to V-REP
_, drone = vrep.simxGetObjectHandle(clientID, 'drone_zed', vrep.simx_opmode_blocking)
_, target = vrep.simxGetObjectHandle(clientID, 'Quadricopter_target', vrep.simx_opmode_blocking)

default_height = 3


def calc_angle_by_xy(x, y):
    return math.atan2(y, x) / math.pi * 180


def set_target_position(pos):
    if len(pos) < 3:
        pos.append(default_height)
    _, now_pos = vrep.simxGetObjectPosition(clientID, drone, -1, vrep.simx_opmode_blocking)
    delta_x = pos[0] - now_pos[0]
    delta_y = pos[1] - now_pos[1]
    rotate_drone_to(calc_angle_by_xy(delta_x, delta_y))
    vrep.simxSetObjectPosition(clientID=clientID,
                               objectHandle=target,
                               relativeToObjectHandle=-1,
                               position=pos,
                               operationMode=vrep.simx_opmode_oneshot)


def rotate_drone(angle):
    vrep.simxSetObjectOrientation(clientID=clientID,
                                  objectHandle=target,
                                  relativeToObjectHandle=target,
                                  eulerAngles=[0, 0, math.radians(angle)],
                                  operationMode=vrep.simx_opmode_oneshot)


def rotate_drone_to(angle):
    vrep.simxSetObjectOrientation(clientID=clientID,
                                  objectHandle=target,
                                  relativeToObjectHandle=-1,
                                  eulerAngles=[0, 0, math.radians(angle)],
                                  operationMode=vrep.simx_opmode_oneshot)


def get_drone_position():
    return get_position(drone)


def get_target_position():
    return get_position(target)


def get_position(handle):
    _, ret = vrep.simxGetObjectPosition(clientID=clientID,
                                        objectHandle=handle,
                                        relativeToObjectHandle=-1,
                                        operationMode=vrep.simx_opmode_blocking)
    return ret


def distance_between_drone_and_target():
    drone_pos = get_drone_position()
    target_pos = get_target_position()
    return np.linalg.norm(np.array([d1-d2 for d1, d2 in zip(drone_pos, target_pos)]))

if __name__ == '__main__':
    print(calc_angle_by_xy(0.1, 0))
    print(calc_angle_by_xy(0, 0.1))
    print(calc_angle_by_xy(-0.1, 0))
    print(calc_angle_by_xy(0, -0.1))
