#include <iostream>
#include "LandingState.h"
#include "FinishState.h"

LandingState::LandingState()
{

}

void LandingState::Enter(PathUpdater *t)
{
    std::cout << "now begin to land" << std::endl;
    Point plane_pos = t->getPlanePosition();
    t->setLandingSignal(plane_pos[2] + RELATIVE_LANDING_BEGIN_HEIGHT, plane_pos[2] + RELATIVE_LANDING_END_HEIGHT);
    std::cout << "adjust landing height to " << plane_pos[2] + RELATIVE_LANDING_BEGIN_HEIGHT << " and "
              << plane_pos[2] + RELATIVE_LANDING_END_HEIGHT << std::endl;
}

void LandingState::Execute(PathUpdater *t)
{
    Point target_pos = t->getTargetPosition();
    Point plane_pos = t->getPlanePosition();
    plane_pos.setZ(plane_pos[2] + RELATIVE_LANDING_HEIGHT);
    Point error = plane_pos - target_pos;
    std::cout << error[0] << ' ' << error[1] << ' ' << error[2] << std::endl;
    target_pos = target_pos + error.normalize() * std::min(LANDING_STEP_LENGTH, error.length());
    t->setTargetPosition(target_pos);
    if(error.norm() < 0.1)
    {
        t->changeState(new FinishState);
    }
}

void LandingState::Exit(PathUpdater *t)
{
    std::cout << "finish landing, keep this" << std::endl;
}
