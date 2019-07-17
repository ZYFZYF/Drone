#include <iostream>
#include "MoveTask.h"

void MoveTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to move from " << m_source_object->getName() << " to " << m_destination_object->getName() << std::endl;
}

void MoveTask::Exit(PlanningPathUpdater *t)
{
    std::cout << "Arrive at " << m_destination_object->getName() << std::endl;
    Task::Exit(t);
}

const std::string MoveTask::getName()
{
    return "Move_From_" + m_source_object->getName() + "_To_" + m_destination_object->getName();
}

MoveTask::MoveTask(Object *source, Object *destination):m_source_object(source), m_destination_object(destination)
{
    
}

void MoveTask::Execute(PlanningPathUpdater *t)
{

}
