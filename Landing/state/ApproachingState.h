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


    const simxFloat APPROACHING_OVER_HEIGHT = 0.3;
    const simxFloat APPROACHING_STEP_LENGTH = 0.03;
    const simxFloat RELATIVE_LANDING_BEGIN_HEIGHT = 0.75;
    const simxFloat RELATIVE_LANDING_END_HEIGHT = 0.3;
};


#endif //LANDING_APPROCHINGSTATE_H
