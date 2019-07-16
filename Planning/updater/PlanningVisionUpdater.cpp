#include <iostream>
#include "PlanningVisionUpdater.h"
#include "../../Common/config/Config.h"
using namespace std;
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int clientID;
int targetx;
int targety;
int circlex;
int circley;
PlanningVisionUpdater::PlanningVisionUpdater(int client_id): PlanningUpdater(Config::Instance()->getIntParam("PlanningVisionUpdater", "TIME_STEP"), client_id)
{
    clientID=client_id;
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void PlanningVisionUpdater::update() {
    simxInt camera;
    simxGetObjectHandle(clientID, "zed_vision0", &camera, simx_opmode_blocking);
    simxInt resolution[2];
    simxUChar *image = 0;
    namedWindow("opencv test", CV_WINDOW_AUTOSIZE);

    while (true) {
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
        GaussianBlur(gray, gray ,Size(9, 9), 2, 2);
        vector<Vec3f> circles;
        HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 10, 1000);
        if (circles.size() > 0) {
            circlex = circles[0][1];
            circley = circles[0][0];
            cout << "圆:  " << circlex << "  " << circley << endl;
        } else
            cout<<"没找到圆"<<endl;
//        cvtColor(channel, channel, cv::COLOR_RGB2BGR);
        int startx = -1, starty = -1;
        int finishx = 0, finishy = 0;
        for (int i = 0; i < channel.rows; i++)
            for (int j = 0; j < channel.cols; j++)
                if (channel.at<Vec3b>(i, j)[0] > 170 && channel.at<Vec3b>(i, j)[1] < 50 &&
                    channel.at<Vec3b>(i, j)[2] < 50) {
                    if (startx == -1) {
                        startx = i;
                        starty = j;
                    }
                    finishx = i;
                    finishy = j;
                }
        if (finishx > 0) {
            targetx = (startx + finishx) / 2;
            targety = (starty + finishy) / 2;
            cout<<targetx<<"  "<<targety<<endl;
        }
    }
}