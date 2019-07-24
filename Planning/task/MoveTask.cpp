#include <iostream>
#include <cassert>
#include "MoveTask.h"
#include "../updater/PlanningPathUpdater.h"

void MoveTask::Enter(PlanningPathUpdater *t)
{
    Task::Enter(t);
    std::cout << "Prepare to move from " << m_source_object->getName() << " to " << m_destination_object->getName()
              << std::endl;
    m_previous_round_pos = m_start_pos = t->getDronePosition();
    m_path_points = t->getPathPoints(m_start_pos, m_target_pos);
    assert(m_path_points.size() >= 2);
    std::cout << "Have " << m_path_points.size() << " path points" << std::endl;
    for (const auto &point: m_path_points)
        std::cout << point << std::endl;
    m_now_target_index = 1;
    if(m_now_target_index < m_path_points.size())
        t->setTargetPosition(m_path_points[m_now_target_index]);
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

MoveTask::MoveTask(Object *source, Object *destination) : m_source_object(source), m_destination_object(destination),
                                                          m_close_rounds(0)
{
    m_start_pos = m_source_object->getValidPosition();
    m_target_pos = m_destination_object->getValidPosition();
}

void MoveTask::Execute(PlanningPathUpdater *t)
{
  //  Point now_pos = t->getTargetPosition();
    //std::cout << now_pos << ' ' << m_target_pos << std::endl;
//    Point error = m_path_points[m_now_target_index] - now_pos;
//    if (error.norm() > CLOSE_THRESHOLD)
//    {
//        now_pos = now_pos + error.normalize() * std::min(MOVE_STEP_LENGTH, error.length());
//        t->setTargetPosition(now_pos);
//    }
    //std::cout << error << ' ' << error.norm() << std::endl;
    //std::cout << (t->getDronePosition() - m_target_pos).norm() << std::endl;
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
        if(m_now_target_index < m_path_points.size())
            t->setTargetPosition(m_path_points[m_now_target_index]);
    }
    if (m_now_target_index >= m_path_points.size())
    {
        t->finishCurrentTask();
    }
    if (m_close_rounds != 0)
    {
        std::cout << "close rounds is " << m_close_rounds << std::endl;
    }
    m_previous_round_pos = t->getDronePosition();
}

float MoveTask::getDistance(Router *router) const
{
    std::vector<Point> path = router->route(m_start_pos, m_target_pos);
    float dist = 0;
    for (auto i = 1; i < path.size(); i++)
    {
        dist += distance(path[i - 1], path[i]);
    }
    return dist;
}
