#include <iostream>
#include <cassert>
#include "Updater.h"
#include "../utils/utils.h"

Updater::Updater(int time_step, int client_id) : m_time_step(time_step), m_cid(client_id)
{
}

void Updater::run()
{
    while (true)
    {
        update();
        utils::sleep(m_time_step);
    }
}