#include <iostream>
#include <cassert>
#include "Updater.h"
#include "../utils/utils.h"

Updater::Updater(int time_step, int client_id) : m_time_step(time_step), m_cid(client_id), m_is_finished(false)
{
}

void Updater::run()
{
    while (!m_is_finished)
    {
        update();
        utils::sleep(m_time_step);
    }
}

void Updater::setFinished()
{
    m_is_finished = true;
}
