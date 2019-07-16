#ifndef DRONE_PLANNINGUPDATER_H
#define DRONE_PLANNINGUPDATER_H


#include "../../Common/updater/Updater.h"

class PlanningUpdater: public Updater
{
public:
    explicit PlanningUpdater(int time_step=0, int client_id=-1);
};


#endif //DRONE_PLANNINGUPDATER_H
