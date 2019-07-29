# coding=utf-8
# from utils import *
from facerecognition.contour_detection import *
from facerecognition.recognition import *
import time
from matplotlib import pyplot as plt

# if __name__ == '__main__':
#     assert drone != 0
#     assert target != 0
#     # vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
#     try:
#         for i in range(9):
#             rotateDrone(10)
#             _, ret = vrep.simxGetObjectOrientation(clientID, target, -1, vrep.simx_opmode_blocking)
#             print(ret)
#             time.sleep(0.5)
#     except KeyboardInterrupt:
#         pass
#     finally:
#         disconnect()

def rec_image(img_rgb):
    mask=color_mask(img)
    contours=find_contours(mask)
    faces=perspective_transformation(img, contours)
    for i, face in enumerate(faces):
        # plt.imshow(face)
        # plt.savefig('output/%d.png'%i)
        print(recogize_portrait(face))

img=read_rgb_img('/home/eric/Work/Drone/Following/facerecognition/45dgrees-a1.png')
