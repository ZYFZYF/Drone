#include "PlanningUpdater.h"
#include "../../Common/utils/utils.h"

PlanningUpdater::PlanningUpdater(int time_step, int client_id) : Updater(time_step, client_id)
{
    simxGetObjectHandle(m_cid, "Quadricopter_base", &m_handle_drone, simx_opmode_blocking);
    simxGetObjectHandle(m_cid, "Quadricopter_target", &m_handle_target, simx_opmode_blocking);
}

const Point PlanningUpdater::getDronePosition()
{
    return utils::getObjectPosition(m_handle_drone, m_cid);
}

const Point PlanningUpdater::getTargetPosition()
{
    return utils::getObjectPosition(m_handle_target, m_cid);
}

void PlanningUpdater::setTargetPosition(Point p)
{
    simxFloat pos[3];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    simxSetObjectPosition(m_cid, m_handle_target, -1, pos, simx_opmode_oneshot);
}
