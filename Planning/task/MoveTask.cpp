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
    if (m_destination_object->isPlatform())
    {
        m_target_pos = m_destination_object->getPosition();
        if(m_destination_object->getName() == "End")
        {
            m_target_pos.setZ(HOVER_HEIGHT_OVER_END);
        } else
        {
            m_target_pos.setZ(HOVER_HEIGHT_OVER_PLATFORM);
        }

    }
    if (m_destination_object->isDoor())
    {
        //根据在门的哪边来确定将哪儿设为终点
        if (m_start_pos.y() > m_destination_object->getPosition().y())
        {
            m_target_pos = m_destination_object->getPosition() + Point(0, Y_DISTANCE_FROM_DOOR, 0);
        } else
        {
            m_target_pos = m_destination_object->getPosition() - Point(0, Y_DISTANCE_FROM_DOOR, 0);
        }
    }
    m_path_points = t->getPathPoints(m_start_pos, m_target_pos);
    assert(!m_path_points.empty());
    std::cout << "Have " << m_path_points.size() << " path points" << std::endl;
    for(const auto &point: m_path_points)
        std::cout << point << std::endl;
    m_now_target_index = 1;
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

}

void MoveTask::Execute(PlanningPathUpdater *t)
{
    Point now_pos = t->getTargetPosition();
    //std::cout << now_pos << ' ' << m_target_pos << std::endl;
    Point error = m_path_points[m_now_target_index] - now_pos;
    if (error.norm() > CLOSE_THRESHOLD)
    {
        now_pos = now_pos + error.normalize() * std::min(MOVE_STEP_LENGTH, error.length());
        t->setTargetPosition(now_pos);
    }
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
        m_now_target_index ++;
    }
    if(m_now_target_index >= m_path_points.size())
    {
        t->finishCurrentTask();
    }
    if (m_close_rounds != 0)
    {
        std::cout << "close rounds is " << m_close_rounds << std::endl;
    }
    m_previous_round_pos = t->getDronePosition();
}
