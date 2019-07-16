#include "PlanningVisionUpdater.h"
#include "../../Common/config/Config.h"

PlanningVisionUpdater::PlanningVisionUpdater(int client_id) : PlanningUpdater(
        Config::Instance()->getIntParam("PlanningVisionUpdater", "TIME_STEP"), client_id)
{

}

void PlanningVisionUpdater::update()
{

}
