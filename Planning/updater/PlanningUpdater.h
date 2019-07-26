#ifndef DRONE_PLANNINGUPDATER_H
#define DRONE_PLANNINGUPDATER_H


#include "../../Common/updater/Updater.h"
extern bool use_vision;
class PlanningUpdater: public Updater
{
public:
    explicit PlanningUpdater(int time_step=0, int client_id=-1);

    const Point getDronePosition();

    const Point getTargetPosition();

    void setTargetPosition(Point p);

    void setHand() const;

private:
    simxInt m_handle_drone, m_handle_target;
};


#endif //DRONE_PLANNINGUPDATER_H
