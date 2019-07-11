#include <iostream>
#include "ApproachingState.h"
#include "math.h"
#include "LandingState.h"

void ApproachingState::Enter(PathUpdater *t)
{
    std::cout << "now begin approaching to the car" << std::endl;
}

void ApproachingState::Execute(PathUpdater *t)
{
    Point target_pos = t->getTargetPosition();
    Point plane_pos = t->getPlanePosition();
    plane_pos.setZ(plane_pos[2] + APPROACHING_OVER_HEIGHT);
    Point error = plane_pos - target_pos;
    std::cout << error[0] << ' ' << error[1] << ' ' << error[2] << std::endl;
    target_pos = target_pos + error.normalize() * std::min(APPROACHING_STEP_LENGTH, error.length());
    t->setTargetPosition(target_pos);
    if(error.norm() < 0.1)
    {
        t->changeState(new LandingState);
    }
}

void ApproachingState::Exit(PathUpdater *t)
{
    std::cout << "finished approaching, now we are suspending above the car" << std::endl;
}

ApproachingState::ApproachingState()
{

}
