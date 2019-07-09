#include <iostream>
#include "RisingState.h"

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
    simxFloat target_pos[3];
    t->getDronePosition(target_pos);
    std::cout << target_pos[0] << " " << target_pos[1] << " " << target_pos[2] << std::endl;
    target_pos[2] += 0.05;
    std::cout << target_pos[2] << std::endl;
    t->setTargetPosition(target_pos);
}

void RisingState::Exit(PathUpdater *t)
{
    std::cout << "rising finished and prepare to leave" << std::endl;
}
