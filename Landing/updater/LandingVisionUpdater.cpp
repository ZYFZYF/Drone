#include <iostream>
#include "LandingVisionUpdater.h"
#include <cmath>
#include "LandingUpdater.h"
using namespace std;
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int clientID;
float midx,midy;
Point p;
float height=0.282;
float rate=1.75;
float offsetx;
float offsety;
simxFloat position[3];
simxFloat angle[3];
simxFloat tar_position[3];
LandingVisionUpdater::LandingVisionUpdater(int client_id): LandingUpdater(Config::Instance()->getIntParam("LandingVisionUpdater", "TIME_STEP"), client_id)
{
    clientID=client_id;
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void LandingVisionUpdater::update()
{
    simxInt camera;
    simxInt target;
    simxGetObjectHandle(clientID, "zed_vision0", &camera, simx_opmode_blocking);
    simxGetObjectHandle(clientID, "land_plane", &target, simx_opmode_blocking);
    simxInt resolution[2];
    simxUChar * image=0;
    while(true) {
        int ret = simxGetVisionSensorImage(clientID, camera, resolution, &image, 0, simx_opmode_blocking);
        if (ret != simx_return_ok) {
            return;
        }
        simxGetObjectPosition(clientID, camera, -1,position, simx_opmode_blocking);
        simxGetObjectOrientation(clientID, camera, -1,angle,simx_opmode_blocking);
//        cout << position[0] << " "<<position[1]<<" "<<position[2]<<"  "<<angle[0]<<" "<<angle[1]<<" "<<angle[2]<<endl;
        cv::Mat channel(resolution[1], resolution[0], CV_8UC3, image);
        //读回来的图像数据是垂直翻转的,问题应该是在cvMat 和 v-rep 垂直坐标轴的方向相反,flip一下就正常了
        flip(channel, channel, 0);
        int startx = -1, starty = -1;
        int finishx = 0, finishy = 0;
        for (int i = 0; i < channel.rows; i++)
            for (int j = 0; j < channel.cols; j++)
                if (channel.at<cv::Vec3b>(i, j)[0] > 230 && channel.at<cv::Vec3b>(i, j)[1] > 230 && channel.at<cv::Vec3b>(i, j)[2] > 230) {
                    if (startx == -1) {
                        startx = i;
                        starty = j;
                    }
                    finishx = i;
                    finishy = j;
                }
        if(startx==-1){
            cout<<"未发现二维码"<<endl;
            p.setX(-1);
            p.setY(-1);
            p.setZ(-1);
        }
        else {
            midx = (startx + finishx) / 2;
            midy = (starty + finishy) / 2;
            offsetx = (position[2] - height) * rate / 1280 * (640 - midy);
            offsety = (position[2] - height) * rate / 1280 * (midx - 360);
            p.setX(position[0] + offsetx * cos(angle[2]) + offsety * sin(angle[2]));
            p.setY(position[1] + offsety * cos(angle[2]) - offsetx * sin(angle[2]));
            p.setZ(height);
            simxGetObjectPosition(clientID, target, -1, tar_position, simx_opmode_blocking);
            cout << p.x() << " " << p.y() << " " << p.z() << "  " << tar_position[0] << " " << tar_position[1] << " " << tar_position[2] << endl;
        }
        simxSetFloatSignal(clientID,"QRcode_x",p.x(),simx_opmode_blocking);
        simxSetFloatSignal(clientID,"QRcode_y",p.y(),simx_opmode_blocking);
        simxSetFloatSignal(clientID,"QRcode_z",p.z(),simx_opmode_blocking);
    }
}
