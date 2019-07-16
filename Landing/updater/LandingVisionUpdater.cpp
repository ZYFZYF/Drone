#include <iostream>
#include "LandingVisionUpdater.h"

LandingVisionUpdater::LandingVisionUpdater(int client_id): LandingUpdater(Config::Instance()->getIntParam("LandingVisionUpdater", "TIME_STEP"), client_id)
{
    std::cout<<"VisionPlanner constructed"<<std::endl;
}

void LandingVisionUpdater::update()
{
}