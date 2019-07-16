#ifndef DRONE_PLANNINGPATHUPDATER_H
#define DRONE_PLANNINGPATHUPDATER_H


#include "PlanningUpdater.h"

class PlanningPathUpdater: public PlanningUpdater
{
public:
    explicit PlanningPathUpdater(int client_id);

    void update() override;
};


#endif //DRONE_PLANNINGPATHUPDATER_H
