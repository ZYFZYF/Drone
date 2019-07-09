#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "PathUpdater.h"
#include "VisionUpdater.h"
#include "logging.h"
#include <windows.h>
#include <signal.h>
extern "C" {
#include "extApi.h"
}
int client_id;
bool ctrlHandler(DWORD fdwctrltype)
{
    switch (fdwctrltype)
    {
        case CTRL_C_EVENT:
            simxStopSimulation(client_id, simx_opmode_blocking);
            simxFinish(client_id);
            std::cout<<"Close connection to V-REP"<<std::endl;
            return false;
//        case CTRL_CLOSE_EVENT:
//            printf("ctrl-close event\n\n");
//            return(true);
//        case CTRL_BREAK_EVENT:
//            printf("ctrl-break event\n\n");
//            return false;
//        case CTRL_LOGOFF_EVENT:
//            printf("ctrl-logoff event\n\n");
//            return false;
//            case CTRL_SHUTDOWN_EVENT:
//            printf("ctrl-shutdown event\n\n");
//            return false;
//        default:
//            return false;
    }
}
int main(int argc, char const *argv[])
{
    if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlHandler, true))
    {
        std::cout << "Capture ctrl-c event failed" << std::endl;
        return 0;
    };
    simxFinish(-1);
    client_id = simxStart("127.0.0.1", 19997, 1, 1, 2000, 5);
    if(client_id == -1)
    {
        std::cout<< "Failed to connect to remote API server" <<std::endl;
        return 0;
    }
    std::cout<< "Connect to remote API server and cid is " << client_id <<std::endl;
    simxStartSimulation(client_id, simx_opmode_blocking);
    std::thread path([]() {
        PathUpdater::Instance(client_id)->run();
    });
    std::thread vision([]() {
        VisionUpdater::Instance(client_id)->run();
    });
    path.join();
    vision.join();
    return 0;
}

