#include "Door.h"
#include "../task/ThroughDoorTask.h"

bool Door::isDoor()
{
    return true;
}

Door::Door(const std::string &name, int client_id) : Object(name, client_id)
{
    m_task = new ThroughDoorTask(this);
}
