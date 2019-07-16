//
// Created by 97344 on 2019/7/16.
//

#include <iostream>
#include "FollowingPathUpdater.h"

void FollowingPathUpdater::update()
{

}

FollowingPathUpdater::FollowingPathUpdater(int client_id) : FollowingUpdater(Config::Instance()->getIntParam("FollowingPathUpdater", "TIME_STEP"), client_id)
{
    std::cout << "This is path updater of task Following" << std::endl;
}
