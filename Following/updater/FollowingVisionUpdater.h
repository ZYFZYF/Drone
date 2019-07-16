#ifndef DRONE_FOLLOWINGVISIONUPDATER_H
#define DRONE_FOLLOWINGVISIONUPDATER_H


#include "FollowingUpdater.h"
#include "../../Common/config/Config.h"

class FollowingVisionUpdater: public FollowingUpdater
{
public:
    explicit FollowingVisionUpdater(int client_id);

    void update() override;
};


#endif //DRONE_FOLLOWINGVISIONUPDATER_H
