# coding=utf-8
import vrep
import math
from PIL import Image as I
import array
import numpy as np
import logging

logging.getLogger().setLevel(logging.INFO)
vrep.simxFinish(-1)
clientID = vrep.simxStart('127.0.0.1', 19999, True, True, 5000, 5)
if clientID==-1:
    logging.error("Failed to connect to remote API Server")
    exit()
else:
    logging.info('Connected to remote API server')

_, drone = vrep.simxGetObjectHandle(clientID, 'drone_zed', vrep.simx_opmode_blocking)
_, target = vrep.simxGetObjectHandle(clientID, 'Quadricopter_target', vrep.simx_opmode_blocking)
_, v0 = vrep.simxGetObjectHandle(clientID, 'zed_vision0', vrep.simx_opmode_oneshot_wait)
# _, v1 = vrep.simxGetObjectHandle(clientID, 'zed_vision1', vrep.simx_opmode_oneshot_wait)
# vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)

def change_color_and_resize(image):
    for i in range(len(image)):
        image[i]=(image[i]+256)%256
    image_buffer = I.frombuffer("RGB", (resolution[0],resolution[1]), bytes(image), "raw", "RGB", 0, 1).rotate(180)
    return image_buffer

def get_sensor_image(vision_sensor):
    cnt=0
    while (vrep.simxGetConnectionId(clientID) != -1):
        err, resolution, image = vrep.simxGetVisionSensorImage(clientID, vision_sensor, 0, vrep.simx_opmode_buffer)
        cnt+=1
        if err == vrep.simx_return_ok:
            image_buffer = change_color_and_resize(image)
            return image_buffer
        if cnt % 2048 ==0:
            logging.warning('get_sensor_image retry %d tiems'%cnt)
            # image_buffer.save("a%d.png"%(cnt,))


def rotateDrone(angel):
    vrep.simxSetObjectOrientation(clientID, target, target, [0, 0, math.radians(angel)], vrep.simx_opmode_oneshot)


def rotateDroneTo(angel):
    vrep.simxSetObjectOrientation(clientID, target, -1, [0, 0, math.radians(angel)], vrep.simx_opmode_oneshot)


def disconnect():
    # vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
    vrep.simxFinish(clientID)
