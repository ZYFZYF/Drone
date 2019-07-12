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
    plane_pos.setZ(target_pos[2]);
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
        close_rounds ++;
        //t->changeState(new FinishState);
    } else
    {
        close_rounds = 0;
    }
    std::cout << "close rounds = " << close_rounds << std::endl;
    if(close_rounds >= 10)
    {
        std::cout << "prepare to stop the rotor" << std::endl;
        t->setLandingFinished();
    }
}

void LandingState::Exit(PathUpdater *t)
{
    std::cout << "finish landing, keep this" << std::endl;
}
