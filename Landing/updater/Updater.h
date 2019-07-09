#ifndef LANDING_PLANNER_H
#define LANDING_PLANNER_H

extern "C" {
#include "extApi.h"
}

class Updater
{
public:
    Updater(int time_step, int client_id);

    virtual void update() = 0;

    void run();

    void getDronePosition(simxFloat *pos);

    void getCarPosition(simxFloat *pos);

    void getTargetPosition(simxFloat *pos);

    void getPlanePosition(simxFloat *pos);

    void setTargetPosition(simxFloat *pos);


protected:
    simxInt m_cid;
    simxInt m_handle_drone, m_handle_target, m_handle_car, m_handle_plane;
private:
    float m_time_step;
};


#endif //LANDING_PLANNER_H
