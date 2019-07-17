#include "Platform.h"
#include "../task/GrabTask.h"

bool Platform::isPlatform()
{
    return true;
}

Task *Platform::getTask()
{
    static GrabTask task(this);
    if (getName() == "Target_platform")return &task;
    else return nullptr;
}
