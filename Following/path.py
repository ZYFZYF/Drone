# coding=utf-8
from utils import *
import time
import numpy as np
from test_follow import recognize

task_list = [[0, -4, 3.5, 8.5],
             [0, -4, 0, 8.5],
             [0, -4, 0],
             [90, -4, -9],
             [90, 10, -9],
             [90, 10, 0],
             [90, -4, 0]]

now_index = 0
last_time_fount_people = time.time()
is_ever_found_people = False


def arrive_now_target():
    distance = distance_between_drone_and_target()
    res, vel, _ = vrep.simxGetObjectVelocity(clientID, base, vrep.simx_opmode_blocking)
    vel_norm = np.linalg.norm(vel)
    print('now distance = ', round(distance, 2), '\tvel =  ', round(vel_norm, 2))
    return distance < 0.1


def path_update():
    # 识别成功的情况下不作任何处理
    global is_ever_found_people
    if recognize:
        is_ever_found_people = True
        return
    # 若不曾发现过人或者距离上一次发现人已经过了一段时间则照之前规划的路径转圈
    if not is_ever_found_people or time.time() - last_time_fount_people > 20:
        global now_index
        set_target_position(task_list[now_index])
        if arrive_now_target():
            now_index += 1
            if now_index == len(task_list):
                now_index = 3
    else:
        rotate_drone(1)

