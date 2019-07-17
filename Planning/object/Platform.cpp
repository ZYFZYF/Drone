#include "Platform.h"
#include "../task/GrabTask.h"

bool Platform::isPlatform()
{
    return true;
}

Platform::Platform(const std::string &name, int client_id) : Object(name, client_id)
{
    if (getName() == "Target_platform")
        m_task = new GrabTask(this);
}

