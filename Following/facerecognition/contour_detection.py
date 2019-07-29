import numpy as np
import cv2
from matplotlib import pyplot as plt
import logging

color_ranges=[]
# red
# color.append([np.asarray([170, 110, 110]), np.asarray([210, 140, 140])])
color_ranges.append([np.asarray([0, 80, 150]), np.asarray([5, 100, 220])])
# green
# color.append([np.asarray([122, 162, 127]), np.asarray([152, 202, 157])])
color_ranges.append([np.asarray([60, 60, 160]), np.asarray([80, 80, 230])])
# blue
# color.append([np.asarray([110, 130, 170]), np.asarray([137, 159, 202])])
color_ranges.append([np.asarray([100, 77, 160]), np.asarray([120, 97, 200])])
# deep grey
# color.append([np.asarray([95, 95, 95]), np.asarray([120, 120, 120])])
color_ranges.append([np.asarray([0, 0, 95]), np.asarray([0, 0, 120])])
# shadow grey
# color.append([np.asarray([156, 156, 156]), np.asarray([176, 176, 176])])
color_ranges.append([np.asarray([0, 0, 150]), np.asarray([0, 0, 200])])
id_to_color=('red','green','blue','deep grey','shadow grey')


def color_mask(img):
    # mask=np.zeros(img.shape[:2],dtype='uint8')
    # for x,row in enumerate(img):
    #     for y, p in enumerate(row):
    #         if p[0]<70:
    #             mask[x,y]=255
    flag, thresh = cv2.threshold(img[:,:,0], 70, 255, cv2.THRESH_BINARY_INV)
    return thresh


def find_contours(mask):
    # Prepocess
    gray = mask
    blur = cv2.GaussianBlur(gray,(1,1),1000)
    flag, thresh = cv2.threshold(blur, 120, 255, cv2.THRESH_BINARY)

    # Find contours
    contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)

    # Select long perimeters only
    listindex=[i for i in range(len(contours)) if hierarchy[0,i,3]==-1 and cv2.contourArea(contours[i])>10]
    contours=[contours[i] for i in listindex]
    logging.info('INFO: # potential faces = %d'%len(listindex))
    return contours


def perspective_transformation(img, contours):
    num_faces=len(contours)
    warp = [None for i in range(num_faces)]
    bounding_parallelogram_boxes=[None for i in range(len(contours))]
    output_size=(120,120)
    for i in range(num_faces):
        contour = contours[i]
        peri = cv2.arcLength(contour,True)
        for exp_threshold in range(0,20):
            approx = cv2.approxPolyDP(contour,0.04*peri*2**(exp_threshold/2),True)
            if len(approx)==4:
                break
            elif len(approx)<4:
                rect = cv2.minAreaRect(contours[i])
                approx = [cv2.boxPoints(rect)]
                break

        # extract points from nested list
        approx = np.array([item for sublist in approx for item in sublist],np.float32)

        # pair bouding points with target points
        approx=sorted(approx.tolist(),key=lambda x:x[1])
        top_points=sorted(approx[:2])
        bottom_points=sorted(approx[-2:])
        approx=np.array((bottom_points[0],*top_points,bottom_points[1]),np.float32)

        h = np.array([ [0,output_size[1]],[0,0],[output_size[0],0],
            [output_size[0],output_size[1]] ], np.float32)
        transform = cv2.getPerspectiveTransform(approx,h)
        warp[i] = cv2.warpPerspective(img,transform,output_size)
        bounding_parallelogram_boxes[i]=approx
    return warp, bounding_parallelogram_boxes

def read_rgb_img(filename):
    img = cv2.imread(filename)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    return img


def which_color(image_block_rgb):
    img_hsv = cv2.cvtColor(image_block_rgb, cv2.COLOR_RGB2HSV)
    color_cnt=np.zeros((len(color_ranges,)))
    for i, color_range in enumerate(color_ranges):
        mask = cv2.inRange(img_hsv, color_range[0], color_range[1])
        color_cnt[i]=cv2.countNonZero(mask)
    color_id = color_cnt.argmax()
    if color_cnt[color_id]<=1:
        return -1
    return color_id


def get_person_color(img_rgb, bounding_parallelogram_box):
    para=bounding_parallelogram_box.astype(int)
    x_min=para[:,0].min()
    x_max=para[:,0].max()
    y_min=para[:,1].min()
    y_max=para[:,1].max()
    y_offset=y_max-y_min
    color_id = which_color(img_rgb[y_min+y_offset:y_max+y_offset,x_min:x_max])
    return color_id


# img=read_rgb_img('45dgrees-a1.png')
# contours=find_contours(color_mask(img))
# faces=perspective_transformation(img, contours)
