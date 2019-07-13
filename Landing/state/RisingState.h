#ifndef LANDING_RISINGSTATE_H
#define LANDING_RISINGSTATE_H

#include <PathUpdater.h>
#include "State.h"

class RisingState : public State<PathUpdater>
{
public:
    RisingState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

private:


    const simxFloat RISING_HEIGHT = config.getFloatParam("RisingState", "RISING_HEIGHT");

    const float RISING_STEP_LENGTH = config.getFloatParam("RisingState", "RISING_STEP_LENGTH");

};


#endif //LANDING_RISINGSTATE_H
