# coding=utf-8
from utils import *
import time

task_list = [[-4.075003147, 3.399998665, 8.425001144],
             [-4.075003147, 0, 8.425001144],
             [-4.075003147, 0],
             [-4.075003147, -8],
             [4, -8],
             [4, 0],
             [-4, 0]]
now_index = 0
start_time = 0


def arrive_now_target():
    distance = distance_between_drone_and_target()
    print('now distance = ', distance)
    now_time = time.time()
    return distance < 0.1 or now_time - start_time > 100


def path_update():
    if arrive_now_target():
        global now_index, start_time
        now_index += 1
        if now_index < len(task_list):
            set_target_position(task_list[now_index])
        start_time = time.time()

