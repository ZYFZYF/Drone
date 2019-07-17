#include "Door.h"
#include "../task/ThroughDoorTask.h"

bool Door::isDoor()
{
    return true;
}

Task *Door::getTask()
{
    static ThroughDoorTask task(this);
    return &task;
}
