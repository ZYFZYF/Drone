import numpy as np
import vrep
import time
from math import *
delta = 0.001

vrep.simxFinish(-1) # just in case, close all opened connections
clientID=vrep.simxStart('127.0.0.1',19997,True,True,5000,5) # Connect to V-REP
if clientID!=-1:
    print ('Connected to remote API server')

    ps = np.arange(0.1,0.2,0.01)
    res, base = vrep.simxGetObjectHandle(clientID,"Quadricopter_base1",vrep.simx_opmode_blocking)
    res, target = vrep.simxGetObjectHandle(clientID,"Quadricopter_target1",vrep.simx_opmode_blocking)
    res, init_position = vrep.simxGetObjectPosition(clientID,target, -1,vrep.simx_opmode_blocking)
    # Now retrieve streaming data (i.e. in a non-blocking fashion):
    for p in ps:
        vrep.simxSetFloatSignal(clientID,"p",p,vrep.simx_opmode_blocking)
        print(p,":")
        vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
        startTime=time.time()
        while time.time()-startTime < 10:
            res, end_position = vrep.simxGetObjectPosition(clientID,base, -1,vrep.simx_opmode_blocking)
            res, lv, rv = vrep.simxGetObjectVelocity(clientID,base,vrep.simx_opmode_blocking)
            d_position = np.array(end_position) - np.array(init_position)
            if np.linalg.norm(d_position) < 0.01:
                v = np.linalg.norm(lv)
            elif np.linalg.norm(lv) < 0.01:
                pos = np.linalg.norm(d_position)
        print("diff pos: ",np.linalg.norm(d_position))
        print("lv : ",np.linalg.norm(lv))
        vrep.simxStopSimulation(clientID,vrep.simx_opmode_blocking)
        time.sleep(0.5)



    # Now close the connection to V-REP:
    vrep.simxFinish(clientID)
else:
    print ('Failed connecting to remote API server')
print ('Program ended')
