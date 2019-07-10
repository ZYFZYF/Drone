#include <iostream>
#include "RisingState.h"
#include "ApproachingState.h"
#include "WaitState.h"

RisingState::RisingState() {}

RisingState* RisingState::Instance()
{
    static RisingState instance;
    return &instance;
}
void RisingState::Enter(PathUpdater *t)
{
    std::cout << "now begin rising to high" << std::endl;
}

void RisingState::Execute(PathUpdater *t)
{
    Point target_pos = t->getDronePosition();
    std::cout << target_pos[0] << " " << target_pos[1] << " " << target_pos[2] << std::endl;
    target_pos.setZ(target_pos[2] + RISING_STEP_LENGTH);
    std::cout << target_pos[2] << std::endl;
    t->setTargetPosition(target_pos);

    if(target_pos[2] > RISING_HEIGHT)
    {
        t->changeState(new WaitState(200, ApproachingState::Instance()));
        //t->changeState(ApproachingState::Instance());
    }
}

void RisingState::Exit(PathUpdater *t)
{
    std::cout << "rising to height " << RISING_HEIGHT << " and prepare to leave" << std::endl;
}
