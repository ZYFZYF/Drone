#include "PlanningPathUpdater.h"
#include "../../Common/config/Config.h"

PlanningPathUpdater::PlanningPathUpdater(int client_id) : PlanningUpdater(
        Config::Instance()->getIntParam("PlanningPathUpdater", "TIME_STEP"), client_id)
{

}

void PlanningPathUpdater::update()
{

}
