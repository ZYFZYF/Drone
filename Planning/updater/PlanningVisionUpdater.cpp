#include <iostream>
#include "PlanningVisionUpdater.h"
#include "../../Common/config/Config.h"
using namespace std;
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int clientID;
float target_height=0.24;
float target_platform=-0.225;
float end_platform=0.875;
float plane=0.445;
float platform_height;
float rate=1.75;
float circle_offsetx;
float circle_offsety;
float targetx;
float targety;
float target_offsetx;
float target_offsety;
float circlex;
float circley;
simxFloat position[3];
simxFloat angle[3];
simxFloat tar_position[3];
Point p;
PlanningVisionUpdater::PlanningVisionUpdater(int client_id): PlanningUpdater(Config::Instance()->getIntParam("PlanningVisionUpdater", "TIME_STEP"), client_id)
{
    clientID=client_id;
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void PlanningVisionUpdater::update() {
    simxInt camera;
    simxInt target;
    simxGetObjectHandle(clientID, "zed_vision0", &camera, simx_opmode_blocking);
    simxGetObjectHandle(clientID, "Target", &target, simx_opmode_blocking);
    simxInt resolution[2];
    simxUChar *image = 0;
    cv::namedWindow("opencv test", CV_WINDOW_AUTOSIZE);
    int ret = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_blocking);
    if (ret != simx_return_ok) {
        return;
    }

    cv::Mat channel(resolution[1], resolution[0], CV_8UC3, image);
    //读回来的图像数据是垂直翻转的,问题应该是在cvMat 和 v-rep 垂直坐标轴的方向相反,flip一下就正常了
    flip(channel, channel, 0);
    //读回来的图像数据时rgb通道分布的，而cvMat 默认bgr
    int startx = -1, starty = -1;
    int finishx = 0, finishy = 0;
    for (int i = 0; i < channel.rows; i++)
        for (int j = 0; j < channel.cols; j++)
            if (channel.at<cv::Vec3b>(i, j)[0] > 170 && channel.at<cv::Vec3b>(i, j)[1] < 50 &&
                channel.at<cv::Vec3b>(i, j)[2] < 50) {
                if (startx == -1) {
                    startx = i;
                    starty = j;
                }
                finishx = i;
                finishy = j;
            }
    if (startx == -1) {
        cout << "未发现抓取物体" << endl;
        p.setX(-1);
        p.setY(-1);
        p.setZ(-1);
        platform_height = end_platform;
    } else {
        simxGetObjectPosition(clientID, camera, -1, position, simx_opmode_blocking);
        targetx = (startx + finishx) / 2;
        targety = (starty + finishy) / 2;
        target_offsetx = (position[2] - target_height) * rate / 1280 * (640 - targety);
        target_offsety = (position[2] - target_height) * rate / 1280 * (targetx - 360);
        p.setX(position[0] + target_offsetx * cos(angle[2]) + target_offsety * sin(angle[2]));
        p.setY(position[1] + target_offsety * cos(angle[2]) - target_offsetx * sin(angle[2]));
        p.setZ(plane);
        simxGetObjectPosition(clientID, target, -1, tar_position, simx_opmode_blocking);
        cout << p.x() << " " << p.y() << " " << p.z() << "  " << tar_position[0] << " " << tar_position[1] << " "
             << tar_position[2] << endl;
        platform_height = target_platform;
    }
    simxSetFloatSignal(clientID, "target_x", p.x(), simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "target_y", p.y(), simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "target_z", p.z(), simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "angle_x", 0, simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "angle_y", 0, simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "angle_z", 0, simx_opmode_oneshot);


    cv::Mat gray;
    cvtColor(channel, gray, cv::COLOR_RGB2GRAY);
    GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);
    vector<cv::Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 10, 1000);
    if (circles.size() > 0) {
        circlex = circles[0][1];
        circley = circles[0][0];
        circle_offsetx = (position[2] - platform_height) * rate / 1280 * (640 - circley);
        circle_offsety = (position[2] - platform_height) * rate / 1280 * (circlex - 360);
        p.setX(position[0] + circle_offsetx * cos(angle[2]) + circle_offsety * sin(angle[2]));
        p.setY(position[1] + circle_offsety * cos(angle[2]) - circle_offsetx * sin(angle[2]));
        p.setZ(platform_height);
    } else {
        cout << "没找到圆" << endl;
        p.setX(-1);
        p.setY(-1);
        p.setZ(-1);
    }
    simxSetFloatSignal(clientID, "circle_x", p.x(), simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "circle_y", p.y(), simx_opmode_oneshot);
    simxSetFloatSignal(clientID, "circle_z", p.z(), simx_opmode_oneshot);
}