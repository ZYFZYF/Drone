#ifndef LANDING_RISINGSTATE_H
#define LANDING_RISINGSTATE_H


#include "../updater/PathUpdater.h"

class RisingState : public State<PathUpdater>
{
public:
    RisingState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

private:


    const simxFloat RISING_HEIGHT = Config::Instance()->getFloatParam("RisingState", "RISING_HEIGHT");

    const float RISING_STEP_LENGTH = Config::Instance()->getFloatParam("RisingState", "RISING_STEP_LENGTH");

    const simxInt WAITING_ROUNDS = Config::Instance()->getIntParam("RisingState", "WAITING_ROUNDS");
};


#endif //LANDING_RISINGSTATE_H
