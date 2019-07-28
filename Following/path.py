# coding=utf-8
from utils import *

task_list = [[-4.075003147, 3.399998665, 8.425001144],
             [-4.075003147, 0, 8.425001144],
             [-4.075003147, 0]]
now_index = 0


def arrive_now_target():
    distance = distance_between_drone_and_target()
    print('now distance = ', distance)
    return distance < 0.1


def path_update():
    if arrive_now_target():
        global now_index
        now_index += 1
        set_target_position(task_list[now_index])

