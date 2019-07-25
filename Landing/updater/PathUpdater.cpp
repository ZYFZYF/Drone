#include <iostream>
#include <cassert>
#include "PathUpdater.h"
#include "../state/RisingState.h"

PathUpdater *PathUpdater::Instance(int client_id)
{
    static PathUpdater instance(client_id);
    return &instance;
}

PathUpdater::PathUpdater(int client_id) : Updater(PATH_TIME_STEP, client_id)
{
    std::cout << "PathPlanner constructed" << std::endl;
    m_current_state = new RisingState;
}

void PathUpdater::update()
{
    m_current_state->Execute(this);
}

void PathUpdater::changeState(State<PathUpdater> *p_new_state)
{
    //Memory leak exist
    assert(m_current_state && p_new_state);
    m_current_state->Exit(this);
    m_current_state = p_new_state;
    m_current_state->Enter(this);
}

void PathUpdater::setLandingFinished()
{
    simxSetFloatSignal(m_cid, "is_landing_finished", 1.0, simx_opmode_oneshot);
}
