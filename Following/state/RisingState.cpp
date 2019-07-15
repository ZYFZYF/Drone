#include <iostream>
#include "RisingState.h"
#include "ApproachingState.h"
#include "WaitState.h"

RisingState::RisingState() {}

void RisingState::Enter(PathUpdater *t)
{
    std::cout << "now begin rising to high" << std::endl;
}

void RisingState::Execute(PathUpdater *t)
{
    Point drone_pos = t->getDronePosition();
    std::cout << drone_pos[0] << " " << drone_pos[1] << " " << drone_pos[2] << std::endl;
    drone_pos.setZ(drone_pos[2] + RISING_STEP_LENGTH);
    std::cout << drone_pos[2] << std::endl;
    t->setTargetPosition(drone_pos);
    // check leave
    if(drone_pos[2] > RISING_HEIGHT)
    {
        t->changeState(new WaitState(200, new ApproachingState));
    }
}

void RisingState::Exit(PathUpdater *t)
{
    std::cout << "rising to height " << RISING_HEIGHT << " and prepare to leave" << std::endl;
}