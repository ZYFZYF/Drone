#include <iostream>
#include <utility>
#include "GrabTask.h"

void GrabTask::Execute(PlanningPathUpdater *t)
{

}

const std::string GrabTask::getName()
{
    return "Grab_On_" + m_object->getName();
}

GrabTask::GrabTask(Object *object):m_object(object)
{

}

void GrabTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to grab cylinder on platform " << m_object->getName() << std::endl;
}

void GrabTask::Exit(PlanningPathUpdater *t)
{
    std::cout << "Success to grab cylinder on platform " << m_object->getName() <<"and go to next task" << std::endl;
    Task::Exit(t);
}
