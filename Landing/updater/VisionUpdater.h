#ifndef LANDING_VISIONPLANNER_H
#define LANDING_VISIONPLANNER_H


#include "Updater.h"
const int VISIONTIMESTEP = 25;
class VisionUpdater: public Updater
{
public:
    static VisionUpdater *Instance(int client_id);
private:
    VisionUpdater(int client_id);
    void update() override ;
};


#endif //LANDING_VISIONPLANNER_H
