# coding=utf-8
from utils import *
from path import path_update
from facerecognition.contour_detection import *
from facerecognition.recognition import *
import time
from matplotlib import pyplot as plt

def rec_image(img):
    mask=color_mask(img)
    contours=find_contours(mask)
    faces, boxes=perspective_transformation(img, contours)
    for i, face in enumerate(faces):
        # plt.imshow(face)
        # plt.savefig('output/%d.png'%i)
        print(recogize_portrait(face))
        print(get_person_color(img, boxes[i]))

if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    # vrep.simxSetObjectOrientation(clientID,target,base,{0,0,math.radians(90)},vrep.simx_opmode_oneshot)
    # vrep.simxSetObjectOrientation(clientID,sub_target,target,{0,0,0},vrep.simx_opmode_oneshot)
    try:
        # for i in range(9):
        #     rotate_drone(10)
        #     _, ret = vrep.simxGetObjectOrientation(clientID, target, -1, vrep.simx_opmode_blocking)
        #     print(ret)
        #     time.sleep(0.5)
        while True:
            path_update()
    except KeyboardInterrupt:
        pass
    finally:
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
        vrep.simxFinish(clientID)

# img=read_rgb_img('/home/eric/Work/Drone/Following/facerecognition/45dgrees-a1.png')
# rec_image(img)
