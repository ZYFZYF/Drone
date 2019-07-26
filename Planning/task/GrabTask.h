#ifndef DRONE_GRABTASK_H
#define DRONE_GRABTASK_H


#include "Task.h"
#include "../../Common/object/Object.h"

class GrabTask: public Task
{
public:
    //not a good implement, lead to shared ptr

    explicit GrabTask(Object *object);

    void Enter(PlanningPathUpdater *t) override;

    void Exit(PlanningPathUpdater *t) override;

    void Execute(PlanningPathUpdater *t) override;

    const std::string getName() override;

private:
    Object *m_object;
    std::vector<Point> m_path_points;
    int m_now_target_index;
    int m_close_rounds;
    const simxFloat CLOSE_THRESHOLD = Config::Instance()->getFloatParam("MoveTask", "CLOSE_THRESHOLD");
    const simxInt CLOSE_ROUNDS_LIMIT = Config::Instance()->getIntParam("MoveTask", "CLOSE_ROUNDS_LIMIT");
};


#endif //DRONE_GRABTASK_H
