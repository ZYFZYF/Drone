#include <iostream>
#include "Updater.h"
#include "windows.h"

extern "C" {
#include "extApi.h"
}

Updater::Updater(int time_step, int client_id) : m_time_step(time_step), m_cid(client_id)
{
    simxGetObjectHandle(m_cid, "Quadricopter_base", &m_handle_drone, simx_opmode_blocking);
    simxGetObjectHandle(m_cid, "Quadricopter_target", &m_handle_target, simx_opmode_blocking);
    simxGetObjectHandle(m_cid, "land_plane", &m_handle_plane, simx_opmode_blocking);
    simxGetObjectHandle(m_cid, "Car", &m_handle_car, simx_opmode_blocking);
}

void Updater::run()
{
    while (true)
    {
        update();
        Sleep(m_time_step);
    }
}

void Updater::getCarPosition(simxFloat *pos)
{
    simxGetObjectPosition(m_cid, m_handle_car, -1, pos, simx_opmode_blocking);
}

void Updater::getDronePosition(simxFloat *pos)
{
    simxGetObjectPosition(m_cid, m_handle_drone, -1, pos, simx_opmode_blocking);
}

void Updater::getTargetPosition(simxFloat *pos)
{
    simxGetObjectPosition(m_cid, m_handle_target, -1, pos, simx_opmode_blocking);
}

void Updater::getPlanePosition(simxFloat *pos)
{
    simxGetObjectPosition(m_cid, m_handle_plane, -1, pos, simx_opmode_blocking);
}

void Updater::setTargetPosition(simxFloat *pos)
{
    simxSetObjectPosition(m_cid, m_handle_target, -1, pos, simx_opmode_oneshot);
}