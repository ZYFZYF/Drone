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

private:

    const simxFloat APPROACHING_OVER_HEIGHT = config.getFloatParam("ApproachingState", "APPROACHING_OVER_HEIGHT");
    const simxFloat APPROACHING_STEP_LENGTH = config.getFloatParam("ApproachingState", "APPROACHING_STEP_LENGTH");
    const simxFloat RELATIVE_LANDING_BEGIN_HEIGHT = config.getFloatParam("ApproachingState", "RELATIVE_LANDING_BEGIN_HEIGHT");
    const simxFloat RELATIVE_LANDING_END_HEIGHT = config.getFloatParam("ApproachingState", "RELATIVE_LANDING_END_HEIGHT");
};


#endif //LANDING_APPROCHINGSTATE_H
