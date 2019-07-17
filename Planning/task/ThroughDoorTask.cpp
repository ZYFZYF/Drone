#include <iostream>
#include "ThroughDoorTask.h"

void ThroughDoorTask::Execute(PlanningPathUpdater *t)
{

}

const std::string ThroughDoorTask::getName()
{
    return "Through_Door_Of_" + m_object->getName();
}

void ThroughDoorTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to through the door " << m_object->getName() << std::endl;
}

void ThroughDoorTask::Exit(PlanningPathUpdater *t)
{
    Task::Exit(t);
    std::cout << "Success to through the door " << m_object->getName() << " and go to next task" << std::endl;
}

ThroughDoorTask::ThroughDoorTask(Object *object):m_object(object)
{

}
