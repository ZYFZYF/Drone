# coding=utf-8
from utils import *
import time

if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    try:
        for i in range(9):
            rotateDrone(10)
            _, ret = vrep.simxGetObjectOrientation(clientID, target, -1, vrep.simx_opmode_blocking)
            print(ret)
            time.sleep(0.5)
    except KeyboardInterrupt:
        pass
    finally:
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
        vrep.simxFinish(clientID)
