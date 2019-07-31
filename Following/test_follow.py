# coding=utf-8
from utils import *
from facerecognition.contour_detection import *
from facerecognition.recognition import *
import time
import math
from matplotlib import pyplot as plt
size=0
recognize=False
position=[0,0]
target_people=6
color=0
def rec_image(img_rgb):
    global position,recognize,target_people,color,size
    mask=color_mask(img_rgb)
    contours=find_contours(mask)
    faces, boxes=perspective_transformation(img, contours)
    # faces为识别出脸的结果，识别失败为-1
    for i, face in enumerate(faces):
        people_id=recogize_portrait(face)
        if people_id==target_people:
            print('%d people=%d box=%s'%(i, people_id, boxes[i]))
            color=get_person_color(img, boxes[i], i)
            size=boxes[i][0,1]-boxes[i][1,1]
            position[0]=(boxes[i][0,0]+boxes[i][2,0])/2
            position[1]=(boxes[i][0,1]+boxes[i][2,1])/2+size
            recognize=True
            break
    if recognize==True:
        distance=(180/size-2)/2
        drone_pos=get_drone_position()
        drone_angle=get_drone_angle()[2]
        angle=math.atan((position[0]-640)*1.75/1280)
        if color==which_color(img_rgb[position[1].astype(int)-5:position[1].astype(int)+5,position[0].astype(int)-5:position[0].astype(int)+5]):           
            set_target_position([angle,drone_pos[0]+distance*math.cos(drone_angle+angle),drone_pos[1]+distance*math.sin(drone_angle+angle),3])
        else:
            recogize_color=False
            for i in range(3):
                for j in range(3):
                    if color==which_color(img_rgb[position[1].astype(int)-10+10*i-5:position[1].astype(int)-10+10*i+5,position[0].astype(int)-10+10*j-5:position[0].astype(int)-10+10*j+5]):
                        position[0]=position[0]-10+10*j
                        position[1]=position[1]-10+10*i
                        recogize_color=True
                        break
                if recogize_color:
                    break
            if recogize_color:
                angle=math.atan((position[0]-640)*1.75/1280)
                set_target_position([angle,drone_pos[0]+distance*math.cos(drone_angle+angle),drone_pos[1]+distance*math.sin(drone_angle+angle),3])
            else:
                recognize=False
if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    try:
        while True:
            img = get_sensor_image(v0)
            rec_image(img)
            # path_update()
    except KeyboardInterrupt:
        pass
    finally:
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
        vrep.simxFinish(clientID)
