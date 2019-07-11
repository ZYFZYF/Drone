#ifndef LANDING_LANDINGSTATE_H
#define LANDING_LANDINGSTATE_H


#include <PathUpdater.h>

class LandingState: public State<PathUpdater>
{
public:
    LandingState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

private:
    const simxFloat RELATIVE_LANDING_BEGIN_HEIGHT = 0.75;
    const simxFloat RELATIVE_LANDING_END_HEIGHT = 0.4;
    const simxFloat RELATIVE_LANDING_HEIGHT = 0.35;
    const simxFloat LANDING_STEP_LENGTH = 0.02;
};


#endif //LANDING_LANDINGSTATE_H
