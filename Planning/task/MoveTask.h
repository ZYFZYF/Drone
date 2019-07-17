#ifndef DRONE_MOVETASK_H
#define DRONE_MOVETASK_H


#include "Task.h"
#include "../object/Object.h"

class MoveTask : public Task
{
public:
    explicit MoveTask(Object *source, Object *destination);

    void Enter(PlanningPathUpdater *t) override;

    void Exit(PlanningPathUpdater *t) override;

    void Execute(PlanningPathUpdater *t) override;

    const std::string getName() override;

private:
    int m_close_rounds;
    Object *m_source_object;
    Object *m_destination_object;
    Point m_start_pos, m_target_pos, m_previous_round_pos;
    const simxFloat HOVER_HEIGHT_OVER_PLATFORM = Config::Instance()->getFloatParam("MoveTask", "HOVER_HEIGHT_OVER_PLATFORM");
    const simxFloat Y_DISTANCE_FROM_DOOR = Config::Instance()->getFloatParam("MoveTask", "Y_DISTANCE_FROM_DOOR");
    const simxFloat MOVE_STEP_LENGTH = Config::Instance()->getFloatParam("MoveTask", "MOVE_STEP_LENGTH");
    const simxFloat CLOSE_THRESHOLD = Config::Instance()->getFloatParam("MoveTask", "CLOSE_THRESHOLD");
    const simxInt CLOSE_ROUNDS_LIMIT = Config::Instance()->getIntParam("MoveTask", "CLOSE_ROUNDS_LIMIT");
};


#endif //DRONE_MOVETASK_H
