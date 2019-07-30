# coding=utf-8
from utils import *
from path import path_update
from facerecognition.contour_detection import *
from facerecognition.recognition import *
import time
from matplotlib import pyplot as plt
recognize=False
target_people=1
def rec_image(img_rgb):
    mask=color_mask(img_rgb)
    contours=find_contours(mask)
    faces, boxes=perspective_transformation(img, contours)
    # faces为识别出脸的结果，faces[i]可能为'Unknown'
    for i, face in enumerate(faces):
        # plt.imshow(face)
        # plt.savefig('output/%d.png'%i)
        people_id=recogize_portrait(face)
        people_color = get_person_color(img, boxes[i])
        print('people=%d box=%s'%(people_id, boxes[i]))
        if  people_id==target_people:
            return people_id, boxes, people_color
        # TODO: 根据人脸识别结果和衣服颜色确定跟踪目标
    return -1,-1,-1

if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    try:
        while True:
            img=get_sensor_image(v0)
            print(len(img))
            _id,boxes,color=rec_image(img)

            # path_update()
    except KeyboardInterrupt:
        pass
    finally:
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
        vrep.simxFinish(clientID)
