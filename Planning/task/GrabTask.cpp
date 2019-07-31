#include <iostream>
#include <utility>
#include "GrabTask.h"
#include "../updater/PlanningPathUpdater.h"
#include "../../Common/utils/utils.h"
#include "../../Common/config/Handle.h"

void GrabTask::Execute(PlanningPathUpdater *t)
{
//    Point target_pos = t->getTargetPosition();
//    if ((cylinder_pos.x() - target_pos.x()) * (cylinder_pos.x() - target_pos.x()) +
//        (cylinder_pos.y() - target_pos.y()) * (cylinder_pos.y() - target_pos.y()) < 0.5 * 0.5)
//    {
//        std::cout << "adjust target position" << std::endl;
//        target_pos.setX(cylinder_pos.x());
//        target_pos.setY(cylinder_pos.y());
//        t->setTargetPosition(target_pos);
//    }

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
        m_close_rounds = 0;
        if (m_now_target_index == 3)
        {
            t->setHand();
            utils::sleep(3000);
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

void GrabTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to grab cylinder on platform " << m_object->getName() << std::endl;
    std::cout << "Open the eyes _(:з)∠)_" << std::endl;
    use_vision = true;
    utils::sleep(MICRO_SECONDS_FOR_DISCRIMINATE);
    use_vision = false;
    Point circle_pos = utils::getObjectPosition("CircleDummy", t->getCid());
    Point target_pos = utils::getObjectPosition("TargetDummy", t->getCid());
    std::cout << "circle_pos = " << circle_pos << std::endl;
    std::cout << "target_pos = " << target_pos << std::endl;
    Point selected_pos = target_pos;
    m_path_points.emplace_back(selected_pos.x(), selected_pos.y(), GRAB_START_HEIGHT);
    m_path_points.emplace_back(selected_pos.x(), selected_pos.y(), GRAB_START_HEIGHT - 0.3f);
    m_path_points.emplace_back(selected_pos.x(), selected_pos.y(), GRAB_START_HEIGHT - 0.325f);
    m_path_points.emplace_back(selected_pos.x(), selected_pos.y(), GRAB_START_HEIGHT);
    for(const auto &point: m_path_points)
    {
        std::cout << point << std::endl;
    }
    m_now_target_index = 0;
    if (m_now_target_index < m_path_points.size())
        t->setTargetPosition(m_path_points[m_now_target_index]);
}

void GrabTask::Exit(PlanningPathUpdater *t)
{
    std::cout << "Success to grab cylinder on platform " << m_object->getName() << "and go to next task" << std::endl;
    Task::Exit(t);
}
