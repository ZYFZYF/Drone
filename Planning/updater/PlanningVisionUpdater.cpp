#include <iostream>
#include "LandingVisionUpdater.h"
using namespace std;
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int clientID;

LandingVisionUpdater::LandingVisionUpdater(int client_id): LandingUpdater(Config::Instance()->getIntParam("LandingVisionUpdater", "TIME_STEP"), client_id)
{
    clientID=client_id;
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void LandingVisionUpdater::update()
{
    simxInt camera;
    simxGetObjectHandle(clientID, "zed_vision0", &camera, simx_opmode_blocking);
    simxInt resolution[2];
    simxUChar * image=0;
    namedWindow("opencv test", CV_WINDOW_AUTOSIZE);

    while(true){
        //Sleep(1000);
        //simxSetJointTargetVelocity(clientID, leftmotor, -time*0.02, simx_opmode_oneshot);
        //simxSetJointTargetVelocity(clientID, rightmotor, -time*0.03, simx_opmode_oneshot);

        int ret = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_oneshot);
        if (ret != simx_return_ok) {
            continue;
        }
        Mat channel(resolution[1], resolution[0], CV_8UC3, image);
        //读回来的图像数据是垂直翻转的,问题应该是在cvMat 和 v-rep 垂直坐标轴的方向相反,flip一下就正常了
        flip(channel, channel, 0);
        //读回来的图像数据时rgb通道分布的，而cvMat 默认bgr
        Mat gray;
        cvtColor(channel, gray, cv::COLOR_RGB2GRAY);
        vector<Vec3f> circles;
        HoughCircles(gray,circles,CV_HOUGH_GRADIENT,1,120,100,100,0,0);
        cout<<circles[0][0]<<circles[0][1]<<circles[0][2]<<endl;
//        vector<int> colorVec;
//        colorVec.push_back(channel.at<uchar>(0,0));
//        colorVec.push_back(channel.at<uchar>(0,1));
//        colorVec.push_back(channel.at<uchar>(0,2));


    }
}