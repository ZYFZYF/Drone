#ifndef LANDING_LANDINGSTATE_H
#define LANDING_LANDINGSTATE_H


#include <PathUpdater.h>

class LandingState : public State<PathUpdater>
{
public:
    LandingState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

private:
    const simxFloat RELATIVE_LANDING_HEIGHT = config.getFloatParam("LandingState", "RELATIVE_LANDING_HEIGHT");
    const simxFloat LANDING_STEP_LENGTH = config.getFloatParam("LandingState", "LANDING_STEP_LENGTH");
    int close_rounds = 0;
};


#endif //LANDING_LANDINGSTATE_H
