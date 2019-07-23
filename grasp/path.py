# Make sure to have the server side running in V-REP:
# in a child script of a V-REP scene, add following command
# to be executed just once, at simulation start:
#
# simRemoteApi.start(19999)
#
# then start simulation, and run this program.
#
# IMPORTANT: for each successful call to simxStart, there
# should be a corresponding call to simxFinish at the end!
import numpy as np
import vrep
import time
from math import *


def run(path):
    index = 0
    for p in ps:
        index += 1
        vrep.simxSetObjectPosition(
            clientID, q_target, -1, p, vrep.simx_opmode_blocking)
        res, end_pos = vrep.simxGetObjectPosition(
            clientID, base, -1, vrep.simx_opmode_blocking)
        d_pos = [end_pos[i] - target_position[i] for i in range(3)]
        while np.linalg.norm(d_pos) > 0.1:
            print(np.linalg.norm(d_pos))
            time.sleep(0.5)
            res, end_pos = vrep.simxGetObjectPosition(
                clientID, base, -1, vrep.simx_opmode_blocking)
            d_pos = [end_pos[i] - target_position[i] for i in range(3)]
        print("到达目标点", index, p)


vrep.simxFinish(-1)  # just in case, close all opened connections
clientID = vrep.simxStart('127.0.0.1', 19997, True,
                          True, 5000, 5)  # Connect to V-REP
res, target = vrep.simxGetObjectHandle(
    clientID, "Target", vrep.simx_opmode_blocking)
res, q_target = vrep.simxGetObjectHandle(
    clientID, "Quadricopter_target", vrep.simx_opmode_blocking)
res, base = vrep.simxGetObjectHandle(
    clientID, "Quadricopter_base", vrep.simx_opmode_blocking)
if clientID != -1:
    print('Connected to remote API server')
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    res, target_position = vrep.simxGetObjectPosition(
        clientID, target, -1, vrep.simx_opmode_blocking)
    path = []
    point = target_position
    point[3] += 0.5
    path.append(point)
    point = target_position
    point[3] += 0.21
    path.append(point)
    run(path)

    vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
    vrep.simxFinish(clientID)
else:
    print('Failed connecting to remote API server')
print('Program ended')
