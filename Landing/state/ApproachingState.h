#ifndef LANDING_APPROCHINGSTATE_H
#define LANDING_APPROCHINGSTATE_H

#include <PathUpdater.h>
#include "State.h"

class ApproachingState : public State<PathUpdater>
{
public:
    ApproachingState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

    static ApproachingState *Instance();

private:


    const simxFloat APPROACHING_OVER_HEIGHT = 1.0;

    const simxFloat APPROACHING_STEP_LENGTH = 0.03;
};


#endif //LANDING_APPROCHINGSTATE_H
