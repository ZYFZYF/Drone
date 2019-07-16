#include <iostream>
#include "FollowingVisionUpdater.h"

FollowingVisionUpdater::FollowingVisionUpdater(int client_id) : FollowingUpdater(Config::Instance()->getIntParam("FollowingVisionUpdater", "TIME_STEP"), client_id)
{

}

void FollowingVisionUpdater::update()
{
    std::cout << "This is vision updater of task Following" << std::endl;
}
