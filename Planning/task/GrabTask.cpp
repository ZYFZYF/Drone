#include <iostream>
#include <utility>
#include "GrabTask.h"
#include "../updater/PlanningPathUpdater.h"

void GrabTask::Execute(PlanningPathUpdater *t)
{
    //fake implement, TODO
    static auto remain_rounds = 200;
    remain_rounds--;
    std::cout << "remain " << remain_rounds << " rounds" << std::endl;
    if (!remain_rounds)
    {
        t->finishCurrentTask();
    }
}

const std::string GrabTask::getName()
{
    return "Grab_On_" + m_object->getName();
}

GrabTask::GrabTask(Object *object) : m_object(object)
{

}
extern bool use_vision;
void GrabTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to grab cylinder on platform " << m_object->getName() << std::endl;
    use_vision = true;
    std::cout << "Open the eyes _(:з)∠)_" << std::endl;
}

void GrabTask::Exit(PlanningPathUpdater *t)
{
    std::cout << "Success to grab cylinder on platform " << m_object->getName() << "and go to next task" << std::endl;
    Task::Exit(t);
}
