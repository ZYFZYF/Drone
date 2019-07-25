# coding=utf-8
from utils import *
import time

if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    for i in range(9):
        rotateDrone(10)
        _, ret = vrep.simxGetObjectOrientation(clientID, target, -1, vrep.simx_opmode_blocking)
        print(ret)
        time.sleep(0.5)

    # Now close the connection to V-REP:
    vrep.simxStopSimulation(clientID, vrep.simx_opmode_oneshot)
    vrep.simxFinish(clientID)
