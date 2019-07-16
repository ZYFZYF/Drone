#ifndef DRONE_FOLLOWINGPATHUPDATER_H
#define DRONE_FOLLOWINGPATHUPDATER_H


#include "FollowingUpdater.h"
#include "../../Common/config/Config.h"

class FollowingPathUpdater: public FollowingUpdater
{
public:
    explicit FollowingPathUpdater(int client_id);

    void update() override;
};


#endif //DRONE_FOLLOWINGPATHUPDATER_H
