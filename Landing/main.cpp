#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "PathUpdater.h"
#include "VisionUpdater.h"
#include "logging.h"
#include <windows.h>
extern "C" {
#include "extApi.h"
}
int main(int argc, char const *argv[])
{
    int client_id = simxStart("127.0.0.1", 19997, 1, 1, 2000, 5);
    if(client_id == -1)
    {
        std::cout<< "Failed to connect to remote API server" <<std::endl;
        return 0;
    }
    std::cout<< "Connect to remote API server and cid is " << client_id <<std::endl;
    std::thread path([client_id]() {
        PathUpdater::Instance(client_id)->run();
    });
    std::thread vision([client_id]() {
        VisionUpdater::Instance(client_id)->run();
    });
    path.join();
    vision.join();
//    log::start("task1");
//    log::info("Hello World");
//    log::end();
//    log::start("task2");
//    log::info("Goodbye the cruel world");
//    log::start("task3");
//    Sleep(1000);
//    log::info("I'm sure to come back");
//    log::end();
//    Sleep(500);
//    log::end();
    return 0;
}

