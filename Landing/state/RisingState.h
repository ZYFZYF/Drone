#ifndef LANDING_RISINGSTATE_H
#define LANDING_RISINGSTATE_H

#include <PathUpdater.h>
#include "State.h"

class RisingState : public State<PathUpdater>
{
public:
    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

    static RisingState *Instance();

private:
    RisingState();

    const simxFloat RISING_HEIGHT = 3.0;

    const float RISING_STEP_LENGTH = 0.08;

};


#endif //LANDING_RISINGSTATE_H
