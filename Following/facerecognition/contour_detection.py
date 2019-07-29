import numpy as np
import cv2
from matplotlib import pyplot as plt
import logging


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
    return warp

def read_rgb_img(filename):
    img = cv2.imread(filename)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    return img

# img=read_rgb_img('45dgrees-a1.png')
# contours=find_contours(color_mask(img))
# faces=perspective_transformation(img, contours)
