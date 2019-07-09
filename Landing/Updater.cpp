#include <iostream>
#include "Updater.h"
#include "windows.h"
extern "C" {
#include "extApi.h"
}
Updater::Updater(int time_step, int client_id) :m_timeStep(time_step), m_cid(client_id)
{

}
void Updater::run() const
{
    while(true)
    {
        update();
        Sleep(m_timeStep);
    }
}