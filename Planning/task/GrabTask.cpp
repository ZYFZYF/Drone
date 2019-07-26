#include <iostream>
#include <utility>
#include "GrabTask.h"
#include "../updater/PlanningPathUpdater.h"
#include "../../Common/utils/utils.h"

void GrabTask::Execute(PlanningPathUpdater *t)
{
    if ((t->getDronePosition() - m_path_points[m_now_target_index]).norm() < CLOSE_THRESHOLD)
    {
        m_close_rounds++;
    } else
    {
        m_close_rounds = 0;
    }
    if (m_close_rounds >= CLOSE_ROUNDS_LIMIT)
    {
        m_now_target_index++;
        if(m_now_target_index == 2)
        {
            t->setHand();
            utils::sleep(3000);
            use_vision = false;
        }
        if (m_now_target_index < m_path_points.size())
            t->setTargetPosition(m_path_points[m_now_target_index]);
    }
    if (m_now_target_index >= m_path_points.size())
    {
        t->finishCurrentTask();
    }
    if (m_close_rounds != 0)
    {
        std::cout << "close rounds is " << m_close_rounds << ' ' << m_now_target_index << std::endl;
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
    Point target_pos = t->getHotTargetPosition();
    target_pos.setZ(target_pos.z() + 0.5f);
    m_path_points.emplace_back(Point(target_pos.x(), target_pos.y(), target_pos.z() - 0.28f));
    m_path_points.emplace_back(target_pos.x(), target_pos.y(), target_pos.z() - 0.32f);
    m_path_points.emplace_back(target_pos.x(), target_pos.y(), target_pos.z());
    m_now_target_index = 0;
    if (m_now_target_index < m_path_points.size())
        t->setTargetPosition(m_path_points[m_now_target_index]);
}

void GrabTask::Exit(PlanningPathUpdater *t)
{
    std::cout << "Success to grab cylinder on platform " << m_object->getName() << "and go to next task" << std::endl;
    Task::Exit(t);
}
