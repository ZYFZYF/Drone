
# coding: utf-8

# In[179]:


import numpy as np
import cv2
from matplotlib import pyplot as plt
from mpl_toolkits.axes_grid1 import ImageGrid
import math

# img = cv2.imread('a6.png')
img = cv2.imread('45dgrees-a1.png')

img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
plt.imshow(img)
plt.show()


# In[180]:


mask=np.zeros(img.shape[:2],dtype='uint8')
print(mask.shape)
for x,row in enumerate(img):
    for y, p in enumerate(row):
        if p[0]<70:
            mask[x,y]=255
plt.figure(figsize=(20,10))
plt.imshow(mask)
plt.show()


# In[181]:


# Prepocess
# gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
import random
gray = mask
blur = cv2.GaussianBlur(gray,(1,1),1000)
flag, thresh = cv2.threshold(blur, 120, 255, cv2.THRESH_BINARY)

# Find contours
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
# contours = sorted(contours, key=cv2.contourArea,reverse=True) 

# Select long perimeters only
# perimeters = [cv2.arcLength(contours[i],True) for i in range(len(contours))]
# listindex=[i for i in range(15) if perimeters[i]>perimeters[0]/2 and contourArea(contours[i])>0.5]
listindex=[i for i in range(len(contours)) if hierarchy[0,i,3]==-1 and cv2.contourArea(contours[i])>10]
numcards=len(listindex)
print(len(listindex))
contours=[contours[i] for i in listindex]

# Show image
imgcont = img.copy()
[cv2.drawContours(imgcont, [contours[i]], 0, (random.randint(0,255),random.randint(0,255),random.randint(0,255)), 5) for i in range(numcards)]
# [cv2.drawContours(imgcont, [contours[i]], 0, (0,255,0), 5) for i in listindex]
plt.figure(figsize=(20,10))
plt.imshow(imgcont)
plt.show()


# In[182]:


# contours = sorted(contours, key=cv2.contourArea,reverse=True) 
# # Select long perimeters only
# perimeters = [cv2.arcLength(contours[i],True) for i in range(len(contours))]
# listindex=[i for i in range(len(contours)) if perimeters[i]>perimeters[0]/2]
# numcards=len(listindex)
# print(len(contours))
# print([cv2.contourArea(c) for c in contours])


# In[183]:


warp = [None for i in range(numcards)]
warp_rect = [None for i in range(numcards)]
for i in range(numcards):
    card = contours[i]
    peri = cv2.arcLength(card,True)
#     approx = cv2.approxPolyDP(card,0.04*peri,True)
    print('===%d==='%i)
    for exp_threshold in range(0,20):
        approx = cv2.approxPolyDP(card,0.04*peri*2**(exp_threshold/2),True)
        print(len(approx))
        if len(approx)==4:
            break
        elif len(approx)<4:
            rect = cv2.minAreaRect(contours[i])
            approx = [cv2.boxPoints(rect)]
            break
            
    # extract points from nested list
    approx = np.array([item for sublist in approx for item in sublist],np.float32)

    rect = cv2.minAreaRect(contours[i])
    # rotated rectangle
    if rect[2]<-45:
        rect=(rect[0],(rect[1][1], rect[1][0]), rect[2]+90)
    r = cv2.boxPoints(rect)
#     pts1 = np.float32([rec[1], rec[2], rec[0], rec[3]])
    
    # pair bouding points with target points
#     print(approx, approx.shape)
    approx=sorted(approx.tolist(),key=lambda x:x[1])
    top_points=sorted(approx[:2])
    bottom_points=sorted(approx[-2:])
    approx=np.array((bottom_points[0],*top_points,bottom_points[1]),np.float32)
#     print(top_points, bottom_points)
#     print('i= ', i, approx)
    
    
    h = np.array([ [0,399],[0,0],[399,0],[399,399] ],np.float32)
    try:
        transform = cv2.getPerspectiveTransform(approx,h)
        warp[i] = cv2.warpPerspective(img,transform,(400,400))
    except Exception as e:
        print(i)
        print('approx=',len(approx))
#         print('rect ',rect)
#         print('r ',r)
        print('Error: %d %s'%(i,e))
        warp[i] = np.zeros((400,400))#cv2.warpPerspective(img,transform,(400,400))
        None
    transform = cv2.getPerspectiveTransform(r,h)
    warp_rect[i] = cv2.warpPerspective(img,transform,(400,400))
    
    # drawing for debug
    plt.scatter(approx[:,0], approx[:,1])
plt.imshow(img)
plt.show()

# Show perspective correction
fig = plt.figure(1, (20,20))
grid = ImageGrid(fig, 111, # similar to subplot(111)
                nrows_ncols = (6,4), # creates 2x2 grid of axes
                axes_pad=0.1, # pad between axes in inch.
                aspect=True, # do not force aspect='equal'
                )

for i in range(numcards):
    grid[i*2].imshow(warp[i]) # The AxesGrid object work as a list of axes.
    grid[i*2+1].imshow(warp_rect[i]) # The AxesGrid object work as a list of axes.
plt.show()



# In[194]:


# face recognition
import face_recognition

# Create arrays of known face encodings and their names
known_face_encodings = []
known_face_names = []
for i in range(1,7):
    data_image = face_recognition.load_image_file("/home/eric/Work/vregRobot/face_data/%d.png"%(i,))
    data_encoding = face_recognition.face_encodings(data_image)[0]
    known_face_encodings.append(data_encoding)
    known_face_names.append(str(i))

def recogize_portrait(portrait_rgb):
    rgb_frame=portrait_rgb
    face_locations = [(0, portrait_rgb.shape[1], portrait_rgb.shape[0], 0)]
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    # Loop through each face in this frame of video
    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        # See if the face is a match for the known face(s)
        matches = face_recognition.compare_faces(known_face_encodings, face_encoding)

        name = "Unknown"

        # If a match was found in known_face_encodings, just use the first one.
        # if True in matches:
        #     first_match_index = matches.index(True)
        #     name = known_face_names[first_match_index]

        # Or instead, use the known face with the smallest distance to the new face
        face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
        best_match_index = np.argmin(face_distances)
        if matches[best_match_index]:
            name = known_face_names[best_match_index]
        print(name)
        return name


# In[195]:


recognition_name=['']*20

for i in range(numcards):
    print('===num ', i)
    recognition_name[i*2]=recogize_portrait(warp[i])
    recognition_name[i*2+1]=recogize_portrait(warp_rect[i])


# In[209]:


# Show perspective correction with recoginition ID
fig = plt.figure(1, (20,20))

grid = ImageGrid(fig, 111, # similar to subplot(111)
                nrows_ncols = (5,4), # creates 2x2 grid of axes
                axes_pad=0.5, # pad between axes in inch.
                aspect=True, # do not force aspect='equal'
                )
# plt.title('45 degrees perspective face recoginition')

for i in range(numcards):
    grid[i*2].imshow(warp[i]) # The AxesGrid object work as a list of axes.
    grid[i*2].set_title(recognition_name[i*2])
    grid[i*2+1].imshow(warp_rect[i]) # The AxesGrid object work as a list of axes.
    grid[i*2+1].set_title(recognition_name[i*2+1])
plt.gca().set_facecolor((1,1,1))
plt.show()


# In[ ]:


# TODO: 改到py里面，以后人脸识别应该不会再动了。　可能考虑换人脸识别的模型
# 人的定位

