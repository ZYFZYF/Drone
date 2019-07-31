# coding=utf-8
from utils import *
from facerecognition.contour_detection import *
from facerecognition.recognition import *
import math
from matplotlib import pyplot as plt
size=[0,0]
recognize=False
rec_count=0
position=[0,0]
target_people=3
clothes_color=-1
pants_color=-1
def rec_image(img_rgb):
    global position,recognize,target_people,clothes_color,pants_color,size,rec_count
    mask=color_mask(img_rgb)
    contours=find_contours(mask)
    faces, boxes=perspective_transformation(img, contours)
    # faces为识别出脸的结果，识别失败为-1
    for i, face in enumerate(faces):
        people_id=recogize_portrait(face)
        if people_id==target_people:
            _position=[0,0]
            _size=[0,0]
            _size[0]=(boxes[i][0,0]-boxes[i][1,0]).astype(int)
            _size[1]=(boxes[i][0,1]-boxes[i][1,1]).astype(int)
            _position[0]=((boxes[i][0,0]+boxes[i][2,0])/2).astype(int)
            _position[1]=((boxes[i][0,1]+boxes[i][2,1])/2).astype(int)
            c_color=get_clothes_color(img_rgb, _position,_size, i)
            p_color=get_pants_color(img_rgb, _position,_size, i)
            if (clothes_color==-1 and pants_color==-1) or (c_color==clothes_color and p_color==pants_color):
                print('%d people=%d box=%s'%(i, people_id, boxes[i]))
                print("color: "+str(c_color)+"  "+str(p_color)) 
                position=_position
                size=_size
                recognize=True
                clothes_color=c_color
                pants_color=p_color
                print("size: "+str(size))
                break
    if recognize==True:
        distance=(180/math.sqrt(size[0]*size[0]+size[1]*size[1])-2)/2
        drone_pos=get_drone_position()
        drone_angle=get_drone_angle()[2]
        angle=math.atan((position[0]-640)*1.75/1280)
        if clothes_color==get_clothes_color(img_rgb, position,size, 0) and pants_color==get_pants_color(img_rgb, position,size, 0):   
            print(get_clothes_color(img_rgb, position,size, 0),get_pants_color(img_rgb, position,size, 0))     
            print("exactly recognized")
            set_target_position([angle,drone_pos[0]+distance*math.cos(drone_angle+angle),drone_pos[1]+distance*math.sin(drone_angle+angle),3])
        else:
            _position=find_target(img_rgb,clothes_color)
            if not _position[0]==0:
                print("found target")
                position=_position
                angle=math.atan((position[0]-640)*1.75/1280)
                set_target_position([angle,drone_pos[0]+distance*math.cos(drone_angle+angle),drone_pos[1]+distance*math.sin(drone_angle+angle),3])
            else:
                rec_count+=1
                if rec_count>=10:
                    recognize=False
if __name__ == '__main__':
    assert drone != 0
    assert target != 0
    vrep.simxStartSimulation(clientID, vrep.simx_opmode_blocking)
    try:
        while True:
            img = get_sensor_image(v0)
            plt.imsave('img',img)
            rec_image(img)
            # path_update()
    except KeyboardInterrupt:
        pass
    finally:
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
        vrep.simxFinish(clientID)
