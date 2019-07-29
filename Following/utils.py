# coding=utf-8
import vrep
import math
from PIL import Image as I
import array
import numpy as np
import logging

logging.getLogger().setLevel(logging.INFO)
vrep.simxFinish(-1)
clientID = vrep.simxStart('127.0.0.1', 19997, True, True, 5000, 5)
if clientID==-1:
    logging.error("Failed to connect to remote API Server")
    exit()
else:
    logging.info('Connected to remote API server')

_, drone = vrep.simxGetObjectHandle(clientID, 'drone_zed', vrep.simx_opmode_blocking)
_, target = vrep.simxGetObjectHandle(clientID, 'Quadricopter_target', vrep.simx_opmode_blocking)
_, v0 = vrep.simxGetObjectHandle(clientID, 'zed_vision0', vrep.simx_opmode_blocking)
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

default_height = 2


def calc_angel_by_xy(x, y):
    return math.atan2(y, x) / math.pi * 180


def set_target_position(pos):
    if len(pos) < 3:
        pos.append(default_height)
    _, now_pos = vrep.simxGetObjectPosition(clientID, drone, -1, vrep.simx_opmode_blocking)
    delta_x = pos[0] - now_pos[0]
    delta_y = pos[1] - now_pos[1]
    rotate_drone_to(calc_angel_by_xy(delta_x, delta_y))
    vrep.simxSetObjectPosition(clientID=clientID,
                               objectHandle=target,
                               relativeToObjectHandle=-1,
                               position=pos,
                               operationMode=vrep.simx_opmode_oneshot)


def rotate_drone(angel):
    vrep.simxSetObjectOrientation(clientID=clientID,
                                  objectHandle=target,
                                  relativeToObjectHandle=target,
                                  eulerAngles=[0, 0, math.radians(angel)],
                                  operationMode=vrep.simx_opmode_oneshot)


def rotate_drone_to(angel):
    vrep.simxSetObjectOrientation(clientID=clientID,
                                  objectHandle=target,
                                  relativeToObjectHandle=-1,
                                  eulerAngles=[0, 0, math.radians(angel)],
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
    print(calc_angel_by_xy(0.1, 0))
    print(calc_angel_by_xy(0, 0.1))
    print(calc_angel_by_xy(-0.1, 0))
    print(calc_angel_by_xy(0, -0.1))

def disconnect():
    # vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
    vrep.simxFinish(clientID)
