#ifndef LANDING_PATHPLANER_H
#define LANDING_PATHPLANER_H


#include "../../Common/updater/Updater.h"
#include "../../Common/state/State.h"

class PathUpdater : public Updater
{
public:
    static PathUpdater *Instance(simxInt);

    void changeState(State<PathUpdater> *);

private:
    explicit PathUpdater(simxInt);

    void update() override;

    State<PathUpdater> *m_current_state;

    const int PATH_TIME_STEP = Config::Instance()->getIntParam("PathUpdater", "PATH_TIME_STEP");
};

#endif //LANDING_PATHPLANER_H