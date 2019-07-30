# coding=utf-8
from utils import *
import time
import numpy as np
task_list = [[0,-4, 3.5, 8.5],
             [0,-4, 0, 8.5],
             [0,-4, 0],
             [90,-4, -9],
             [90,10, -9],
             [90,10, 0],
             [90,-4, 0]]

now_index = 0
start_time = 0


def arrive_now_target():
    distance = distance_between_drone_and_target()
    res, vel, _ = vrep.simxGetObjectVelocity(clientID,base,vrep.simx_opmode_blocking)
    vel_norm = np.linalg.norm(vel)
    print('now distance = ', round(distance,2),'\tvel =  ',round(vel_norm,2))
    now_time = time.time()
    return distance < 0.6 and vel_norm < 0.8


def path_update():
    if arrive_now_target():
        global now_index, start_time
        now_index += 1
        if now_index == len(task_list):
            now_index = 3
        set_target_position(task_list[now_index])
        start_time = time.time()

