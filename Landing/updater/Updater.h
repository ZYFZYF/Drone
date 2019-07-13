#ifndef LANDING_PLANNER_H
#define LANDING_PLANNER_H

extern "C" {
#include "extApi.h"
}
#include "Point.h"
#include "Config.h"

class Updater
{
public:
    Updater(int time_step, int client_id);

    virtual void update() = 0;

    void run();

    const Point getDronePosition();

    const Point getCarPosition();

    const Point getTargetPosition();

    const Point getPlanePosition();

    void setTargetPosition(Point p);

    void setLandingSignal(simxFloat landing_begin_height, simxFloat landing_end_height);


protected:
    simxInt m_cid;
    simxInt m_handle_drone, m_handle_target, m_handle_car, m_handle_plane;
private:
    float m_time_step;
};


#endif //LANDING_PLANNER_H
