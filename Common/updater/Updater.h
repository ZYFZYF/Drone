#ifndef LANDING_UPDATER_H
#define LANDING_UPDATER_H

#include "../utils/Point.h"

extern "C" {
#include "../vrep/extApi.h"
}


class Updater
{
public:
    explicit Updater(int time_step=0, int client_id=-1);

    virtual void update() = 0;

    void run();

protected:
    simxInt m_cid;

private:
    float m_time_step;
};


#endif //LANDING_UPDATER_H