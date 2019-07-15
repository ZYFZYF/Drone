#include <iostream>
#include <cassert>
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

const Point Updater::getDronePosition()
{
    simxFloat pos[3];
    simxGetObjectPosition(m_cid, m_handle_drone, -1, pos, simx_opmode_blocking);
    return Point(pos[0], pos[1], pos[2]);
}

const Point Updater::getCarPosition()
{
    simxFloat pos[3];
    simxGetObjectPosition(m_cid, m_handle_car, -1, pos, simx_opmode_blocking);
    return Point(pos);
}

const Point Updater::getTargetPosition()
{
    simxFloat pos[3];
    simxGetObjectPosition(m_cid, m_handle_target, -1, pos, simx_opmode_blocking);
    return Point(pos);
}

const Point Updater::getPlanePosition()
{
    simxFloat pos[3];
    simxGetObjectPosition(m_cid, m_handle_plane, -1, pos, simx_opmode_blocking);
    return Point(pos);
}

void Updater::setTargetPosition(Point p)
{
    simxFloat pos[3];
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    simxSetObjectPosition(m_cid, m_handle_target, -1, pos, simx_opmode_oneshot);
}

void
Updater::setLandingSignal(simxFloat landing_begin_height, simxFloat landing_end_height)
{
    assert(landing_end_height > 0 && landing_end_height < landing_begin_height);
    simxSetFloatSignal(m_cid, "landing_begin_height", landing_begin_height, simx_opmode_oneshot);
    simxSetFloatSignal(m_cid, "landing_end_height", landing_end_height, simx_opmode_oneshot);
}
