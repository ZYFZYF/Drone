#ifndef LANDING_PATHPLANER_H
#define LANDING_PATHPLANER_H


#include "Updater.h"
#include "State.h"

const int PATHTIMESTEP = 60;

class PathUpdater : public Updater
{
public:
    static PathUpdater *Instance(simxInt);
    void changeState(State<PathUpdater>*);
    void setLandingFinished();
private:
    explicit PathUpdater(simxInt);

    void update() override;


    State<PathUpdater>* m_current_state;
};


#endif //LANDING_PATHPLANER_H
