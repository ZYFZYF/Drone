#ifndef LANDING_PATHPLANER_H
#define LANDING_PATHPLANER_H


#include "Updater.h"
#include "State.h"

const int PATHTIMESTEP = 60;

class PathUpdater : public Updater
{
public:
    static PathUpdater *Instance(simxInt);

private:
    explicit PathUpdater(simxInt);

    void update() override;

    void changeState(State<PathUpdater>*);

    State<PathUpdater>* m_current_state;
};


#endif //LANDING_PATHPLANER_H
