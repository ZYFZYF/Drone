#include <iostream>
#include "LandingVisionUpdater.h"
using namespace std;
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int clientID;
int midx,midy;
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
        int startx=-1,starty=-1;
        int finishx=0,finishy=0;
        for(int i=0;i<channel.rows;i++)
            for(int j=0;j<channel.cols;j++)
                if(channel.at<Vec3b>(i,j)[0]>230 && channel.at<Vec3b>(i,j)[1]>230 && channel.at<Vec3b>(i,j)[2]>230) {
                    if (startx == -1) {
                        startx = i;
                        starty = j;
                    }
                    finishx = i;
                    finishy = j;
                }
        midx=(startx+finishx)/2;
        midy=(starty+finishy)/2;

    }
}
