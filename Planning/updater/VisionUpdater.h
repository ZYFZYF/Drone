#ifndef LANDING_VISIONPLANNER_H
#define LANDING_VISIONPLANNER_H


#include "Updater.h"

class VisionUpdater : public Updater
{
public:
    static VisionUpdater *Instance(int client_id);

private:
    VisionUpdater(int client_id);

    void update() override;

    const int VISION_TIME_STEP = Config::Instance()->getIntParam("VisionUpdater", "VISION_TIME_STEP");

};


#endif //LANDING_VISIONPLANNER_H
