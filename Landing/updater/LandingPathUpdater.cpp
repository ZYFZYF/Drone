#include <iostream>
#include <cassert>
#include "LandingPathUpdater.h"
#include "../state/RisingState.h"

LandingPathUpdater *LandingPathUpdater::Instance(int client_id)
{
    static LandingPathUpdater instance(client_id);
    return &instance;
}

LandingPathUpdater::LandingPathUpdater(int client_id) : LandingUpdater(PATH_TIME_STEP, client_id)
{
    std::cout << "PathPlanner constructed" << std::endl;
    m_current_state = new RisingState;
}

void LandingPathUpdater::update()
{
    m_current_state->Execute(this);
}

void LandingPathUpdater::changeState(State<LandingPathUpdater> *p_new_state)
{
    //Memory leak exist
    assert(m_current_state && p_new_state);
    m_current_state->Exit(this);
    m_current_state = p_new_state;
    m_current_state->Enter(this);
}

void LandingPathUpdater::setLandingFinished()
{
    simxSetFloatSignal(m_cid, "is_landing_finished", 1.0, simx_opmode_oneshot);
}
