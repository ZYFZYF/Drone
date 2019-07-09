//
// Created by 97344 on 2019/7/8.
//

#include <iostream>
#include "VisionUpdater.h"
VisionUpdater* VisionUpdater::Instance(int client_id)
{
    static VisionUpdater instance(client_id);
    return &instance;
}

VisionUpdater::VisionUpdater(int client_id): Updater(VISIONTIMESTEP, client_id)
{
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void VisionUpdater::update()
{
}