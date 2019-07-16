#ifndef DRONE_FOLLOWINGUPDATER_H
#define DRONE_FOLLOWINGUPDATER_H


#include "../../Common/updater/Updater.h"

class FollowingUpdater: public Updater
{
public:
    explicit FollowingUpdater(int time_step=0, int client_id=-1);

};


#endif //DRONE_FOLLOWINGUPDATER_H
