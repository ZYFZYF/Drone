#ifndef LANDING_PATHPLANER_H
#define LANDING_PATHPLANER_H


#include "LandingUpdater.h"
#include "../../Common/state/State.h"

class LandingPathUpdater : public LandingUpdater
{
public:
    static LandingPathUpdater *Instance(simxInt);

    void changeState(State<LandingPathUpdater> *);

    void setLandingFinished();

private:
    explicit LandingPathUpdater(simxInt);

    void update() override;

    State<LandingPathUpdater> *m_current_state;

    const int PATH_TIME_STEP = Config::Instance()->getIntParam("LandingPathUpdater", "PATH_TIME_STEP");
};

#endif //LANDING_PATHPLANER_H
