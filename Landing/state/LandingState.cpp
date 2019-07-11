#include <iostream>
#include "LandingState.h"
#include "FinishState.h"

LandingState::LandingState()
{

}

void LandingState::Enter(PathUpdater *t)
{
    std::cout << "now begin to land" << std::endl;
}

void LandingState::Execute(PathUpdater *t)
{
    Point target_pos = t->getTargetPosition();
    Point plane_pos = t->getPlanePosition();
    plane_pos.setZ(plane_pos[2] + RELATIVE_LANDING_HEIGHT);
    Point error = plane_pos - target_pos;
    std::cout << error[0] << ' ' << error[1] << ' ' << error[2] << std::endl;
    target_pos = target_pos + error.normalize() * std::min(LANDING_STEP_LENGTH, error.length());
    std::cout << "error.length is " << error.length() << std::endl;
    t->setTargetPosition(target_pos);
    std::cout << "plane pos " << plane_pos[0] << ' ' << plane_pos[1] << ' ' << plane_pos[2] << std::endl;
    error = t->getDronePosition() - plane_pos;
    std::cout << "error is " << error[0] << ' ' << error[1] << ' ' << error[2] << std::endl;
    if(error.norm() < 0.03)
    {
        //t->changeState(new FinishState);
        t->setLandingFinished();
    }
}

void LandingState::Exit(PathUpdater *t)
{
    std::cout << "finish landing, keep this" << std::endl;
}
